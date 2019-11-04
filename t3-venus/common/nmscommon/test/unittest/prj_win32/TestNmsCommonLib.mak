# Microsoft Developer Studio Generated NMAKE File, Based on TestNmsCommonLib.dsp
!IF "$(CFG)" == ""
CFG=TestNmsCommonLib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to TestNmsCommonLib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TestNmsCommonLib - Win32 Release" && "$(CFG)" != "TestNmsCommonLib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestNmsCommonLib - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\TestNmsCommonLib_R.exe"


CLEAN :
	-@erase "$(INTDIR)\api.obj"
	-@erase "$(INTDIR)\calladdr.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TestNmsCommonLib.obj"
	-@erase "$(INTDIR)\TestNmsCommonLib.pch"
	-@erase "$(INTDIR)\TestNmsCommonLib.res"
	-@erase "$(INTDIR)\TestNmsCommonLibDlg.obj"
	-@erase "$(INTDIR)\tplarray.obj"
	-@erase "$(INTDIR)\tplhash.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\TestNmsCommonLib_R.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /I "." /I ".\\" /I "..\include" /I "..\..\..\..\..\common\include" /I "..\..\..\..\..\..\10-Common\include\cppunit\cppunit" /I "..\..\..\..\..\..\10-Common\include\cppunit\\" /I "..\..\..\..\..\..\10-Common\include\mcu" /I "..\..\..\..\..\..\10-Common\include\platform" /I "..\..\..\..\..\..\10-Common\include\system1" /I "..\..\..\..\..\..\10-Common\include\mt" /I "..\..\..\..\..\..\10-Common\include\nms1" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\TestNmsCommonLib.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\TestNmsCommonLib.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestNmsCommonLib.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=cppunit.lib testrunner.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\TestNmsCommonLib_R.pdb" /machine:I386 /out:"$(OUTDIR)\TestNmsCommonLib_R.exe" /libpath:"..\..\..\..\..\..\10-common\lib\release\win32" /libpath:"..\..\..\..\..\..\10-common\lib\release\test" 
LINK32_OBJS= \
	"$(INTDIR)\api.obj" \
	"$(INTDIR)\calladdr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TestNmsCommonLib.obj" \
	"$(INTDIR)\TestNmsCommonLibDlg.obj" \
	"$(INTDIR)\tplarray.obj" \
	"$(INTDIR)\tplhash.obj" \
	"$(INTDIR)\TestNmsCommonLib.res"

"$(OUTDIR)\TestNmsCommonLib_R.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TestNmsCommonLib - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\TestNmsCommonLib_D.exe"


CLEAN :
	-@erase "$(INTDIR)\api.obj"
	-@erase "$(INTDIR)\calladdr.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TestNmsCommonLib.obj"
	-@erase "$(INTDIR)\TestNmsCommonLib.pch"
	-@erase "$(INTDIR)\TestNmsCommonLib.res"
	-@erase "$(INTDIR)\TestNmsCommonLibDlg.obj"
	-@erase "$(INTDIR)\tplarray.obj"
	-@erase "$(INTDIR)\tplhash.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TestNmsCommonLib_D.exe"
	-@erase "$(OUTDIR)\TestNmsCommonLib_D.ilk"
	-@erase "$(OUTDIR)\TestNmsCommonLib_D.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I ".\\" /I "..\include" /I "..\..\..\..\..\common\include" /I "..\..\..\..\..\..\10-Common\include\cppunit\cppunit" /I "..\..\..\..\..\..\10-Common\include\cppunit\\" /I "..\..\..\..\..\..\10-Common\include\mcu" /I "..\..\..\..\..\..\10-Common\include\platform" /I "..\..\..\..\..\..\10-Common\include\system1" /I "..\..\..\..\..\..\10-Common\include\mt" /I "..\..\..\..\..\..\10-Common\include\nms1" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\TestNmsCommonLib.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\TestNmsCommonLib.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestNmsCommonLib.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=cppunit.lib testrunner.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\TestNmsCommonLib_D.pdb" /debug /machine:I386 /out:"$(OUTDIR)\TestNmsCommonLib_D.exe" /pdbtype:sept /libpath:"..\..\..\..\..\..\10-common\lib\debug\win32" /libpath:"..\..\..\..\..\..\10-common\lib\debug\test" 
LINK32_OBJS= \
	"$(INTDIR)\api.obj" \
	"$(INTDIR)\calladdr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TestNmsCommonLib.obj" \
	"$(INTDIR)\TestNmsCommonLibDlg.obj" \
	"$(INTDIR)\tplarray.obj" \
	"$(INTDIR)\tplhash.obj" \
	"$(INTDIR)\TestNmsCommonLib.res"

"$(OUTDIR)\TestNmsCommonLib_D.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("TestNmsCommonLib.dep")
!INCLUDE "TestNmsCommonLib.dep"
!ELSE 
!MESSAGE Warning: cannot find "TestNmsCommonLib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TestNmsCommonLib - Win32 Release" || "$(CFG)" == "TestNmsCommonLib - Win32 Debug"
SOURCE=..\source\api.cpp

"$(INTDIR)\api.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TestNmsCommonLib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\calladdr.cpp

"$(INTDIR)\calladdr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TestNmsCommonLib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "TestNmsCommonLib - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GR /GX /O2 /I "." /I ".\\" /I "..\include" /I "..\..\..\..\..\common\include" /I "..\..\..\..\..\..\10-Common\include\cppunit\cppunit" /I "..\..\..\..\..\..\10-Common\include\cppunit\\" /I "..\..\..\..\..\..\10-Common\include\mcu" /I "..\..\..\..\..\..\10-Common\include\platform" /I "..\..\..\..\..\..\10-Common\include\system1" /I "..\..\..\..\..\..\10-Common\include\mt" /I "..\..\..\..\..\..\10-Common\include\nms1" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\TestNmsCommonLib.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TestNmsCommonLib.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TestNmsCommonLib - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I ".\\" /I "..\include" /I "..\..\..\..\..\common\include" /I "..\..\..\..\..\..\10-Common\include\cppunit\cppunit" /I "..\..\..\..\..\..\10-Common\include\cppunit\\" /I "..\..\..\..\..\..\10-Common\include\mcu" /I "..\..\..\..\..\..\10-Common\include\platform" /I "..\..\..\..\..\..\10-Common\include\system1" /I "..\..\..\..\..\..\10-Common\include\mt" /I "..\..\..\..\..\..\10-Common\include\nms1" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\TestNmsCommonLib.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TestNmsCommonLib.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\source\TestNmsCommonLib.cpp

"$(INTDIR)\TestNmsCommonLib.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TestNmsCommonLib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\TestNmsCommonLib.rc

"$(INTDIR)\TestNmsCommonLib.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=..\source\TestNmsCommonLibDlg.cpp

"$(INTDIR)\TestNmsCommonLibDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TestNmsCommonLib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\tplarray.cpp

"$(INTDIR)\tplarray.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TestNmsCommonLib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\tplhash.cpp

"$(INTDIR)\tplhash.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TestNmsCommonLib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

