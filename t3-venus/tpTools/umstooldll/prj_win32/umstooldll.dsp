# Microsoft Developer Studio Project File - Name="umstooldll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=umstooldll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "umstooldll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "umstooldll.mak" CFG="umstooldll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "umstooldll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "umstooldll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "umstooldll"
# PROP Scc_LocalPath ".."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "umstooldll - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\prj_win32\Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /ZI /Od /I ".\\" /I "..\include" /I "..\..\..\common\include" /I "..\..\..\..\10-common\include\nms1" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\protocol" /I "..\..\..\..\10-common\include\platform" /I "..\..\..\common\include\platform sdk\include" /I "..\..\..\..\10-common\include\tp" /I "..\..\..\UIFactory\include" /I "..\..\..\uiexlib\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 umclib.lib osplib.lib kdvsys.lib kdvaddrbook.lib nmscommon.lib umsmsg.lib xmlengine.lib tpmsgmgr.lib kdvlog.lib uiex.lib UIFactory.lib tinyxml.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"nafxcw" /nodefaultlib:"nafxcwd" /nodefaultlib:"libcd" /nodefaultlib:"libc" /nodefaultlib:"libcmt" /nodefaultlib:"msvcrtd" /nodefaultlib:"Imm32.lib" /nodefaultlib:"libcmtd.lib" /nodefaultlib:"strmiids.lib" /libpath:"..\..\..\..\10-common\lib\release\win32" /libpath:"..\..\..\common\include\platform sdk\LIB"

!ELSEIF  "$(CFG)" == "umstooldll - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\prj_win32\Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I ".\\" /I "..\include" /I "..\..\..\common\include" /I "..\..\..\..\10-common\include\nms1" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\protocol" /I "..\..\..\..\10-common\include\platform" /I "..\..\..\common\include\platform sdk\include" /I "..\..\..\..\10-common\include\tp" /I "..\..\..\UIFactory\include" /I "..\..\..\uiexlib\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 umclib.lib osplib.lib kdvsys.lib kdvaddrbook.lib nmscommon.lib umsmsg.lib xmlengine.lib tpmsgmgr.lib kdvlog.lib uiex.lib UIFactory.lib tinyxml.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"nafxcwd.lib" /pdbtype:sept /libpath:"..\..\..\..\10-common\lib\debug\win32" /libpath:"..\..\..\common\include\platform sdk\LIB"

!ENDIF 

# Begin Target

# Name "umstooldll - Win32 Release"
# Name "umstooldll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "common_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\msgdispatch.cpp
# End Source File
# Begin Source File

SOURCE=..\source\msghandle.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umstoolcommon.cpp
# End Source File
# End Group
# Begin Group "ui_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\touchlistdataproperty.cpp
# End Source File
# Begin Source File

SOURCE=..\source\wndlogicbase.cpp
# End Source File
# End Group
# Begin Group "logic_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\addrbookexplogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\backupcfglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\boardcfglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\boardoptdlglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\correlativecfglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\expcommondlglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\impcommondlglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\logicmanage.cpp
# End Source File
# Begin Source File

SOURCE=..\source\mainFrameLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\msgboxdlglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\netmngcfglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\netmngoptdlglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\sysinfologic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\templateexplogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\tvwboardcfglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\tvwstylecfglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\tvwstyleoptdlglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umscfglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\vtrcfglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\vtroptdlglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\warninglogic.cpp
# End Source File
# End Group
# Begin Group "business_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\umsboardcommmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsconfigcommmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsnetmngcommmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umssysinfocommmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umstvwboardcommmgr.cpp
# End Source File
# End Group
# Begin Group "modual_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\commonmgrif.cpp
# End Source File
# Begin Source File

SOURCE=..\source\datamgrimp.cpp
# End Source File
# Begin Source File

SOURCE=..\source\sessionins.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\source\umstooldll.cpp
# End Source File
# Begin Source File

SOURCE=.\umstooldll.def
# End Source File
# Begin Source File

SOURCE=.\umstooldll.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "common_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\globaldef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\globalumstool.h
# End Source File
# Begin Source File

SOURCE=..\include\msgdispatch.h
# End Source File
# Begin Source File

SOURCE=..\include\msghandle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\tptooldef.h
# End Source File
# Begin Source File

SOURCE=..\include\umstoolcommon.h
# End Source File
# End Group
# Begin Group "ui_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\touchlistdataproperty.h
# End Source File
# Begin Source File

SOURCE=..\include\wndlogicbase.h
# End Source File
# End Group
# Begin Group "logic_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\addrbookexplogic.h
# End Source File
# Begin Source File

SOURCE=..\include\backupcfglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\boardcfglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\boardoptdlglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\correlativecfglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\expcommondlglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\impcommondlglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\logicmanage.h
# End Source File
# Begin Source File

SOURCE=..\include\mainFrameLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\msgboxdlglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\netmngcfglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\netmngoptdlglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\sysinfologic.h
# End Source File
# Begin Source File

SOURCE=..\include\templateexplogic.h
# End Source File
# Begin Source File

SOURCE=..\include\tvwboardcfglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\tvwstylecfglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\tvwstyleoptdlglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\umscfglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\vtrcfglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\vtroptdlglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\warninglogic.h
# End Source File
# End Group
# Begin Group "business_h"

# PROP Default_Filter ""
# End Group
# Begin Group "modual_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\commonmgrif.h
# End Source File
# Begin Source File

SOURCE=..\include\datamgrimp.h
# End Source File
# Begin Source File

SOURCE=..\include\sessionins.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\include\umstooldll.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\umstooldll.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
