echo off
echo LibTest.exe build begin


if "%1" == "noclean" (
	echo build noclean debug
	nmake /NOLOGO /B /f Libtest.mak CFG="LibTest - Win32 Debug" /x nmakeError.log > ..\..\..\..\10-common\version\CompileInfo\LibTest_D.txt

	echo build noclean release
	nmake /NOLOGO /B /f Libtest.mak CFG="LibTest - Win32 Release" /x nmakeError.log > ..\..\..\..\10-common\version\CompileInfo\LibTest_R.txt
) else (
	echo build clean debug
	del /F /Q debug\*.*
	nmake /NOLOGO /A /B /f Libtest.mak CFG="LibTest - Win32 Debug" /x nmakeError.log > ..\..\..\..\10-common\version\CompileInfo\LibTest_D.txt
	
	echo build clean relese
	del /F /Q Release\*.*
	nmake /NOLOGO /A /B /f Libtest.mak CFG="LibTest - Win32 Release" /x nmakeError.log > ..\..\..\..\10-common\version\CompileInfo\LibTest_R.txt
)

echo LibTest.exe build over
echo on


