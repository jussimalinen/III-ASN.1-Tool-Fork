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

dnl @synopsis III_CHECK_STLPORT
dnl 
dnl Check the existance of STLport
dnl
dnl @author Huang-Ming Huang

AC_DEFUN([III_CHECK_STLPORT], [
    dnl AC_BEFORE([$0],[AC_CXX_HAVE_STL])
    if test "$ac_cv_cxx_have_stl" = yes; then
      AC_CACHE_CHECK([whether the STLport exists],
        [iii_cv_have_stlport], [
           AC_LANG_SAVE
           AC_LANG_CPLUSPLUS
 
           AC_EGREP_CPP(yes,[
              #include <vector>
              #ifdef __SGI_STL_PORT
              yes
              #endif
             ],
             iii_cv_have_stlport=yes,
             iii_cv_have_stlport=no)
        ]
       )

       dnl
       dnl Choose the correct STL library to link with
       dnl
 
       if test "$host_os" = cygwin && test "$iii_cv_have_stlport" = yes ; then
          LIBSTL=-lstlport_cygwin
       elif test "$ac_cv_prog_gxx" = yes; then
          if test "$iii_cv_have_stlport" = yes; then
            LIBSTL=-lstlport_gcc
          else
            LIBSTL=-lstdc++
          fi;
       fi
             
    else
      iii_cv_have_stlport=no
    fi
])
