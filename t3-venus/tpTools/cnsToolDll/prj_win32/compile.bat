echo off
echo cnsToolDll.dll build begin

if /I "%1" == "noclean" (
	echo build noclean debug
	@msdev cnsToolDll.dsp /MAKE "cnsToolDll - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\cnsToolDll_d.txt

	echo build noclean release
	@msdev cnsToolDll.dsp /MAKE "cnsToolDll - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\cnsToolDll_r.txt
) else (
	echo build clean debug
	@msdev cnsToolDll.dsp /MAKE "cnsToolDll - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\cnsToolDll_d.txt

	echo build clean release
	@msdev cnsToolDll.dsp /MAKE "cnsToolDll - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\cnsToolDll_r.txt
)

copy /Y release\cnsToolDll.map ..\..\prj_win32\Release\cnsToolDll.map

echo cnsToolDll.dll build over
echo on