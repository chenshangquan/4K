# Microsoft Developer Studio Generated NMAKE File, Based on uilib.dsp
!IF "$(CFG)" == ""
CFG=UILib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to UILib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "UILib - Win32 Release" && "$(CFG)" != "UILib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "uilib.mak" CFG="UILib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UILib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "UILib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UILib - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\..\..\10-common\lib\release\win32\uilib.lib"


CLEAN :
	-@erase "$(INTDIR)\BMPDlg.obj"
	-@erase "$(INTDIR)\CheckButton.obj"
	-@erase "$(INTDIR)\ColorSelCtrl.obj"
	-@erase "$(INTDIR)\ColourPopup.obj"
	-@erase "$(INTDIR)\FlatButton.obj"
	-@erase "$(INTDIR)\FlatDDButton.obj"
	-@erase "$(INTDIR)\SkinCheckList.obj"
	-@erase "$(INTDIR)\SkinComboBox.obj"
	-@erase "$(INTDIR)\SkinDateTime.obj"
	-@erase "$(INTDIR)\SkinDDListCtrl.obj"
	-@erase "$(INTDIR)\SkinEdit.obj"
	-@erase "$(INTDIR)\SkinFrame.obj"
	-@erase "$(INTDIR)\SkinGroup.obj"
	-@erase "$(INTDIR)\SkinHeaderCtrl.obj"
	-@erase "$(INTDIR)\SkinIPCtrl.obj"
	-@erase "$(INTDIR)\SkinListCtrl.obj"
	-@erase "$(INTDIR)\SkinMenu.obj"
	-@erase "$(INTDIR)\SkinPage.obj"
	-@erase "$(INTDIR)\SkinScroll.obj"
	-@erase "$(INTDIR)\SkinSheet.obj"
	-@erase "$(INTDIR)\SkinSliderCtrl.obj"
	-@erase "$(INTDIR)\SkinSpinCtrl.obj"
	-@erase "$(INTDIR)\SkinTab.obj"
	-@erase "$(INTDIR)\StaticEx.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TextButton30.obj"
	-@erase "$(INTDIR)\uilib.pch"
	-@erase "$(INTDIR)\UITools.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "..\..\..\10-common\lib\release\win32\uilib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\include" /I "..\..\..\10-common\include\nms1" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "WIN32" /D "NDEBUG" /Fp"$(INTDIR)\uilib.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\uilib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\10-common\lib\release\win32\uilib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\BMPDlg.obj" \
	"$(INTDIR)\CheckButton.obj" \
	"$(INTDIR)\ColorSelCtrl.obj" \
	"$(INTDIR)\ColourPopup.obj" \
	"$(INTDIR)\FlatButton.obj" \
	"$(INTDIR)\FlatDDButton.obj" \
	"$(INTDIR)\SkinCheckList.obj" \
	"$(INTDIR)\SkinComboBox.obj" \
	"$(INTDIR)\SkinDateTime.obj" \
	"$(INTDIR)\SkinDDListCtrl.obj" \
	"$(INTDIR)\SkinEdit.obj" \
	"$(INTDIR)\SkinFrame.obj" \
	"$(INTDIR)\SkinGroup.obj" \
	"$(INTDIR)\SkinHeaderCtrl.obj" \
	"$(INTDIR)\SkinIPCtrl.obj" \
	"$(INTDIR)\SkinListCtrl.obj" \
	"$(INTDIR)\SkinMenu.obj" \
	"$(INTDIR)\SkinPage.obj" \
	"$(INTDIR)\SkinScroll.obj" \
	"$(INTDIR)\SkinSheet.obj" \
	"$(INTDIR)\SkinSliderCtrl.obj" \
	"$(INTDIR)\SkinSpinCtrl.obj" \
	"$(INTDIR)\SkinTab.obj" \
	"$(INTDIR)\StaticEx.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TextButton30.obj" \
	"$(INTDIR)\UITools.obj"

"..\..\..\10-common\lib\release\win32\uilib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "UILib - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\..\..\10-common\lib\debug\win32\uilib.lib"


