dnl
dnl Copyright (c) 2001 Institute for Information Industry, Taiwan, Republic of China 
dnl Written by angelo@iii.org.tw
dnl 
dnl This file is part of III ASN.1 Tool.
dnl 
dnl The contents of this file are subject to the Mozilla Public License
dnl Version 1.0 (the "License"); you may not use this file except in
dnl compliance with the License. You may obtain a copy of the License at
dnl http://www.mozilla.org/MPL/
dnl
dnl Software distributed under the License is distributed on an "AS IS"
dnl basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
dnl the License for the specific language governing rights and limitations
dnl under the License.
dnl 
dnl III ASN.1 Tool is the ASN.1 to C++ compiler which transforms ASN.1 Module
dnl to C++ codes along with the C++ run time library for encoding and decoding 
dnl ASN.1 types. For details, see the III ASN.1 Tool World-Wide-Web page, 
dnl `http://www.iii.org.tw/portal/lab1/asn1tool.html'.
dnl

dnl @synopsis III_CHECK_CROSS_SETTING(VARIABLE, HOST_FILE)
dnl
dnl Choose the correct VARIABLE setting from HOST_FILE
dnl
dnl @author Huang-Ming Huang

AC_DEFUN([III_CHECK_CROSS_SETTING],[
	if test -z "[$]$1"; then
		xx=`sed -n -e 's/^[[:blank:]]*$1[[:blank:]]*=[[:blank:]]*\(.*\)$/\1/p' < $2`
    	if test -n "${xx}" ; then
      		$1=$xx
    	fi
    fi
])



dnl @synopsis III_CROSS_TOOLS
dnl
dnl Choose the correct C++ compiler tool settings.
dnl
dnl If the subdirecotry "config" contains a file with the pattern
dnl mh-$host_alias, then use the definition of CC CXX 
dnl RANLIB LDFLAGS CFLAGS CXXFLAGS CPPFLAGS from that file, otherwise
dnl use AC_PROG_CXX and AC_PROG_RANLIB to find a suitable setting.
dnl
dnl @author Huang-Ming Huang

AC_DEFUN([III_CROSS_TOOLS],[
if test -e $srcdir/config/mh-$host_alias ; then
	host_frag=$srcdir/config/mh-$host_alias
	
	III_CHECK_CROSS_SETTING(CC,${host_frag})
	III_CHECK_CROSS_SETTING(CXX,${host_frag})
	III_CHECK_CROSS_SETTING(RANLIB,${host_frag})
	III_CHECK_CROSS_SETTING(CFLAGS,${host_frag})
	III_CHECK_CROSS_SETTING(CXXFLAGS,${host_frag})
	III_CHECK_CROSS_SETTING(CPPFLAGS,${host_frag})
	III_CHECK_CROSS_SETTING(LDFLAGS,${host_frag})
	
	if test "$host_alias" != "$build_alias" ; then
		ac_cv_prog_cc_cross=yes
		dnl prevent the AC_PROG_CXX from running the program produce by cross compiler
		ac_exeext=yyy
	else
		ac_cv_prog_cc_cross=no
	fi
fi

dnl Checks for programs.
AC_CHECK_TOOL(CC, gcc)
AC_PROG_CC
AC_CHECK_TOOL(CXX, c++)
AC_PROG_CXX
AC_CHECK_TOOL(RANLIB, ranlib, :)
AC_PROG_CPP
AC_PROG_CXXCPP
])
