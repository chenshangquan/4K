echo off
echo cnclib.lib build begin

if /I "%1" == "noclean" (
	echo build noclean debug
	@msdev cnclib.dsp /MAKE "cnclib - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\cnclib_d.txt

	echo build noclean release
	@msdev cnclib.dsp /MAKE "cnclib - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\cnclib_r.txt
) else (
	echo build clean debug
	@msdev cnclib.dsp /MAKE "cnclib - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\cnclib_d.txt

	echo build clean release
	@msdev cnclib.dsp /MAKE "cnclib - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\cnclib_r.txt
)

echo cnclib.lib build over
echo on