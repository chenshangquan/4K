echo off
echo moontool.exe build begin

if not exist "release" (
	mkdir release
)

rmdir /s/q "..\..\..\10-common\version\release\win32\moontool"
if not exist "..\..\..\10-common\version\release\win32\moontool" (
	mkdir "..\..\..\10-common\version\release\win32\moontool"
)

if "%1" == "noclean" (
    echo build noclean release	

@msdev moontool.dsp /MAKE "moontool - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\moontool_r.txt
) else (

    echo build clean release

@msdev moontool.dsp /MAKE "moontool - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\moontool_r.txt

)



copy /Y release\moontool.exe ..\..\..\10-common\version\release\win32\moontool\moontool.exe

copy /Y release\moonToolDll.dll ..\..\..\10-common\version\release\win32\moontool\moonToolDll.dll

copy /Y ..\..\producetest2\prj_win32\tftp\release\tftp.exe ..\..\..\10-common\version\release\win32\moontool\tftp.exe

if not exist "..\..\..\10-common\version\release\win32\moontool\resmoontool" (
	mkdir "..\..\..\10-common\version\release\win32\moontool\resmoontool"
)
if not exist "..\..\..\10-common\version\release\win32\moontool\res" (
	mkdir "..\..\..\10-common\version\release\win32\moontool\res"
)

xcopy  resmoontool\*.* ..\..\..\10-common\version\release\win32\moontool\resmoontool /s /y /h
xcopy  res\*.* ..\..\..\10-common\version\release\win32\moontool\res /s /y /h  


copy /Y release\moontool.map ..\..\..\10-common\version\release\win32\moontool\moontool.map

echo build moontool.exe over
echo on
