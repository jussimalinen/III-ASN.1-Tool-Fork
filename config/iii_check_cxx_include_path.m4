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

dnl @synopsis III_CHECK_CXX_INCLUDE_PATH
dnl
dnl Checks whether the environment variable CPLUS_INCLUDE_PATH work correctly
dnl This is bug specific to cygwin 1.3.x
dnl
dnl @author Huang-Ming Huang

AC_DEFUN[(III_CHECK_CXX_INCLUDE_PATH], [
if test "$ac_cv_prog_gxx" = yes; then
AC_CACHE_CHECK([whether the environment variable CPLUS_INCLUDE_PATH work correctly], 
iii_cv_cplus_include_path, [
AC_LANG_SAVE
 
AC_LANG_CPLUSPLUS
 
iii_cv_cplus_include_path_backup=${CPLUS_INCLUDE_PATH}
export CPLUS_INCLUDE_PATH=.
cat > vector << EOF
yes_yes_yes
EOF
AC_EGREP_CPP(yes_yes_yes,[ #include <vector> ],
iii_cv_cplus_include_path=yes,
iii_cv_cplus_include_path=no)
export CPLUS_INCLUDE_PATH=$iii_cv_cplus_include_path_backup
rm vector
])
fi

if test "$iii_cv_cplus_include_path" = no && test -n "$CPLUS_INCLUDE_PATH"; then
CPPFLAGS="`echo -I$CPLUS_INCLUDE_PATH | sed 's/:/ -I/g'` $CPPFLAGS"
fi

])

