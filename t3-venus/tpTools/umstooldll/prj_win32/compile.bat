echo off
echo umstooldll.dll build begin

if /I "%1" == "noclean" (
	echo build noclean debug
	@msdev umstooldll.dsp /MAKE "umstooldll - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\umstooldll_d.txt

	echo build noclean release
	@msdev umstooldll.dsp /MAKE "umstooldll - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\umstooldll_r.txt
) else (
	echo build clean debug
	@msdev umstooldll.dsp /MAKE "umstooldll - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\umstooldll_d.txt

	echo build clean release
	@msdev umstooldll.dsp /MAKE "umstooldll - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\compileinfo\umstooldll_r.txt
)

echo umstooldll.dll build over
echo on