# Microsoft Developer Studio Project File - Name="UIFactory" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=UIFactory - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UIFactory.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UIFactory.mak" CFG="UIFactory - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UIFactory - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "UIFactory - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "UIFactory"
# PROP Scc_LocalPath ".."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UIFactory - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "..\include" /I "..\..\common\expat\include" /I "..\include\Tinyxml" /I "..\..\..\10-common\include\nms1" /I "..\..\common\include\platform sdk\INCLUDE" /I "..\..\uiexlib\include" /I "..\..\luaplus" /I "..\..\common\include\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\10-common\lib\release\win32\uifactory.lib"

!ELSEIF  "$(CFG)" == "UIFactory - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\include" /I "..\..\common\expat\include" /I "..\include\Tinyxml" /I "..\..\..\10-common\include\nms1" /I "..\..\common\include\platform sdk\INCLUDE" /I "..\..\uiexlib\include" /I "..\..\luaplus" /I "..\..\common\include\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "COMPILED_FROM_DSP" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /X
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\10-common\lib\debug\win32\uifactory.lib"

!ENDIF 

# Begin Target

# Name "UIFactory - Win32 Release"
# Name "UIFactory - Win32 Debug"
# Begin Group "系统"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\source\System.cpp
# End Source File
# Begin Source File

SOURCE=..\include\System.h
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\nms1\templateClass.h"
# End Source File
# End Group
# Begin Group "默认的一些注册数据"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\MfcDefaultArgs.cpp
# End Source File
# Begin Source File

SOURCE=..\include\MfcDefaultArgs.h
# End Source File
# Begin Source File

SOURCE=..\source\MfcDefaultWndFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\include\MfcDefaultWndFactory.h
# End Source File
# Begin Source File

SOURCE=..\source\MfcDefaultWndProperty.cpp
# End Source File
# Begin Source File

SOURCE=..\include\MfcDefaultWndProperty.h
# End Source File
# Begin Source File

SOURCE=..\source\MfcDefaultWndPropertySet.cpp
# End Source File
# Begin Source File

SOURCE=..\include\MfcDefaultWndPropertySet.h
# End Source File
# Begin Source File

SOURCE=..\source\RegDefaultData.cpp
# End Source File
# Begin Source File

SOURCE=..\include\RegDefaultData.h
# End Source File
# Begin Source File

SOURCE=..\include\UIExLibArgs.h
# End Source File
# Begin Source File

SOURCE=..\include\UIExLibPropertySet.h
# End Source File
# Begin Source File

SOURCE=..\source\UIExLibWndFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\include\UIExLibWndFactory.h
# End Source File
# Begin Source File

SOURCE=..\include\UILibPropertySet.h
# End Source File
# Begin Source File

SOURCE=..\source\UILibWndFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\include\UILibWndFactory.h
# End Source File
# End Group
# Begin Group "公用接口"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\IValue.cpp
# End Source File
# Begin Source File

SOURCE=..\include\IValue.h
# End Source File
# Begin Source File

SOURCE=..\include\uifactorydef.h
# End Source File
# Begin Source File

SOURCE=..\include\UifactoryHeader.h
# End Source File
# End Group
# Begin Group "xml相关"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\CallBackFuncTag.cpp
# End Source File
# Begin Source File

SOURCE=..\include\CallBackFuncTag.h
# End Source File
# Begin Source File

SOURCE=..\source\DefaultXmlParser.cpp
# End Source File
# Begin Source File

SOURCE=..\include\DefaultXmlParser.h
# End Source File
# Begin Source File

SOURCE=..\source\EventTag.cpp
# End Source File
# Begin Source File

SOURCE=..\include\EventTag.h
# End Source File
# Begin Source File

SOURCE=..\source\ITag.cpp
# End Source File
# Begin Source File

SOURCE=..\include\ITag.h
# End Source File
# Begin Source File

SOURCE=..\source\ItemXmlHandle.cpp
# End Source File
# Begin Source File

SOURCE=..\include\ItemXmlHandle.h
# End Source File
# Begin Source File

SOURCE=..\source\IXmlHanlde.cpp
# End Source File
# Begin Source File

SOURCE=..\include\IXmlHanlde.h
# End Source File
# Begin Source File

SOURCE=..\source\IXmlParser.cpp
# End Source File
# Begin Source File

SOURCE=..\include\IXmlParser.h
# End Source File
# Begin Source File

SOURCE=..\source\LayoutTag.cpp
# End Source File
# Begin Source File

SOURCE=..\include\LayoutTag.h
# End Source File
# Begin Source File

SOURCE=..\source\LayoutXmlHandle.cpp
# End Source File
# Begin Source File

SOURCE=..\include\LayoutXmlHandle.h
# End Source File
# Begin Source File

SOURCE=..\source\listDataAssist.cpp
# End Source File
# Begin Source File

SOURCE=..\include\listDataAssist.h
# End Source File
# Begin Source File

