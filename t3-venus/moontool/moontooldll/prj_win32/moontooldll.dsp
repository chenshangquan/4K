# Microsoft Developer Studio Project File - Name="moontooldll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=moontooldll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "moontooldll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "moontooldll.mak" CFG="moontooldll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "moontooldll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "moontooldll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "moontooldll - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I ".\\" /I "..\include" /I "..\..\..\common\include" /I "..\..\..\..\10-common\include\nms1" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\protocol" /I "..\..\..\..\10-common\include\platform" /I "..\..\..\..\10-common\include\tp2" /I "..\..\..\common\include\platform sdk\include" /I "..\..\..\UIFactory\include" /I "..\..\..\uiexlib\include" /I "..\..\..\common\include\rk100_tp" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MOONTOOLDLL_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Z<none> /X
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /map /machine:I386 /nodefaultlib:"nafxcw.lib" /nodefaultlib:"libc.lib" /libpath:"..\..\..\..\10-common\lib\release\win32" /libpath:"..\..\..\common\include\platform sdk\lib"
# SUBTRACT LINK32 /incremental:yes /debug

!ELSEIF  "$(CFG)" == "moontooldll - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I ".\\" /I "..\include" /I "..\..\..\common\include" /I "..\..\..\..\10-common\include\nms1" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\protocol" /I "..\..\..\..\10-common\include\platform" /I "..\..\..\..\10-common\include\tp2" /I "..\..\..\common\include\platform sdk\include" /I "..\..\..\UIFactory\include" /I "..\..\..\uiexlib\include" /I "..\..\..\common\include\rk100_tp" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "MOONTOOLDLL_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"nafxcwd.lib" /nodefaultlib:"libcd.lib" /pdbtype:sept /libpath:"..\..\..\..\10-common\lib\debug\win32" /libpath:"..\..\..\common\include\platform sdk\lib"

!ENDIF 

# Begin Target

# Name "moontooldll - Win32 Release"
# Name "moontooldll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "logic_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\cameractrlLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\COrderListDlgLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\CorrectParamLogic.cpp
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

SOURCE=..\source\MoonAdjustDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\OrderPosInfoLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\SetContrastAreaLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\SysCfgDlgLogic.cpp
# End Source File
# End Group
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

SOURCE=..\source\moonlibcommonif.cpp
# End Source File
# Begin Source File

SOURCE=..\source\moonlibdatamgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\moontooldll.cpp
# End Source File
# Begin Source File

SOURCE=.\moontooldll.def
# End Source File
# Begin Source File

SOURCE=.\moontooldll.rc
# End Source File
# Begin Source File

SOURCE=..\source\moonToolDllIF.cpp
# End Source File
# Begin Source File

SOURCE=..\source\msgBoxLogic.cpp
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

SOURCE=..\source\uiDataMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\warningLogic.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "logic_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\cameractrlLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\CorrectParamLogic.h
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

SOURCE=..\include\MoonAdjustDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\OrderListDlgLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\OrderPosInfoLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\SetContrastAreaLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\SysCfgDlgLogic.h
# End Source File
# End Group
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

SOURCE=..\include\moonlibcommonif.h
# End Source File
# Begin Source File

SOURCE=..\include\moonlibdatamgr.h
# End Source File
# Begin Source File

SOURCE=..\include\moontooldll.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\moonToolDllIF.h
# End Source File
# Begin Source File

SOURCE=..\include\msgBoxLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\msgdispatch.h
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

SOURCE=..\include\uiDataMgr.h
# End Source File
# Begin Source File

SOURCE=..\include\uiDataType.h
# End Source File
# Begin Source File

SOURCE=..\include\warningLogic.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\moontooldll.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
