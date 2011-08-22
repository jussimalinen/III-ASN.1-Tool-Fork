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

dnl @synopsis III_ENABLE_STL_THREAD
dnl
dnl @author Huang-Ming Huang

AC_DEFUN([III_ENABLE_STL_THREAD], [
  AC_BEFORE([III_CHECK_STLPORT])
  if test x"$ac_cv_prog_gxx" = xyes; then
        if test x"$iii_cv_have_stlport" = xno; then
        # assume using libstdc++
                if test x"$host_os" = xcygwin ; then
                        AC_DEFINE([__STL_WIN32THREADS], , [enable libstdc++ WIN32 thread support] )
                else
                        AC_DEFINE([__STL_PTHREADS], , [enable libstdc++ pthread support] )
                fi
        else
        # using stlport
                AC_DEFINE([_REENTRANT], , [enable STLport thread support])
        fi
  fi
])