CLEAN :
	-@erase "$(INTDIR)\BMPDlg.obj"
	-@erase "$(INTDIR)\CheckButton.obj"
	-@erase "$(INTDIR)\ColorSelCtrl.obj"
	-@erase "$(INTDIR)\ColourPopup.obj"
	-@erase "$(INTDIR)\FlatButton.obj"
	-@erase "$(INTDIR)\FlatDDButton.obj"
	-@erase "$(INTDIR)\SkinCheckList.obj"
	-@erase "$(INTDIR)\SkinComboBox.obj"
	-@erase "$(INTDIR)\SkinDateTime.obj"
	-@erase "$(INTDIR)\SkinDDListCtrl.obj"
	-@erase "$(INTDIR)\SkinEdit.obj"
	-@erase "$(INTDIR)\SkinFrame.obj"
	-@erase "$(INTDIR)\SkinGroup.obj"
	-@erase "$(INTDIR)\SkinHeaderCtrl.obj"
	-@erase "$(INTDIR)\SkinIPCtrl.obj"
	-@erase "$(INTDIR)\SkinListCtrl.obj"
	-@erase "$(INTDIR)\SkinMenu.obj"
	-@erase "$(INTDIR)\SkinPage.obj"
	-@erase "$(INTDIR)\SkinScroll.obj"
	-@erase "$(INTDIR)\SkinSheet.obj"
	-@erase "$(INTDIR)\SkinSliderCtrl.obj"
	-@erase "$(INTDIR)\SkinSpinCtrl.obj"
	-@erase "$(INTDIR)\SkinTab.obj"
	-@erase "$(INTDIR)\StaticEx.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TextButton30.obj"
	-@erase "$(INTDIR)\uilib.pch"
	-@erase "$(INTDIR)\UITools.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\..\..\10-common\lib\debug\win32\uilib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\..\10-common\include\nms1" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\uilib.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\uilib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\10-common\lib\debug\win32\uilib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\BMPDlg.obj" \
	"$(INTDIR)\CheckButton.obj" \
	"$(INTDIR)\ColorSelCtrl.obj" \
	"$(INTDIR)\ColourPopup.obj" \
	"$(INTDIR)\FlatButton.obj" \
	"$(INTDIR)\FlatDDButton.obj" \
	"$(INTDIR)\SkinCheckList.obj" \
	"$(INTDIR)\SkinComboBox.obj" \
	"$(INTDIR)\SkinDateTime.obj" \
	"$(INTDIR)\SkinDDListCtrl.obj" \
	"$(INTDIR)\SkinEdit.obj" \
	"$(INTDIR)\SkinFrame.obj" \
	"$(INTDIR)\SkinGroup.obj" \
	"$(INTDIR)\SkinHeaderCtrl.obj" \
	"$(INTDIR)\SkinIPCtrl.obj" \
	"$(INTDIR)\SkinListCtrl.obj" \
	"$(INTDIR)\SkinMenu.obj" \
	"$(INTDIR)\SkinPage.obj" \
	"$(INTDIR)\SkinScroll.obj" \
	"$(INTDIR)\SkinSheet.obj" \
	"$(INTDIR)\SkinSliderCtrl.obj" \
	"$(INTDIR)\SkinSpinCtrl.obj" \
	"$(INTDIR)\SkinTab.obj" \
	"$(INTDIR)\StaticEx.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TextButton30.obj" \
	"$(INTDIR)\UITools.obj"

"..\..\..\10-common\lib\debug\win32\uilib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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
!IF EXISTS("uilib.dep")
!INCLUDE "uilib.dep"
!ELSE 
!MESSAGE Warning: cannot find "uilib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "UILib - Win32 Release" || "$(CFG)" == "UILib - Win32 Debug"
SOURCE=..\source\BMPDlg.cpp

"$(INTDIR)\BMPDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\CheckButton.cpp

"$(INTDIR)\CheckButton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\ColorSelCtrl.cpp

"$(INTDIR)\ColorSelCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\ColourPopup.cpp

"$(INTDIR)\ColourPopup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\FlatButton.cpp

"$(INTDIR)\FlatButton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\FlatDDButton.cpp

"$(INTDIR)\FlatDDButton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\SkinCheckList.cpp

"$(INTDIR)\SkinCheckList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\SkinComboBox.cpp

"$(INTDIR)\SkinComboBox.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\SkinDateTime.cpp

"$(INTDIR)\SkinDateTime.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\SkinDDListCtrl.cpp

"$(INTDIR)\SkinDDListCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\SkinEdit.cpp

"$(INTDIR)\SkinEdit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\SkinFrame.cpp

"$(INTDIR)\SkinFrame.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\SkinGroup.cpp

"$(INTDIR)\SkinGroup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\SkinHeaderCtrl.cpp

"$(INTDIR)\SkinHeaderCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\SkinIPCtrl.cpp

"$(INTDIR)\SkinIPCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\SkinListCtrl.cpp

"$(INTDIR)\SkinListCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\SkinMenu.cpp

"$(INTDIR)\SkinMenu.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\SkinPage.cpp

"$(INTDIR)\SkinPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\SkinScroll.cpp

"$(INTDIR)\SkinScroll.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\SkinSheet.cpp

"$(INTDIR)\SkinSheet.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\SkinSliderCtrl.cpp

"$(INTDIR)\SkinSliderCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\SkinSpinCtrl.cpp

"$(INTDIR)\SkinSpinCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\SkinTab.cpp

"$(INTDIR)\SkinTab.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\StaticEx.cpp

"$(INTDIR)\StaticEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\StdAfx.cpp

!IF  "$(CFG)" == "UILib - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\include" /I "..\..\..\10-common\include\nms1" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "WIN32" /D "NDEBUG" /Fp"$(INTDIR)\uilib.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\uilib.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "UILib - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\..\10-common\include\nms1" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\uilib.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\uilib.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\source\TextButton30.cpp

"$(INTDIR)\TextButton30.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\UITools.cpp

"$(INTDIR)\UITools.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\uilib.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

