# Microsoft Developer Studio Project File - Name="TestNmsCommonLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TestNmsCommonLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestNmsCommonLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestNmsCommonLib.mak" CFG="TestNmsCommonLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestNmsCommonLib - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TestNmsCommonLib - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "TestNmsCommonLib"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestNmsCommonLib - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "." /I ".\\" /I "..\include" /I "..\..\..\..\..\common\include" /I "..\..\..\..\..\..\10-Common\include\cppunit\cppunit" /I "..\..\..\..\..\..\10-Common\include\cppunit\\" /I "..\..\..\..\..\..\10-Common\include\mcu" /I "..\..\..\..\..\..\10-Common\include\platform" /I "..\..\..\..\..\..\10-Common\include\system1" /I "..\..\..\..\..\..\10-Common\include\mt" /I "..\..\..\..\..\..\10-Common\include\nms1" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 cppunit.lib testrunner.lib /nologo /subsystem:windows /machine:I386 /out:"Release/TestNmsCommonLib_R.exe" /libpath:"..\..\..\..\..\..\10-common\lib\release\win32" /libpath:"..\..\..\..\..\..\10-common\lib\release\test"

!ELSEIF  "$(CFG)" == "TestNmsCommonLib - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I ".\\" /I "..\include" /I "..\..\..\..\..\common\include" /I "..\..\..\..\..\..\10-Common\include\cppunit\cppunit" /I "..\..\..\..\..\..\10-Common\include\cppunit\\" /I "..\..\..\..\..\..\10-Common\include\mcu" /I "..\..\..\..\..\..\10-Common\include\platform" /I "..\..\..\..\..\..\10-Common\include\system1" /I "..\..\..\..\..\..\10-Common\include\mt" /I "..\..\..\..\..\..\10-Common\include\nms1" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 cppunit.lib testrunner.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/TestNmsCommonLib_D.exe" /pdbtype:sept /libpath:"..\..\..\..\..\..\10-common\lib\debug\win32" /libpath:"..\..\..\..\..\..\10-common\lib\debug\test"

!ENDIF 

# Begin Target

# Name "TestNmsCommonLib - Win32 Release"
# Name "TestNmsCommonLib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\source\api.cpp
# End Source File
# Begin Source File

SOURCE=..\source\calladdr.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\source\TestNmsCommonLib.cpp
# End Source File
# Begin Source File

SOURCE=.\TestNmsCommonLib.rc
# End Source File
# Begin Source File

SOURCE=..\source\TestNmsCommonLibDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\tplarray.cpp
# End Source File
# Begin Source File

SOURCE=..\source\tplhash.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\api.h
# End Source File
# Begin Source File

SOURCE=..\include\calladdr.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\include\TestNmsCommonLib.h
# End Source File
# Begin Source File

SOURCE=..\include\TestNmsCommonLibDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\tplarray.h
# End Source File
# Begin Source File

SOURCE=..\include\tplhash.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\TestNmsCommonLib.ico
# End Source File
# Begin Source File

SOURCE=.\res\TestNmsCommonLib.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\compile.bat
# End Source File
# Begin Source File

SOURCE=..\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\TestNmsCommonLib.mak
# End Source File
# End Target
# End Project
