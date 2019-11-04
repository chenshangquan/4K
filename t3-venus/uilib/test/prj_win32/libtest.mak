# Microsoft Developer Studio Generated NMAKE File, Based on LibTest.dsp
!IF "$(CFG)" == ""
CFG=LibTest - Win32 Debug
!MESSAGE No configuration specified. Defaulting to LibTest - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "LibTest - Win32 Release" && "$(CFG)" != "LibTest - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "LibTest - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\LibTest.exe"

!ELSE 

ALL : "UILib - Win32 Release" "$(OUTDIR)\LibTest.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"UILib - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\LibTest.obj"
	-@erase "$(INTDIR)\LibTest.pch"
	-@erase "$(INTDIR)\LibTest.res"
	-@erase "$(INTDIR)\LibTestDlg.obj"
	-@erase "$(INTDIR)\listtestdlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LibTest.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /I "..\include" /I "..\..\..\10-Common\include\nms1" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\LibTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /D /O2/I "..\..\..\10-Common\include\nms1" /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\LibTest.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LibTest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\LibTest.pdb" /machine:I386 /out:"$(OUTDIR)\LibTest.exe" 
LINK32_OBJS= \
	"$(INTDIR)\LibTest.obj" \
	"$(INTDIR)\LibTestDlg.obj" \
	"$(INTDIR)\listtestdlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LibTest.res" \
	"..\..\project\Release\UILib.lib"

"$(OUTDIR)\LibTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LibTest - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\LibTest.exe" "$(OUTDIR)\LibTest.bsc"

!ELSE 

ALL : "UILib - Win32 Debug" "$(OUTDIR)\LibTest.exe" "$(OUTDIR)\LibTest.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"UILib - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\LibTest.obj"
	-@erase "$(INTDIR)\LibTest.pch"
	-@erase "$(INTDIR)\LibTest.res"
	-@erase "$(INTDIR)\LibTest.sbr"
	-@erase "$(INTDIR)\LibTestDlg.obj"
	-@erase "$(INTDIR)\LibTestDlg.sbr"
	-@erase "$(INTDIR)\listtestdlg.obj"
	-@erase "$(INTDIR)\listtestdlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LibTest.bsc"
	-@erase "$(OUTDIR)\LibTest.exe"
	-@erase "$(OUTDIR)\LibTest.ilk"
	-@erase "$(OUTDIR)\LibTest.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "..\..\..\..\10-Common/include/nms1" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LibTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /I /GZ /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\LibTest.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LibTest.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\LibTest.sbr" \
	"$(INTDIR)\LibTestDlg.sbr" \
	"$(INTDIR)\listtestdlg.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\LibTest.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=..\..\..\..\10-Common\lib\debug\win32\UILib.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\LibTest.pdb" /debug /machine:I386 /out:"$(OUTDIR)\LibTest.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\LibTest.obj" \
	"$(INTDIR)\LibTestDlg.obj" \
	"$(INTDIR)\listtestdlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LibTest.res" \
	"..\..\..\..\10-Common\lib\debug\win32\UILib.lib"

"$(OUTDIR)\LibTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("LibTest.dep")
!INCLUDE "LibTest.dep"
!ELSE 
!MESSAGE Warning: cannot find "LibTest.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "LibTest - Win32 Release" || "$(CFG)" == "LibTest - Win32 Debug"
SOURCE=..\Source\LibTest.cpp

!IF  "$(CFG)" == "LibTest - Win32 Release"


"$(INTDIR)\LibTest.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibTest.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LibTest - Win32 Debug"


"$(INTDIR)\LibTest.obj"	"$(INTDIR)\LibTest.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibTest.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\LibTest.rc

"$(INTDIR)\LibTest.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=..\Source\LibTestDlg.cpp

!IF  "$(CFG)" == "LibTest - Win32 Release"


"$(INTDIR)\LibTestDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibTest.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LibTest - Win32 Debug"


"$(INTDIR)\LibTestDlg.obj"	"$(INTDIR)\LibTestDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibTest.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\listtestdlg.cpp

!IF  "$(CFG)" == "LibTest - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /I "..\include" /I "..\..\..\10-Common\include\nms1" /I "..\project" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\LibTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /D /O2/I "..\..\..\10-Common\include\nms1" /c 

"$(INTDIR)\listtestdlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibTest.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LibTest - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "..\..\..\..\10-Common/include/nms1" /I "..\project" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LibTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /I /GZ /c 

"$(INTDIR)\listtestdlg.obj"	"$(INTDIR)\listtestdlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibTest.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "LibTest - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /I "..\include" /I "..\..\..\10-Common\include\nms1" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\LibTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /D /O2/I "..\..\..\10-Common\include\nms1" /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LibTest.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LibTest - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "..\..\..\..\10-Common/include/nms1" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LibTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /I /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\LibTest.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "LibTest - Win32 Release"

"UILib - Win32 Release" : 
   cd "\CCroot\zhuyunrong2_KDV30_dev\KDV30_VOB\70-nms1\UILib\project"
   $(MAKE) /$(MAKEFLAGS) /F ".\UILib.mak" CFG="UILib - Win32 Release" 
   cd "..\test\project"

"UILib - Win32 ReleaseCLEAN" : 
   cd "\CCroot\zhuyunrong2_KDV30_dev\KDV30_VOB\70-nms1\UILib\project"
   $(MAKE) /$(MAKEFLAGS) /F ".\UILib.mak" CFG="UILib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\test\project"

!ELSEIF  "$(CFG)" == "LibTest - Win32 Debug"

"UILib - Win32 Debug" : 
   cd "\CCroot\zhuyunrong2_KDV30_dev\KDV30_VOB\70-nms1\UILib\project"
   $(MAKE) /$(MAKEFLAGS) /F ".\UILib.mak" CFG="UILib - Win32 Debug" 
   cd "..\test\project"

"UILib - Win32 DebugCLEAN" : 
   cd "\CCroot\zhuyunrong2_KDV30_dev\KDV30_VOB\70-nms1\UILib\project"
   $(MAKE) /$(MAKEFLAGS) /F ".\UILib.mak" CFG="UILib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\test\project"

!ENDIF 


!ENDIF 

