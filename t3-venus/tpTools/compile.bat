@echo off
cd cnsToolDll
cd prj_win32
call compile.bat %1
cd ..
cd ..

cd prj_win32
call compile.bat %1
cd ..

call setup.bat %1

@echo on


