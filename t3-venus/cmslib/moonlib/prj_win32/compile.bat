echo off
echo moonlib.lib build begin

if /I "%1" == "noclean" (
	echo build noclean debug
	@msdev moonlib.dsp /MAKE "moonlib - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\moonlib_d.txt

	echo build noclean release
	@msdev moonlib.dsp /MAKE "moonlib - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\moonlib_r.txt
) else (
	echo build clean debug
	@msdev moonlib.dsp /MAKE "moonlib - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\moonlib_d.txt

	echo build clean release
	@msdev moonlib.dsp /MAKE "moonlib - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\moonlib_r.txt
)

echo moonlib.lib build over
echo on