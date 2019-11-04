# Microsoft Developer Studio Project File - Name="cnsToolDll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=cnsToolDll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cnsToolDll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cnsToolDll.mak" CFG="cnsToolDll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cnsToolDll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "cnsToolDll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "cnsToolDll"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cnsToolDll - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../prj_win32/Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I ".\\" /I "..\include" /I "..\..\..\common\include" /I "..\..\..\..\10-common\include\nms1" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\protocol" /I "..\..\..\..\10-common\include\platform" /I "..\..\..\..\10-common\include\tp" /I "..\..\..\common\include\platform sdk\include" /I "..\..\..\UIFactory\include" /I "..\..\..\uiexlib\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "CNSTOOLDLL_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /map /machine:I386 /nodefaultlib:"nafxcw" /nodefaultlib:"nafxcwd" /nodefaultlib:"libcd" /nodefaultlib:"libc" /nodefaultlib:"libcmt" /nodefaultlib:"msvcrtd" /nodefaultlib:"Imm32.lib" /nodefaultlib:"libcmtd.lib" /nodefaultlib:"strmiids.lib" /libpath:"..\..\..\..\10-common\lib\release\win32" /libpath:"..\..\..\..\10-common\lib\release\win32_2010" /libpath:"..\..\..\common\include\platform sdk\lib" /mapinfo:lines
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "cnsToolDll - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../prj_win32/debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I ".\\" /I "..\include" /I "..\..\..\common\include" /I "..\..\..\..\10-common\include\nms1" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\protocol" /I "..\..\..\..\10-common\include\platform" /I "..\..\..\..\10-common\include\tp" /I "..\..\..\common\include\platform sdk\include" /I "..\..\..\UIFactory\include" /I "..\..\..\uiexlib\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CNSTOOLDLL_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"nafxcwd.lib" /nodefaultlib:"libcd.lib" /pdbtype:sept /libpath:"..\..\..\..\10-common\lib\debug\win32" /libpath:"..\..\..\..\10-common\lib\debug\win32_2010" /libpath:"..\..\..\common\include\platform sdk\lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "cnsToolDll - Win32 Release"
# Name "cnsToolDll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "logic_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\addrbookExpLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\BasicInfoLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cameraLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\CentCfgCameraDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\centCfgDisplayDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\CentCfgFrameLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\centCtrlLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cfgAdjustImageDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\CfgAdvanceDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cfgAudioDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cfgAudioPortLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cfgCallSerLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cfgCnsFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\source\CfgCnsLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cfgDemonStrationDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\CfgDiagnosticFrameLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cfgEqLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cfgFrameLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cfgMainAudioDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cfgMixLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cfgnetmngLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cfgNetSecurityLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cfgServerLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\diagInfoLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\DiagInterfaceLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\diagTestFrameLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\diagTestInfoLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\expcommonLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\impcommonLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\mainFrameLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\msgBoxLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\NetDiagnosticLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\netmngoptdlgLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\NetPacketLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\recordOptDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\renameOptDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\routeCfgdlgLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\warningLogic.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\source\cnclibcommonif.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cnclibdatamgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cnsToolDll.cpp
# End Source File
# Begin Source File

SOURCE=.\cnsToolDll.def
# End Source File
# Begin Source File

SOURCE=.\cnsToolDll.rc
# End Source File
# Begin Source File

SOURCE=..\source\cnsToolDllIF.cpp
# End Source File
# Begin Source File

SOURCE=..\source\confsign.cpp
# End Source File
# Begin Source File

SOURCE=..\source\listAssist.cpp
# End Source File
# Begin Source File

SOURCE=..\source\logicBase.cpp
# End Source File
# Begin Source File

SOURCE=..\source\logicMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\msgdispatch.cpp
# End Source File
# Begin Source File

SOURCE=..\source\sessionmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\source\telnetsocket.cpp
# End Source File
# Begin Source File

SOURCE=..\source\uiDataMgr.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "logic_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\addrbookExpLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\BasicInfoLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\cameraLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\CentCfgCameraDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\centCfgDisplayDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\CentCfgFrameLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\centCtrlLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\cfgAdjustImageDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\CfgAdvanceDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\cfgAudioDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\cfgAudioPortLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\cfgCallSerLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\cfgCnsFrame.h
# End Source File
# Begin Source File

SOURCE=..\include\CfgCnsLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\cfgDemonStrationDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\CfgDiagnosticFrameLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\cfgEqLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\cfgFrameLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\cfgMainAudioDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\cfgMixLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\cfgnetmngLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\cfgNetSecurityLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\cfgServerLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\diagInfoLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\DiagInterfaceLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\diagTestFrameLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\diagTestInfoLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\expcommonLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\impcommonLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\MainFrameLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\msgBoxLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\NetDiagnosticLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\netmngoptdlgLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\NetPacketLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\recordOptDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\renameOptDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\routeCfgdlgLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\warningLogic.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\include\cnclibcommonif.h
# End Source File
# Begin Source File

SOURCE=..\include\cnclibdatamgr.h
# End Source File
# Begin Source File

SOURCE=..\include\cnsToolDll.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\cnsToolDllIF.h
# End Source File
# Begin Source File

SOURCE=..\include\confsign.h
# End Source File
# Begin Source File

SOURCE=..\include\globaldefine.h
# End Source File
# Begin Source File

SOURCE=..\include\listAssist.h
# End Source File
# Begin Source File

SOURCE=..\include\logicBase.h
# End Source File
# Begin Source File

SOURCE=..\include\logicMgr.h
# End Source File
# Begin Source File

SOURCE=..\include\msgdispatch.h
# End Source File
# Begin Source File

SOURCE=..\include\netcapture.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\include\sessionmgr.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\include\telnetsocket.h
# End Source File
# Begin Source File

SOURCE=..\include\uidatamgr.h
# End Source File
# Begin Source File

SOURCE=..\include\uiDataType.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\cnsToolDll.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
