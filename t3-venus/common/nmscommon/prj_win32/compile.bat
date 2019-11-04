echo off
echo NmsCommon.lib build begin

if exist "nmscommon.dep" (
	del "nmscommon.dep"
)

if /I "%1" == "noclean" (
	echo build noclean debug
	@msdev nmscommon.dsp /MAKE "nmscommon - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\nmscommon_d.txt

	echo build noclean release
	@msdev nmscommon.dsp /MAKE "nmscommon - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\nmscommon_r.txt
) else (
	
	echo build clean debug
	@msdev nmscommon.dsp /MAKE "nmscommon - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\nmscommon_d.txt

	echo build clean release
	@msdev nmscommon.dsp /MAKE "nmscommon - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\nmscommon_r.txt
)

echo NmsCommon.lib build over
echo on


