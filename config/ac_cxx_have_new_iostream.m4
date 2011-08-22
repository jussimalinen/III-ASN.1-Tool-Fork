dnl @synopsis AC_CXX_HAVE_NEW_IOSTREAM
dnl
dnl If the C++ library has a working ASNI compliant iostream, define HAVE_NEW_IOSTREAM.
dnl
dnl @author Huang-Ming Huang
dnl @version $Id: ac_cxx_have_new_iostream.m4,v 1.1.1.1 2001/08/01 07:38:42 mangelo Exp $
dnl
AC_DEFUN([AC_CXX_HAVE_NEW_IOSTREAM],
[AC_CACHE_CHECK(whether the compiler has ASNI compliant iostream,
ac_cv_cxx_have_new_iostream,
[AC_REQUIRE([AC_CXX_NAMESPACES])
 AC_LANG_SAVE
 AC_LANG_CPLUSPLUS
 AC_TRY_COMPILE([#include <ios>
using namespace std;
],[ios_base::iostate state = ios_base::goodbit; return 0;],
 ac_cv_cxx_have_new_iostream=yes, ac_cv_cxx_have_new_iostream=no)
 AC_LANG_RESTORE
])
if test "$ac_cv_cxx_have_new_iostream" = yes; then
  AC_DEFINE(HAVE_NEW_IOSTREAM,,[define if the compiler has ASNI compliant iostream])
fi
])
