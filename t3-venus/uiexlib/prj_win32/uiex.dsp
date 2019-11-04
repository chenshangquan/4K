# Microsoft Developer Studio Project File - Name="uiex" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=uiex - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "uiex.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "uiex.mak" CFG="uiex - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "uiex - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "uiex - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "uiex"
# PROP Scc_LocalPath ".."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "uiex - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "..\include" /I "..\..\..\10-common\include\nms1" /I "..\..\common\include\platform sdk\INCLUDE" /I "..\..\common\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\10-common\lib\release\win32\uiex.lib"

!ELSEIF  "$(CFG)" == "uiex - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\include" /I "..\..\..\10-common\include\nms1" /I "..\..\common\include\platform sdk\INCLUDE" /I "..\..\common\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\10-common\lib\debug\win32\uiex.lib"

!ENDIF 

# Begin Target

# Name "uiex - Win32 Release"
# Name "uiex - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\source\BaseWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\source\BitmapHelp.cpp
# End Source File
# Begin Source File

SOURCE=..\source\dragwindow.cpp
# End Source File
# Begin Source File

SOURCE=..\source\IAlgorithm.cpp
# End Source File
# Begin Source File

SOURCE=..\source\IBaseItem.cpp
# End Source File
# Begin Source File

SOURCE=..\source\IList.cpp
# End Source File
# Begin Source File

SOURCE=..\source\item.cpp
# End Source File
# Begin Source File

SOURCE=..\source\LetterIndex.cpp
# End Source File
# Begin Source File

SOURCE=..\source\listfuncmanage.cpp
# End Source File
# Begin Source File

SOURCE=..\source\SrcManage.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\source\TransparentBaseWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentBtn.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentCalendar.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentCheckButton.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentComboBox.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\transparentDlgBase.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentDragButton.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentHoriList.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentList.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentListHoriSlider.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentListSlider.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentProgress.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentSlideBlock.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentSliderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\source\transparentSliderWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentStatic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentSwitchButton.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentViewList.cpp
# End Source File
# Begin Source File

SOURCE=..\source\VirtualBattery.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\algorithm.h
# End Source File
# Begin Source File

SOURCE=..\include\baseWnd.h
# End Source File
# Begin Source File

SOURCE=..\include\bitmapHelp.h
# End Source File
# Begin Source File

SOURCE=..\include\button.h
# End Source File
# Begin Source File

SOURCE=..\include\calendar.h
# End Source File
# Begin Source File

SOURCE=..\include\combobox.h
# End Source File
# Begin Source File

SOURCE=..\include\dragWindow.h
# End Source File
# Begin Source File

SOURCE=..\include\edit.h
# End Source File
# Begin Source File

SOURCE=..\include\iAlgorithm.h
# End Source File
# Begin Source File

SOURCE=..\include\iBaseItem.h
# End Source File
# Begin Source File

SOURCE=..\include\iList.h
# End Source File
# Begin Source File

SOURCE=..\include\item.h
# End Source File
# Begin Source File

SOURCE=..\include\letterIndex.h
# End Source File
# Begin Source File

SOURCE=..\include\list.h
# End Source File
# Begin Source File

SOURCE=..\include\listfuncmanage.h
# End Source File
# Begin Source File

SOURCE=..\include\progress.h
# End Source File
# Begin Source File

SOURCE=..\include\slider.h
# End Source File
# Begin Source File

SOURCE=..\include\srcManage.h
# End Source File
# Begin Source File

SOURCE=..\include\static.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\nms1\templateClass.h"
# End Source File
# Begin Source File

SOURCE=..\include\transparenBaseWnd.h
# End Source File
# Begin Source File

SOURCE=..\include\TransparentDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\transparentDlgBase.h
# End Source File
# Begin Source File

SOURCE=..\include\TransparentHoriList.h
# End Source File
# Begin Source File

SOURCE=..\include\TransparentListHoriSlider.h
# End Source File
# Begin Source File

SOURCE=..\include\TransparentListSlider.h
# End Source File
# Begin Source File

SOURCE=..\include\TransparentViewList.h
# End Source File
# Begin Source File

SOURCE=..\include\uiexBaseData.h
# End Source File
# Begin Source File

SOURCE=..\..\common\include\uiexhead.h
# End Source File
# Begin Source File

SOURCE=..\include\virtualBattery.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# End Target
# End Project
