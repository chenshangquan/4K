echo off
echo tpTools.exe build begin

if not exist "debug" (
	mkdir debug
)
if not exist "release" (
	mkdir release
)

copy /Y bin\release\umstooldll.dll release\
copy /Y bin\release\umstooldll.lib release\


copy /Y bin\Debug\umstooldll.dll Debug\
copy /Y bin\Debug\umstooldll.lib Debug\


rmdir /s/q "..\..\..\10-common\version\debug\win32\tpTools"
if not exist "..\..\..\10-common\version\debug\win32\tpTools" (
	mkdir "..\..\..\10-common\version\debug\win32\tpTools"
)

rmdir /s/q "..\..\..\10-common\version\release\win32\tpTools"
if not exist "..\..\..\10-common\version\release\win32\tpTools" (
	mkdir "..\..\..\10-common\version\release\win32\tpTools"
)

if "%1" == "noclean" (
    echo build noclean debug
@msdev tpTools.dsp /MAKE "tpTools - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\tpTools_d.txt

    echo build noclean release	

@msdev tpTools.dsp /MAKE "tpTools - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\tpTools_r.txt
) else (

    echo build clean debug
@msdev tpTools.dsp /MAKE "tpTools - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\tpTools_d.txt

    echo build clean release

@msdev tpTools.dsp /MAKE "tpTools - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\tpTools_r.txt

)

copy /Y release\tpTools.exe ..\..\..\10-common\version\release\win32\tpTools\tpTools.exe

copy /Y release\umstooldll.dll ..\..\..\10-common\version\release\win32\tpTools\umstooldll.dll
copy /Y release\umstooldll.lib ..\..\..\10-common\version\release\win32\tpTools\umstooldll.lib

copy /Y release\cnsToolDll.dll ..\..\..\10-common\version\release\win32\tpTools\cnsToolDll.dll
copy /Y release\cnsToolDll.lib ..\..\..\10-common\version\release\win32\tpTools\cnsToolDll.lib

copy /Y ..\..\..\10-common\lib\release\win32_2010\pfc.dll ..\..\..\10-common\version\release\win32\tpTools\pfc.dll


copy /Y Debug\tpTools.exe ..\..\..\10-common\version\Debug\win32\tpTools\tpTools.exe

copy /Y Debug\umstooldll.dll ..\..\..\10-common\version\Debug\win32\tpTools\umstooldll.dll

copy /Y Debug\cnsToolDll.dll ..\..\..\10-common\version\Debug\win32\tpTools\cnsToolDll.dll


if not exist "..\..\..\10-common\version\debug\win32\tpTools\rescnstool" (
	mkdir "..\..\..\10-common\version\debug\win32\tpTools\rescnstool"
)
if not exist "..\..\..\10-common\version\debug\win32\tpTools\resumstool" (
	mkdir "..\..\..\10-common\version\debug\win32\tpTools\resumstool"
)


if not exist "..\..\..\10-common\version\debug\win32\tpTools\res" (
	mkdir "..\..\..\10-common\version\debug\win32\tpTools\res"
)
xcopy  rescnstool\*.* ..\..\..\10-common\version\debug\win32\tpTools\rescnstool /s /y /h
xcopy  resumstool\*.* ..\..\..\10-common\version\debug\win32\tpTools\resumstool /s /y /h  
xcopy  res\*.* ..\..\..\10-common\version\debug\win32\tpTools\res /s /y /h  

if not exist "..\..\..\10-common\version\release\win32\tpTools\rescnstool" (
	mkdir "..\..\..\10-common\version\release\win32\tpTools\rescnstool"
)
if not exist "..\..\..\10-common\version\release\win32\tpTools\resumstool" (
	mkdir "..\..\..\10-common\version\release\win32\tpTools\resumstool"
)
if not exist "..\..\..\10-common\version\release\win32\tpTools\res" (
	mkdir "..\..\..\10-common\version\release\win32\tpTools\res"
)
xcopy  rescnstool\*.* ..\..\..\10-common\version\release\win32\tpTools\rescnstool /s /y /h
xcopy  resumstool\*.* ..\..\..\10-common\version\release\win32\tpTools\resumstool /s /y /h  
xcopy  res\*.* ..\..\..\10-common\version\release\win32\tpTools\res /s /y /h  


copy /Y release\tpTools.map ..\..\..\10-common\version\release\win32\tpTools\tpTools.map
copy /Y release\cnsToolDll.map ..\..\..\10-common\version\release\win32\tpTools\cnsToolDll.map

echo build tpTools.exe over
echo on
