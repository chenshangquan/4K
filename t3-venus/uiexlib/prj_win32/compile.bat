echo off
echo uiexlib.lib build begin


if "%1" == "noclean" (
	echo build noclean debug
	@msdev uiex.dsp /MAKE "uiex - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\uiexlib_d.txt

	echo build noclean release
	@msdev uiex.dsp /MAKE "uiex - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\uiexlib_r.txt
) else (
	echo build clean debug
	@msdev uiex.dsp /MAKE "uiex - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\uiexlib_d.txt

	echo build clean release
	@msdev uiex.dsp /MAKE "uiex - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\uiexlib_r.txt
)

echo uiexlib.lib build over
echo on


