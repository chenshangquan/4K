# Microsoft Developer Studio Project File - Name="umclib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=umclib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "umclib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "umclib.mak" CFG="umclib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "umclib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "umclib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "umclib"
# PROP Scc_LocalPath "..\..\..\.."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "umclib - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "..\include" /I "..\source" /I "..\..\common\include" /I "..\..\common\source" /I "..\..\..\..\10-common\include\um" /I "..\..\..\..\10-common\include\radstack" /I "..\..\..\..\10-common\include\platform" /I "..\..\..\..\10-common\include\mt" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\nms1" /I "..\..\..\..\10-common\include\snmp" /I "..\..\..\..\10-common\include\protocol" /I "..\..\..\..\10-common\include\tp" /I "..\..\..\common\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\..\10-common\lib\release\win32\umclib.lib"

!ELSEIF  "$(CFG)" == "umclib - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\10-common\lib\debug\win32"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I ".\\" /I "..\include" /I "..\source" /I "..\..\common\include" /I "..\..\common\source" /I "..\..\..\common\include" /I "..\..\..\..\10-common\include\um" /I "..\..\..\..\10-common\include\radstack" /I "..\..\..\..\10-common\include\platform" /I "..\..\..\..\10-common\include\mt" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\nms1" /I "..\..\..\..\10-common\include\snmp" /I "..\..\..\..\10-common\include\protocol" /I "..\..\..\..\10-common\include\tp" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "umclib - Win32 Release"
# Name "umclib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "commom"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\common\source\commandqueue.cpp
# End Source File
# Begin Source File

SOURCE=..\source\confTemplateCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\source\kdvDispEvent.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\source\addrmsgdriver.cpp
# End Source File
# Begin Source File

SOURCE=..\source\confCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\source\msgdriver.cpp
# End Source File
# Begin Source File

SOURCE=..\source\ospmsgrecver.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\source\tvwCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umclib.cpp
# End Source File
# Begin Source File

SOURCE=..\source\ummsysInfoCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsboardCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsConfigCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsexportCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsnetmngCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsSession.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umstvwboardCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsVTRCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umswebaddrbook.cpp
# End Source File
# Begin Source File

SOURCE=..\source\userCtrl.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "70_common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\common\include\cmsConst.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\evCmsLib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\kdvDispEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\umsboardCtrlIF.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\umsexportCtrlIF.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\umssysinfoCtrlIF.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\umstvwboardCtrlIF.h
# End Source File
# End Group
# Begin Group "10-common"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\..\..\10-common\include\tp\eventoutcnsmp.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\tp\eventoutumsboard.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\tp\eventoutumscall.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\tp\eventoutumscfg.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\tp\eventoutumsconftemplate.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\tp\eventoutumshdu2.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\tp\eventoutumslogin.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\tp\eventoutumsreg.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\tp\eventoutumstool.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\tp\tpstruct.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\tp\tpsys.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\tp\tptype.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\tp\umshduevent.h"
# End Source File
# End Group
# Begin Group "common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\common\include\commandqueue.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\include\addrmsgdriver.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\cmsstruct.h
# End Source File
# Begin Source File

SOURCE=..\include\confCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\confCtrlIF.h
# End Source File
# Begin Source File

SOURCE=..\include\confTemplateCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\confTemplateCtrlIF.h
# End Source File
# Begin Source File

SOURCE=..\include\msgdriver.h
# End Source File
# Begin Source File

SOURCE=..\include\ospmsgrecver.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\include\tvwCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\tvwCtrlIF.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\umclib.h
# End Source File
# Begin Source File

SOURCE=..\include\umsboardCtrl.h
# End Source File
# Begin Source File

SOURCE=..\include\umsConfigCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\umsConfigCtrlIF.h
# End Source File
# Begin Source File

SOURCE=..\include\umsexportCtrl.h
# End Source File
# Begin Source File

SOURCE=..\include\umsNetMngCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\umsNetMngCtrlIF.h
# End Source File
# Begin Source File

SOURCE=..\include\umsSession.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\umsSessionCtrlIF.h
# End Source File
# Begin Source File

SOURCE=..\include\umssysinfoCtrl.h
# End Source File
# Begin Source File

SOURCE=..\include\umstvwboardCtrl.h
# End Source File
# Begin Source File

SOURCE=..\include\umsVTRCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\umsVTRCtrlIF.h
# End Source File
# Begin Source File

SOURCE=..\include\userCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\userCtrlIF.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# End Target
# End Project
