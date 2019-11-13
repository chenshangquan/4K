
if not exist "setup files" (
    mkdir "setup files"
)

rem 拷贝相应文件
if not exist "setup files\res" (
    mkdir "setup files\res"
)

if not exist "setup files\rescnstool" (
    mkdir "setup files\rescnstool"
)

if not exist "setup files\resumstool" (
    mkdir "setup files\resumstool"
)

if not exist "..\..\10-common\version\release\win32\tpTools\tpTools.exe" (
    goto end
)

if not exist "..\..\10-common\version\release\win32\tpTools\cnsToolDll.dll" (
    goto end
)

if not exist "..\..\10-common\version\release\win32\tpTools\umstooldll.dll" (
    goto end
)

copy /Y ..\..\10-common\lib\release\win32_2010\pfc.dll "setup files\pfc.dll"

copy /Y ..\..\10-common\version\release\win32\tpTools\tpTools.exe "setup files\tpTools.exe"

copy /Y ..\..\10-common\version\release\win32\tpTools\cnsToolDll.dll "setup files\cnsToolDll.dll"

copy /Y ..\..\10-common\version\release\win32\tpTools\tpTools.map "setup files\tpTools.map"

copy /Y ..\..\10-common\version\release\win32\tpTools\umstooldll.dll "setup files\umstooldll.dll"


xcopy "..\..\10-common\version\release\win32\tpTools\rescnstool\*.*" "setup files\rescnstool\" /s /y /h
xcopy "..\..\10-common\version\release\win32\tpTools\resumstool\*.*" "setup files\resumstool\" /s /y /h 
xcopy "..\..\10-common\version\release\win32\tpTools\res\*.*" "setup files\res\" /s /y /h

cd setup
call compile.bat %1
rem call compile_desk.bat %1
cd..

del /S /Q "setup files\*.*"
rmdir /s /q "setup files"

:end

