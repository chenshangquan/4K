# Microsoft Developer Studio Generated NMAKE File, Based on nmscommon.dsp
!IF "$(CFG)" == ""
CFG=NmsCommon - Win32 Debug
!MESSAGE No configuration specified. Defaulting to NmsCommon - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "NmsCommon - Win32 Release" && "$(CFG)" != "NmsCommon - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "NmsCommon - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\..\..\..\10-common\lib\release\win32\nmscommon.lib"


CLEAN :
	-@erase "$(INTDIR)\CallAddr.obj"
	-@erase "$(INTDIR)\FtpCtrl.obj"
	-@erase "$(INTDIR)\LogManage.obj"
	-@erase "$(INTDIR)\NmsCommon.obj"
	-@erase "$(INTDIR)\nmscommon.pch"
	-@erase "$(INTDIR)\parsecfgfile.obj"
	-@erase "$(INTDIR)\Ping.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TraceRT.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "..\..\..\..\10-common\lib\release\win32\nmscommon.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\include" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\platform" /I "..\..\..\..\10-common\include\nms1" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\nmscommon.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\nmscommon.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\..\10-common\lib\release\win32\nmscommon.lib" 
LIB32_OBJS= \
	"$(INTDIR)\CallAddr.obj" \
	"$(INTDIR)\FtpCtrl.obj" \
	"$(INTDIR)\LogManage.obj" \
	"$(INTDIR)\NmsCommon.obj" \
	"$(INTDIR)\parsecfgfile.obj" \
	"$(INTDIR)\Ping.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TraceRT.obj"

"..\..\..\..\10-common\lib\release\win32\nmscommon.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "NmsCommon - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\..\..\..\10-common\lib\debug\win32\nmscommon.lib"


CLEAN :
	-@erase "$(INTDIR)\CallAddr.obj"
	-@erase "$(INTDIR)\FtpCtrl.obj"
	-@erase "$(INTDIR)\LogManage.obj"
	-@erase "$(INTDIR)\NmsCommon.obj"
	-@erase "$(INTDIR)\nmscommon.pch"
	-@erase "$(INTDIR)\parsecfgfile.obj"
	-@erase "$(INTDIR)\Ping.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TraceRT.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\..\..\..\10-common\lib\debug\win32\nmscommon.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\include" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\platform" /I "..\..\..\..\10-common\include\nms1" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\nmscommon.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\nmscommon.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\..\10-common\lib\debug\win32\nmscommon.lib" 
LIB32_OBJS= \
	"$(INTDIR)\CallAddr.obj" \
	"$(INTDIR)\FtpCtrl.obj" \
	"$(INTDIR)\LogManage.obj" \
	"$(INTDIR)\NmsCommon.obj" \
	"$(INTDIR)\parsecfgfile.obj" \
	"$(INTDIR)\Ping.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TraceRT.obj"

"..\..\..\..\10-common\lib\debug\win32\nmscommon.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("nmscommon.dep")
!INCLUDE "nmscommon.dep"
!ELSE 
!MESSAGE Warning: cannot find "nmscommon.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "NmsCommon - Win32 Release" || "$(CFG)" == "NmsCommon - Win32 Debug"
SOURCE=..\source\CallAddr.cpp

"$(INTDIR)\CallAddr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\nmscommon.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\FtpCtrl.cpp

"$(INTDIR)\FtpCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\nmscommon.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\LogManage.cpp

"$(INTDIR)\LogManage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\nmscommon.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\NmsCommon.cpp

"$(INTDIR)\NmsCommon.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\nmscommon.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\parsecfgfile.cpp

"$(INTDIR)\parsecfgfile.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\nmscommon.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\Ping.cpp

"$(INTDIR)\Ping.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\nmscommon.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "NmsCommon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\include" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\platform" /I "..\..\..\..\10-common\include\nms1" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\nmscommon.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\nmscommon.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NmsCommon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\include" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\platform" /I "..\..\..\..\10-common\include\nms1" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\nmscommon.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\nmscommon.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\source\TraceRT.cpp

"$(INTDIR)\TraceRT.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\nmscommon.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