SOURCE=..\source\PropertyTag.cpp
# End Source File
# Begin Source File

SOURCE=..\include\PropertyTag.h
# End Source File
# Begin Source File

SOURCE=..\source\SaveXmlHelp.cpp
# End Source File
# Begin Source File

SOURCE=..\include\SaveXmlHelp.h
# End Source File
# Begin Source File

SOURCE=..\source\SchemeHelp.cpp
# End Source File
# Begin Source File

SOURCE=..\include\SchemeHelp.h
# End Source File
# Begin Source File

SOURCE=..\source\SchemeTag.cpp
# End Source File
# Begin Source File

SOURCE=..\include\SchemeTag.h
# End Source File
# Begin Source File

SOURCE=..\source\SystemXmlHandle.cpp
# End Source File
# Begin Source File

SOURCE=..\include\SystemXmlHandle.h
# End Source File
# Begin Source File

SOURCE=..\source\WindowTag.cpp
# End Source File
# Begin Source File

SOURCE=..\include\WindowTag.h
# End Source File
# Begin Source File

SOURCE=..\source\XmlAttrib.cpp
# End Source File
# Begin Source File

SOURCE=..\include\XmlAttrib.h
# End Source File
# End Group
# Begin Group "窗口创建相关"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\ItemFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\include\ItemFactory.h
# End Source File
# Begin Source File

SOURCE=..\source\UILayoutHelp.cpp
# End Source File
# Begin Source File

SOURCE=..\include\UILayoutHelp.h
# End Source File
# Begin Source File

SOURCE=..\source\WindowFacotryManage.cpp
# End Source File
# Begin Source File

SOURCE=..\include\WindowFacotryManage.h
# End Source File
# Begin Source File

SOURCE=..\source\WindowFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\include\windowfactory.h
# End Source File
# Begin Source File

SOURCE=..\source\WindowManage.cpp
# End Source File
# Begin Source File

SOURCE=..\include\WindowManage.h
# End Source File
# Begin Source File

SOURCE=..\source\WndTreeHelp.cpp
# End Source File
# Begin Source File

SOURCE=..\include\WndTreeHelp.h
# End Source File
# End Group
# Begin Group "函数回调以及事件相应"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\CallFuncManage.cpp
# End Source File
# Begin Source File

SOURCE=..\include\CallFuncManage.h
# End Source File
# Begin Source File

SOURCE=..\source\WndMsgEventManage.cpp
# End Source File
# Begin Source File

SOURCE=..\include\WndMsgEventManage.h
# End Source File
# End Group
# Begin Group "脚本相关"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\DefaultScript.cpp
# End Source File
# Begin Source File

SOURCE=..\include\DefaultScript.h
# End Source File
# Begin Source File

SOURCE=..\source\IScript.cpp
# End Source File
# Begin Source File

SOURCE=..\include\IScript.h
# End Source File
# End Group
# Begin Group "属性相关"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\IProperty.cpp
# End Source File
# Begin Source File

SOURCE=..\include\IProperty.h
# End Source File
# Begin Source File

SOURCE=..\source\IPropertyAssist.cpp
# End Source File
# Begin Source File

SOURCE=..\include\IPropertyAssist.h
# End Source File
# Begin Source File

SOURCE=..\source\PropertyHelp.cpp
# End Source File
# Begin Source File

SOURCE=..\include\PropertyHelp.h
# End Source File
# Begin Source File

SOURCE=..\source\PropertySet.cpp
# End Source File
# Begin Source File

SOURCE=..\include\PropertySet.h
# End Source File
# End Group
# Begin Group "日志相关"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\DefaultLogger.cpp
# End Source File
# Begin Source File

SOURCE=..\include\DefaultLogger.h
# End Source File
# Begin Source File

SOURCE=..\source\Logger.cpp
# End Source File
# Begin Source File

SOURCE=..\include\Logger.h
# End Source File
# End Group
# Begin Group "TinyXml"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\Tinyxml\tinystr.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\include\Tinyxml\tinystr.h
# End Source File
# Begin Source File

SOURCE=..\include\Tinyxml\tinyxml.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\include\Tinyxml\tinyxml.h
# End Source File
# Begin Source File

SOURCE=..\include\Tinyxml\tinyxmlerror.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\include\Tinyxml\tinyxmlparser.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "Observer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\SystemInfoManage.cpp
# End Source File
# Begin Source File

SOURCE=..\include\SystemInfoManage.h
# End Source File
# Begin Source File

SOURCE=..\source\UILoadManage.cpp
# End Source File
# Begin Source File

SOURCE=..\include\UILoadManage.h
# End Source File
# Begin Source File

SOURCE=..\source\WindowTypeManage.cpp
# End Source File
# Begin Source File

SOURCE=..\include\WindowTypeManage.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# Begin Source File

SOURCE=..\source\uifactorylib.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\include\uifactorylib.h
# End Source File
# End Target
# End Project
