# Microsoft Developer Studio Project File - Name="H323Parser" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=H323Parser - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "H323Parser.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "H323Parser.mak" CFG="H323Parser - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "H323Parser - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "H323Parser - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "H323Parser___Win32_Debug"
# PROP BASE Intermediate_Dir "H323Parser___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "..\ASN1" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "H323PARSER_EXPORTS" /FD /D /GZ /Zm500 /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "..\ASN1" /D "_DEBUG" /D "WIN32" /D "__WIN32__" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "H323PARSER_EXPORTS" /D "ASN1_HAS_IOSTREAM" /D "ASN1_STATIC" /FD /D /GZ /Zm500 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x404 /d "_DEBUG"
# ADD RSC /l 0x404 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 nmapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib asn1_nb_d.lib /nologo /dll /debug /machine:I386 /out:"Debug/IIIh323Parser.dll" /pdbtype:sept /libpath:"..\LIB"
# ADD LINK32 nmapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"Debug/IIIh323Parser.dll" /pdbtype:sept /libpath:"..\LIB"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "H323Parser___Win32_Release"
# PROP BASE Intermediate_Dir "H323Parser___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "." /I "..\ASN1" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "H323PARSER_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "..\ASN1" /D "NDEBUG" /D "WIN32" /D "__WIN32__" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "H323PARSER_EXPORTS" /D "ASN1_HAS_IOSTREAM" /D "ASN1_STATIC" /YX /FD /Zm300 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x404 /d "NDEBUG"
# ADD RSC /l 0x404 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 nmapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib asn1_nb.lib /nologo /dll /machine:I386 /out:"Release/IIIh323Parser.dll" /libpath:"..\LIB"
# ADD LINK32 nmapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/IIIh323Parser.dll" /libpath:"..\LIB"

!ENDIF 

# Begin Target

# Name "H323Parser - Win32 Debug"
# Name "H323Parser - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\addressing_data_elements.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\call_completion_operations.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\call_diversion_operations.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\call_hold_operations.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\call_offer_operations.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\call_park_pickup_operations.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\call_transfer_operations.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\call_waiting_operations.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\asnh323\h2250v4.asn

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"
# Begin Custom Build
InputPath=..\asnh323\h2250v4.asn

"h2250v4_new.asn" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	transform_h2250.js

# End Custom Build

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"
# Begin Custom Build
InputPath=..\asnh323\h2250v4.asn

"h2250v4_new.asn" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	transform_h2250.js

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\h2250v4_new.asn

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"
# Begin Custom Build
InputPath=.\h2250v4_new.asn

BuildCmds= \
	cd ..\asnh323 \
	..\Lib\asnparser -v -c -o ..\h323parser h245v7.asn h235v2.asn h248.asn ..\h323parser\h2250v4_new.asn ro.asn h4501.asn h4502.asn h4503.asn h4504.asn h4505.asn h4506.asn h4507.asn h4508.asn h4509.asn h45010.asn \
	

"addressing_data_elements.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"addressing_data_elements.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"addressing_data_elements.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_completion_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_completion_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_completion_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_diversion_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_diversion_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_diversion_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_hold_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_hold_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_hold_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_offer_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_offer_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_offer_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_park_pickup_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_park_pickup_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_park_pickup_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_transfer_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_transfer_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_transfer_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_waiting_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_waiting_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_waiting_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h225_generic_parameters_definition.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h225_generic_parameters_definition.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h235_security_messages.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h235_security_messages.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h235_security_messages.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h235_security_messages_t.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h323_messages.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h323_messages.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h323_messages.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h4501_general_error_list.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h4501_general_error_list.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h4501_supplementary_serviceapdu_structure.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h4501_supplementary_serviceapdu_structure.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h4501_supplementary_serviceapdu_structure.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"hm_aliasaddress.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"hm_aliasaddress.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"hm_aliasaddress.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"hm_callidentifier.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"hm_callidentifier.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"hm_callidentifier.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"manufacturer_specific_service_extension_definition.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"manufacturer_specific_service_extension_definition.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"manufacturer_specific_service_extension_definition.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"manufacturer_specific_service_extension_definition_t.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"media_gateway_control.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"media_gateway_control.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"media_gateway_control.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"message_waiting_indication_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"message_waiting_indication_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"message_waiting_indication_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"mgc_signalsdescriptor.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"mgc_signalsdescriptor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"mgc_signalsdescriptor.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"multimedia_system_control.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"multimedia_system_control.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"multimedia_system_control.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"name_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"name_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"name_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"remote_operations_apdus.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"remote_operations_apdus.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"remote_operations_apdus.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"remote_operations_apdus_t.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"remote_operations_information_objects.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"remote_operations_information_objects.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"remote_operations_information_objects.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"
# Begin Custom Build
InputPath=.\h2250v4_new.asn

