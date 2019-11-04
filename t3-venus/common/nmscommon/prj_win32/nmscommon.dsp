# Microsoft Developer Studio Project File - Name="NmsCommon" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=NmsCommon - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "nmscommon.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nmscommon.mak" CFG="NmsCommon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NmsCommon - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "NmsCommon - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "NmsCommon"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NmsCommon - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\platform" /I "..\..\..\..\10-common\include\nms1" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\..\10-common\lib\release\win32\nmscommon.lib"

!ELSEIF  "$(CFG)" == "NmsCommon - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\include" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\platform" /I "..\..\..\..\10-common\include\nms1" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\..\10-common\lib\debug\win32\nmscommon.lib"

!ENDIF 

# Begin Target

# Name "NmsCommon - Win32 Release"
# Name "NmsCommon - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\source\CallAddr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\chartoPY.cpp
# End Source File
# Begin Source File

SOURCE=..\source\FtpCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\source\LogManage.cpp
# End Source File
# Begin Source File

SOURCE=..\source\NmsCommon.cpp
# End Source File
# Begin Source File

SOURCE=..\source\parsecfgfile.cpp
# End Source File
# Begin Source File

SOURCE=..\source\Ping.cpp
# End Source File
# Begin Source File

SOURCE=..\source\printctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\source\TraceRT.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE="..\..\..\..\10-common\include\nms1\CallAddr.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\nms1\chartoPY.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\nms1\FtpCtrl.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\nms1\HexAsciiString.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\nms1\IcmpStruct.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\nms1\LogManage.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-Common\include\nms1\NmsCommon.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\nms1\parsecfgfile.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\nms1\Ping.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\nms1\printctrl.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\nms1\TplArray.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\nms1\TplHash.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-common\include\nms1\TraceRT.h"
# End Source File
# End Group
# Begin Group "Readme Files"

# PROP Default_Filter "txt;mak;bat"
# Begin Source File

SOURCE=.\Compile.bat
# End Source File
# Begin Source File

SOURCE=.\NmsCommon.mak
# End Source File
# Begin Source File

SOURCE=..\ReadMe.txt
# End Source File
# End Group
# End Target
# End Project
