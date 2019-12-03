
if not exist "setup files" (
    mkdir "setup files"
)

rem 拷贝相应文件
if not exist "setup files\res" (
    mkdir "setup files\res"
)

if not exist "setup files\resmoontool" (
    mkdir "setup files\resmoontool"
)

if not exist "..\..\10-common\version\release\win32\moontool\moontool.exe" (
    goto end
)

if not exist "..\..\10-common\version\release\win32\moontool\moontooldll.dll" (
    goto end
)

copy /Y ..\..\10-common\version\release\win32\moontool\moontool.exe "setup files\moontool.exe"

copy /Y ..\..\10-common\version\release\win32\moontool\moontool.map "setup files\moontool.map"

copy /Y ..\..\10-common\version\release\win32\moontool\moontooldll.dll "setup files\moontooldll.dll"

copy /Y ..\..\10-common\version\release\win32\moontool\tftp.exe "setup files\tftp.exe"

xcopy "..\..\10-common\version\release\win32\moontool\resmoontool\*.*" "setup files\resmoontool\" /s /y /h  
xcopy "..\..\10-common\version\release\win32\moontool\res\*.*" "setup files\res\" /s /y /h

cd setup
call compile.bat %1
rem call compile_desk.bat %1
cd..

del /S /Q "setup files\*.*"
rmdir /s /q "setup files"

:end

