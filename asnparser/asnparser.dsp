# Microsoft Developer Studio Project File - Name="ASNParser" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=ASNParser - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "asnparser.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "asnparser.mak" CFG="ASNParser - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ASNParser - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ASNParser - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/ITGv4/asnparser", LDAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ASNParser - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "." /D "NDEBUG" /FR /FD /Zm500 /c
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"..\Lib\asnparser.exe" /libpath:"..\..\lib"

!ELSEIF  "$(CFG)" == "ASNParser - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GR /GX /ZI /Od /I "." /D "_DEBUG" /FR /FD /Zm500 /c
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"..\Lib\asnparser.exe" /pdbtype:sept /libpath:"..\..\lib"

!ENDIF 

# Begin Target

# Name "ASNParser - Win32 Release"
# Name "ASNParser - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ".cxx"
# Begin Source File

SOURCE=.\asn_grammar.cxx

!IF  "$(CFG)" == "ASNParser - Win32 Release"

# ADD CPP /D "MSDOS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "ASNParser - Win32 Debug"

# ADD CPP /W3 /D "MSDOS"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asn_grammar.y

!IF  "$(CFG)" == "ASNParser - Win32 Release"

# Begin Custom Build - Performing Bison Step
InputPath=.\asn_grammar.y
InputName=asn_grammar

BuildCmds= \
	bison -t -v -d $(InputName).y \
	move $(InputName)_tab.c $(InputName).cxx \
	move $(InputName)_tab.h $(InputName).h \
	

"$(InputName).cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ASNParser - Win32 Debug"

# Begin Custom Build - Performing Bison Step
InputPath=.\asn_grammar.y
InputName=asn_grammar

BuildCmds= \
	bison -v -d -t $(InputName).y \
	move $(InputName)_tab.c $(InputName).cxx \
	move $(InputName)_tab.h $(InputName).h \
	

"$(InputName).cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asn_lex.cxx
# ADD CPP /W2
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\asn_lex.l

!IF  "$(CFG)" == "ASNParser - Win32 Release"

USERDEP__ASN_L="asn_grammar.h"	"asn_grammar.cxx"	
# Begin Custom Build - Performing Lex Step
InputPath=.\asn_lex.l
InputName=asn_lex

"$(InputName).cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	flex -t $(InputName).l > $(InputName).cxx

# End Custom Build

!ELSEIF  "$(CFG)" == "ASNParser - Win32 Debug"

USERDEP__ASN_L="asn_grammar.h"	"asn_grammar.cxx"	
# Begin Custom Build - Performing Lex Step
InputPath=.\asn_lex.l
InputName=asn_lex

"$(InputName).cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	flex -t $(InputName).l > $(InputName).cxx

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asn_ref_grammar.cxx

!IF  "$(CFG)" == "ASNParser - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "ASNParser - Win32 Debug"

# ADD CPP /W3
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asn_ref_grammar.y

!IF  "$(CFG)" == "ASNParser - Win32 Release"

# Begin Custom Build - Performing Bison Step
InputPath=.\asn_ref_grammar.y
InputName=asn_ref_grammar

BuildCmds= \
	bison -p id -t -v -d $(InputName).y \
	move $(InputName)_tab.c $(InputName).cxx \
	move $(InputName)_tab.h $(InputName).h \
	

"$(InputName).cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ASNParser - Win32 Debug"

# Begin Custom Build - Performing Bison Step
InputPath=.\asn_ref_grammar.y
InputName=asn_ref_grammar

BuildCmds= \
	bison -p id -v -d -t $(InputName).y \
	move $(InputName)_tab.c $(InputName).cxx \
	move $(InputName)_tab.h $(InputName).h \
	

"$(InputName).cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asn_ref_lex.cxx

!IF  "$(CFG)" == "ASNParser - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "ASNParser - Win32 Debug"

# ADD CPP /W3
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asn_ref_lex.l

!IF  "$(CFG)" == "ASNParser - Win32 Release"

# Begin Custom Build
InputPath=.\asn_ref_lex.l
InputName=asn_ref_lex

"$(InputName).cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	flex -Pid -t $(InputName).l > $(InputName).cxx

# End Custom Build

!ELSEIF  "$(CFG)" == "ASNParser - Win32 Debug"

# Begin Custom Build - Performing Lex Step
InputPath=.\asn_ref_lex.l
InputName=asn_ref_lex

"$(InputName).cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	flex -Pid -t $(InputName).l > $(InputName).cxx

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\getopt.c
# End Source File
# Begin Source File

SOURCE=.\main.cxx

!IF  "$(CFG)" == "ASNParser - Win32 Release"

!ELSEIF  "$(CFG)" == "ASNParser - Win32 Debug"

# ADD CPP /W3

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\asn_grammar.h
# End Source File
# Begin Source File

SOURCE=.\main.h
# End Source File
# End Group
# End Target
# End Project
