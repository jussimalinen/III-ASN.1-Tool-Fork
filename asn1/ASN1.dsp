# Microsoft Developer Studio Project File - Name="ASN1" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ASN1 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ASN1.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ASN1.mak" CFG="ASN1 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ASN1 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ASN1 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/ITGv4/ASN1", CAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ASN1 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /I "." /D "NDEBUG" /D "_LIB" /D "__WIN32__" /D "WIN32" /D "_MBCS" /D "ASN1_HAS_IOSTREAM" /D "ASN1_STATIC" /Yc"asn1.h" /FD /c
# ADD BASE RSC /l 0x404 /d "NDEBUG"
# ADD RSC /l 0x404 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\asn1s.lib"

!ELSEIF  "$(CFG)" == "ASN1 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GR /GX /ZI /Od /I "." /I "../asn1" /I "../asnh323/cxx" /D "_DEBUG" /D "_LIB" /D "__WIN32__" /D "WIN32" /D "_MBCS" /D "ASN1_HAS_IOSTREAM" /D "ASN1_STATIC" /YX /FD /GZ /c
# ADD BASE RSC /l 0x404 /d "_DEBUG"
# ADD RSC /l 0x404 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\asn1sd.lib"

!ENDIF 

# Begin Target

# Name "ASN1 - Win32 Release"
# Name "ASN1 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\asn1.cxx
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\AVNDecoder.cxx
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\AVNEncoder.cxx
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\BERDecoder.cxx
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\BEREnCoder.cxx
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\CoderEnv.cxx

!IF  "$(CFG)" == "ASN1 - Win32 Release"

!ELSEIF  "$(CFG)" == "ASN1 - Win32 Debug"

# ADD CPP /Yc"asn1.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\InvalidTracer.cxx

!IF  "$(CFG)" == "ASN1 - Win32 Release"

# ADD CPP /YX

!ELSEIF  "$(CFG)" == "ASN1 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PERDecoder.cxx
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\PEREnCoder.cxx
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ValidChecker.cxx
# ADD CPP /YX
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\asn1.h
# End Source File
# Begin Source File

SOURCE=.\AssocVector.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# End Target
# End Project
