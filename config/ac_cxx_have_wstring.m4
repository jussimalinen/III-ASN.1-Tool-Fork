dnl @synopsis AC_CXX_HAVE_WSTRING
dnl
dnl If the C++ library has a working wstring, define HAVE_WSTRING.
dnl
dnl @author Huang-Ming Huang
dnl @version $Id: ac_cxx_have_wstring.m4,v 1.4 2002/07/04 03:47:22 mangelo Exp $
dnl

AC_DEFUN([AC_CXX_HAVE_WSTRING],
 [ AC_CACHE_CHECK([whether the compiler has wstring],
    		  [ac_cv_cxx_have_wstring],
    		  [
		      AC_REQUIRE([AC_CXX_NAMESPACES])
		      AC_LANG_SAVE
		      AC_LANG_CPLUSPLUS
		      AC_TRY_COMPILE([
		         #include <string>
		         #ifdef HAVE_NAMESPACES
		         using namespace std;
		         #endif
		         ],[wstring str; str = L"Hello"; return 0;],
		         ac_cv_cxx_have_wstring=yes, 
		         ac_cv_cxx_have_wstring=no
		      )
		      dnl GCC 3.0 require _GLIBCPP_USE_CHAR_T to be defined  
		      if test "$ac_cv_cxx_have_wstring" = no; then
		         AC_TRY_COMPILE([
		            #define _GLIBCPP_USE_WCHAR_T 1
		            #include<string>
		            #ifdef HAVE_NAMESPACES
		            using namespace std;
		            #endif
		            ],[
		            wstring str; str = L"Hello"; return 0;
		            ],[
		            ac_cv_cxx_have_wstring=yes
			    ac_cv_need__GLIBCPP_USE_WCHAR_T=yes		            
		            ], ac_cv_cxx_have_wstring=no)
		     fi 
		     dnl GCC 2.95.x need a typedef
		     if test "$ac_cv_cxx_have_wstring" = no; then
		         AC_TRY_COMPILE([
		            #include<string>
		            #ifdef HAVE_NAMESPACES
		            using namespace std;
		            #endif
		            ],[
		            typedef basic_string<wchar_t> wstring;
		            wstring str; str = L"Hello"; return 0;
		            ],[
		            ac_cv_cxx_have_wstring=yes
			    ac_cv_need_wstring_typedef=yes		            
		            ], ac_cv_cxx_have_wstring=no)
		     fi 
		     AC_LANG_RESTORE
     		  ]
    		 )
  
  if test "$ac_cv_cxx_have_wstring" = yes; then
    AC_DEFINE(HAVE_WSTRING,,[define if the compiler has wstring])
    if test "$ac_cv_need__GLIBCPP_USE_WCHAR_T" = yes; then
    	AC_DEFINE(_GLIBCPP_USE_WCHAR_T,1, [define if the GLIB need the flag to turn on wstring support])
    fi
    if test "$ac_cv_need_wstring_typedef" = yes; then
    	AC_DEFINE(NEED_WSTRING_TYPEDEF, 1, [define if explicit wstring typedef is needed])
    fi
  fi
 ]
)
