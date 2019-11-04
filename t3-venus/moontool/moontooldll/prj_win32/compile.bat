echo off
echo moonToolDll.dll build begin

if /I "%1" == "noclean" (
	echo build noclean debug
	@msdev moonToolDll.dsp /MAKE "moonToolDll - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\moonToolDll_d.txt

	echo build noclean release
	@msdev moonToolDll.dsp /MAKE "moonToolDll - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\moonToolDll_r.txt
) else (
	echo build clean debug
	@msdev moonToolDll.dsp /MAKE "moonToolDll - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\moonToolDll_d.txt

	echo build clean release
	@msdev moonToolDll.dsp /MAKE "moonToolDll - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\moonToolDll_r.txt
)

copy /Y release\moonToolDll.map ..\..\prj_win32\Release\moonToolDll.map

echo moonToolDll.dll build over
echo on