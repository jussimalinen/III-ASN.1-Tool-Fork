// makedef.cpp : Defines the entry point for the console application.
//

#if _MSC_VER <= 1200
#pragma warning(disable:4786)
#elif _MSC_VER >= 1400
#pragma warning(disable:4996)
#endif


#include <unistd.h>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include <fcntl.h>
#include <process.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>




using namespace std;

struct SymbolContent {
	SymbolContent() : in_lib(false){}
	int ordinal;
	string unmangled;
	bool in_lib;
};

typedef map<string, SymbolContent> SymbolMap;

struct comp_ordinal {
	bool operator()(SymbolMap::value_type& lhs, SymbolMap::value_type& rhs) {
		return lhs.second.ordinal < rhs.second.ordinal;
	}
};

int max_ordinal = 0;

void output_symbol(ostream& os, 
				   const string& name, 
				   int ordinal, 
				   const string& unmangled)
{
	os << "    " << name << " @" << ordinal
			     << " NONAME ;" << unmangled << '\n';
}

namespace std {
istream& operator >> (istream& is, SymbolMap::value_type& symbol)
{
	string noname;
	char at, semicolon;
	string& name = const_cast<string&>(symbol.first);
	is >> name >> at >> symbol.second.ordinal >> noname 
		    >> semicolon;
	getline(is,symbol.second.unmangled);
	
	if (at != '@' || noname != "NONAME" || semicolon != ';')
		is.setstate(ios_base::failbit);
	return is;
}


ostream& operator << (ostream& os, const SymbolMap::value_type& symbol)
{
	if (symbol.second.in_lib)
		output_symbol(os, symbol.first, symbol.second.ordinal, symbol.second.unmangled);
	return os;
}

}

int main(int argc, char* argv[])
{
	cout << "start" << endl; 
	ifstream ignore_file;
	string libfilename;
	int c;
	const char* opt = "l:x:";

	while ((c=getopt(argc, argv, opt)) != -1) {
		switch (c) {
			case 'l':
	            libfilename = optarg; 
			case 'x':
				ignore_file.open(optarg);
				break;
		}
	}
	
	if (argc-optind != 1 ) {
		cerr << "Usage : makedef -l libfile [-x ignore_file] deffile\n";
		return 1;
	}

	/*
	// Although it's OK to use pipe when the program is run under windows command prompt, 
	// it causes some trouble when the program used in the Visual Studio custom build. For
	// some strange reason, VS will redirect the stdout of child process to the Output 
	// Window instead of using the pipe which has been assigned by the parent proces.
	// Therefore, I just use a temporary file instead of pipe.

	int fdStdOutPipe[2];

	// Create the pipe
	if(_pipe(fdStdOutPipe, 512, O_NOINHERIT) == -1)
		return   1;

	// Duplicate stdout file descriptor (next line will close original)
	int fdStdOut = _dup(_fileno(stdout));


	// Duplicate write end of pipe to stdout file descriptor
	if(_dup2(fdStdOutPipe[1], _fileno(stdout)) != 0)
		return   2;

	// Close original write end of pipe
	_close(fdStdOutPipe[1]);
    */

	char** p = _environ;
	const char* arg[]={"dumpbin", "/symbols", 0, 0, 0};
	char out[128];
	_snprintf(out, 127, "/out:%s.tmp",libfilename.c_str());
	arg[2] = out;
	arg[3] = libfilename.c_str();

	const char* outfile = out+5;

	if (_spawnvpe(_P_WAIT  ,"dumpbin", arg, p) !=0) {
		cerr << "Error when executing \"dumpbin\"\n";
		return 1;
	}

	/*
	// Duplicate copy of original stdout back into stdout
	if(_dup2(fdStdOut, _fileno(stdout)) != 0)
		return   3;

	// Close duplicate copy of original stdout
	_close(fdStdOut);

	// Duplicate read end of pipe to stdin file descriptor
    if(_dup2(fdStdOutPipe[0], _fileno(stdin)) != 0)
         return   2;

    */

	typedef set<string> IgnoreSet;
	IgnoreSet ignores;

	std::string keyword;
	if (ignore_file.is_open()) {
		while (ignore_file >> keyword && keyword != "EXPORTS");
		while (ignore_file >> keyword) {
			ignores.insert(keyword);
			getline(ignore_file, keyword);
		}
	}

	SymbolMap def_symbols;

	char* def_filename = argv[optind];
	ifstream rdeffile(def_filename);
	int max_ordinal=-1;

	if (rdeffile.is_open()) {
		while (rdeffile >> keyword && keyword != "EXPORTS");
		
		istream_iterator<SymbolMap::value_type> first(rdeffile), last;
		def_symbols.insert(first, last);
		
		rdeffile.close();
	}

	typedef map<string, string> Symbols;
	Symbols new_symbols;

	ifstream symfile(outfile);
	//istream& symfile =  cin ;

	while (symfile) {
		char line[9192];
		symfile.getline(line, 9192);
		char* namepos = strchr(line, '|');
		if (namepos != NULL) {
			*namepos = '\0';
			while (*++namepos == ' ');
			if (strstr(line, " UNDEF ") == NULL &&
				strstr(line, " External ") != NULL &&
				strstr(namepos, "deleting destructor") == NULL) {
				size_t namelen = strcspn(namepos," \n\r\t");
				namepos[namelen] = '\0';
				if (ignores.count(namepos))
					continue;
				SymbolMap::iterator it = def_symbols.find(namepos);
				if (it != def_symbols.end())
					it->second.in_lib = true;
				else if (strncmp(namepos,"??_C@_", 6) != 0 &&
					strncmp(namepos, "__real@", 7) != 0 &&
					strncmp(namepos, "?__LINE__Var@", 13) !=0) 
				{
						char* unmangled = strchr(namepos+namelen+1, '(');
						if (unmangled == NULL)
							unmangled = namepos;
						else {
							++unmangled;
							char* endunmangled = strrchr(unmangled, ')');
							if (endunmangled != NULL)
								*endunmangled = '\0';
						}

						//if (strstr(unmangled, "anonymous namespace") == NULL)
						new_symbols[namepos]=unmangled;
				}
			}
		}

	}

	ofstream odeffile(argv[optind]);

	if (!odeffile.is_open())	
		return 1;
	char* enddeffile = strrchr(def_filename, '.');
	*enddeffile = '\0';
	odeffile << "LIBRARY " << def_filename << '\n'
            << "EXPORTS" << endl;

	
	
	copy(def_symbols.begin(), def_symbols.end(), 
		 ostream_iterator<SymbolMap::value_type>(odeffile));
		 

	SymbolMap::iterator max_itr = max_element(def_symbols.begin(), def_symbols.end(), comp_ordinal());

	int i = max_itr == def_symbols.end() ? 1 : max_itr->second.ordinal+1;
	for (Symbols::iterator itr = new_symbols.begin();
		 itr != new_symbols.end(); 
		 ++itr, ++i) {
		 output_symbol(odeffile, itr->first, i, itr->second);
	}

	remove(outfile);
	
	return 0;
}

