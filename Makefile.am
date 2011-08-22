#
# Copyright (c) 2001 Institute for Information Industry, Taiwan, Republic of China 
# Written by mangelo@users.sourceforge.net
# 
# This file is part of III ASN.1 Tool.
# 
# The contents of this file are subject to the Mozilla Public License
# Version 1.0 (the "License"); you may not use this file except in
# compliance with the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS"
# basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
# the License for the specific language governing rights and limitations
# under the License.
# 
# III ASN.1 Tool is the ASN.1 to C++ compiler and C++ run time library
# for encoding and decoding ASN.1 types.
# For details, see the III ASN.1 Tool World-Wide-Web page, 
# `http://iiiasn1.sourceforge.net'.
#

AUTOMAKE_OPTIONS = dist-zip
ACLOCAL = @ACLOCAL@ -I config

H323Parser_FILES = h323parser/perattacher.h\
				   h323parser/perattacher.cpp\
				   h323parser/Q931pdu.h\
				   h323parser/Q931pdu.cpp\
				   h323parser/pointainer.h\
				   h323parser/H323Parser.cpp\
				   h323parser/H323.def\
				   h323parser/h225.sed\
				   h323parser/H323Parser.dsp\
				   h323parser/H323Parser.vcproj
				   
				  
config_FIELS = config/ac_cxx_have_new_iostream.m4\
               config/ac_cxx_have_stl.m4\
	       config/ac_cxx_have_wstring.m4\
	       config/ac_cxx_namespaces.m4\
	       config/acx_pthread.m4\
               config/iii_check_cxx_include_path.m4\
               config/iii_check_stlport.m4\
               config/iii_cross_tools.m4\
               config/iii_enable_stl_thread.m4\
	       config/config.guess\
	       config/config.sub\
	       config/install-sh\
	       config/mh-powerpc-mt\
	       config/missing\
	       config/mkinstalldirs  
	  
makedef_FILES = makedef/makedef.cpp makedef/makedef.dsp makedef/makedef.vcproj
				   
EXTRA_DIST = configure mpl-1.0.htm iiiasn1.dsw iiiasn1.sln $(H323Parser_FILES) $(config_FIELS) $(makedef_FILES)

SUBDIRS = asnparser asn1 @asnh323dir@

