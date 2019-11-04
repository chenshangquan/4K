echo off
echo UILib.lib build begin

if exist ".\uilib.dep" (
	del .\uilib.dep
)

if "%1" == "noclean" (	
	echo build noclean debug
	@msdev uilib.dsp /MAKE "uilib - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\UILib_D.txt

	echo build noclean release
	@msdev uilib.dsp /MAKE "uilib - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\UILib_R.txt
) else (	
	echo build clean debug
	@msdev uilib.dsp /MAKE "uilib - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\UILib_D.txt

	echo build clean release
	@msdev uilib.dsp /MAKE "uilib - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\UILib_R.txt
)

echo UILib.lib build over
echo on