BuildCmds= \
	cd ..\asnh323 \
	..\Lib\asnparser -v -c -o ..\h323parser h245v7.asn h235v2.asn h248.asn ..\h323parser\h2250v4_new.asn ro.asn h4501.asn h4502.asn h4503.asn h4504.asn h4505.asn h4506.asn h4507.asn h4508.asn h4509.asn h45010.asn \
	

"addressing_data_elements.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"addressing_data_elements.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"addressing_data_elements.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_completion_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_completion_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_completion_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_diversion_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_diversion_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_diversion_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_hold_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_hold_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_hold_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_offer_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_offer_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_offer_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_park_pickup_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_park_pickup_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_park_pickup_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_transfer_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_transfer_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_transfer_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_waiting_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_waiting_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"call_waiting_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h225_generic_parameters_definition.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h225_generic_parameters_definition.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h235_security_messages.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h235_security_messages.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h235_security_messages.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h235_security_messages_t.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h323_messages.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h323_messages.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h323_messages.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h4501_general_error_list.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h4501_general_error_list.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h4501_supplementary_serviceapdu_structure.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h4501_supplementary_serviceapdu_structure.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"h4501_supplementary_serviceapdu_structure.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"hm_aliasaddress.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"hm_aliasaddress.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"hm_aliasaddress.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"hm_callidentifier.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"hm_callidentifier.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"hm_callidentifier.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"manufacturer_specific_service_extension_definition.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"manufacturer_specific_service_extension_definition.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"manufacturer_specific_service_extension_definition.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"manufacturer_specific_service_extension_definition_t.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"media_gateway_control.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"media_gateway_control.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"media_gateway_control.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"message_waiting_indication_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"message_waiting_indication_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"message_waiting_indication_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"mgc_signalsdescriptor.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"mgc_signalsdescriptor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"mgc_signalsdescriptor.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"multimedia_system_control.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"multimedia_system_control.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"multimedia_system_control.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"name_operations.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"name_operations.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"name_operations.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"remote_operations_apdus.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"remote_operations_apdus.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"remote_operations_apdus.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"remote_operations_apdus_t.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"remote_operations_information_objects.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"remote_operations_information_objects.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"remote_operations_information_objects.inl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\h225_generic_parameters_definition.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\h235_security_messages.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\H323.def

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\h323_messages.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\H323Parser.cpp

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"
# ADD BASE CPP /YX
# ADD CPP /YX

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\h4501_general_error_list.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\h4501_supplementary_serviceapdu_structure.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hm_aliasaddress.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hm_callidentifier.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\manufacturer_specific_service_extension_definition.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\media_gateway_control.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\message_waiting_indication_operations.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mgc_signalsdescriptor.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\multimedia_system_control.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\name_operations.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\perattacher.cpp

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Q931pdu.cpp

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\remote_operations_apdus.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\remote_operations_information_objects.cxx

!IF  "$(CFG)" == "H323Parser - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ELSEIF  "$(CFG)" == "H323Parser - Win32 Release"

# PROP Intermediate_Dir "Release"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\perattacher.h
# End Source File
# Begin Source File

SOURCE=.\Q931pdu.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
