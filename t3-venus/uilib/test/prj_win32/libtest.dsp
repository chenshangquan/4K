# Microsoft Developer Studio Project File - Name="LibTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=LibTest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LibTest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LibTest.mak" CFG="LibTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LibTest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "LibTest - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "LibTest"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LibTest - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /I "..\include" /I "..\..\..\10-Common\include\nms1" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /D /O2/I "..\..\..\10-Common\include\nms1" /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "LibTest - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "..\..\..\..\10-Common/include/nms1" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /I /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\..\..\10-Common\lib\debug\win32\UILib.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "LibTest - Win32 Release"
# Name "LibTest - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\Source\LibTest.cpp
# End Source File
# Begin Source File

SOURCE=.\LibTest.rc
# End Source File
# Begin Source File

SOURCE=..\Source\LibTestDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\listtestdlg.cpp
# ADD CPP /I "..\project"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Include\LibTest.h
# End Source File
# Begin Source File

SOURCE=..\Include\LibTestDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\listtestdlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\10-Common\include\nms1\UILibHead.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\b1down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\b1gray.bmp
# End Source File
# Begin Source File

SOURCE=.\res\b1mask.bmp
# End Source File
# Begin Source File

SOURCE=.\res\b1norm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LibTest.ico
# End Source File
# Begin Source File

SOURCE=.\res\LibTest.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Sky.bmp
# End Source File
# Begin Source File

SOURCE=".\res\»¬¶¯MENU1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\»®Ìõµ×ÎÆ.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\¾²Òô.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\À®°È1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\À®°È2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\À®°È3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Âó¿Ë·ç1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Âó¿Ë·ç2 ¿½±´.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Âó¿Ë·ç2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Âó¿Ë·ç3 ¿½±´.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Âó¿Ë·ç3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ÑÆÒô.bmp"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
