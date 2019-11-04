echo off
echo TestNmsCommonLib.exe build begin

if /I "%1" == "debug" (
	echo build clean debug
	del /F /Q debug\*.*
	namke /NOLOGO /A /B /f TestNmsCommonLib.mak CFG="TestNmsCommonLib = Win32 Debug" /x nmakeError.log > ..\..\..\..\..\..\10-common\version\compileinfo\nmscommonlib_unittest_D.txt

	copy /y Debug\TestNmsCommonLib_D.exe ..\..\..\..\..\..\10-common\version\debug\unittest\nms1\nmscommonlib\testnmscommonlib_D.exe
) else if "%1" == "noclean" (
	echo build noclean release
	nmake /NOLOGO /B /f TestNmsCommonLib.mak CFG="TestNmsCommonLib - Win32 Release" /x nmakeError.log > ..\..\..\..\..\..\10-common\version\compileinfo\nmscommonlib_unittest_R.txt

	copy /y Release\TestNmsCommonLib_R.exe ..\..\..\..\..\..\10-common\version\release\unittest\nms1\nmscommonlib\testnmscommonlib_R.exe
) else (
	echo build clean release
	del /F /Q release\*.*
	nmake /NOLOGO /A /B /f TestNmsCommonLib.mak CLEAN ALL CFG="TestNmsCommonLib - Win32 Release" /x nmakeError.log > ..\..\..\..\..\..\10-common\version\compileinfo\nmscommonlib_unittest_R.txt

	copy /y Release\TestNmsCommonLib_R.exe ..\..\..\..\..\..\10-common\version\release\unittest\nms1\nmscommonlib\testnmscommonlib_R.exe
)

echo TestNmsCommonLib.exe build over
echo on


