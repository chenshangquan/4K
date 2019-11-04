@echo off
cd cnclib
cd prj_win32
call compile.bat %1
cd ..
cd ..

cd moonlib
cd prj_win32
call compile.bat %1
cd ..
cd ..

rem cd umclib
rem cd prj_win32
rem call compile.bat %1
rem cd ..
rem cd ..

@echo on


