echo off
echo umclib.lib build begin

if /I "%1" == "noclean" (
	echo build noclean debug
	@msdev umclib.dsp /MAKE "umclib - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\umclib_d.txt

	echo build noclean release
	@msdev umclib.dsp /MAKE "umclib - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\umclib_r.txt
) else (
	echo build clean debug
	@msdev umclib.dsp /MAKE "umclib - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\umclib_d.txt

	echo build clean release
	@msdev umclib.dsp /MAKE "umclib - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\umclib_r.txt
)

echo umclib.lib build over
echo on