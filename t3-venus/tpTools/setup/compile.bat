rem copy /Y touchpcmt\Script Files\SetupComm.Rul \touchpcmt\Script Files\Setup.Rul

"%InstallShield12Build%\compile.exe" "tpTools\script files\setup.rul" ifx.obl isrt.obl -libpath"%InstallShield12Script%\ifx\lib" -libpath"%InstallShield12Script%\isrt\lib" -i"%InstallShield12Script%\ifx\include" -i"%InstallShield12Script%\isrt\include" -i"%InstallShield12Script%\include" -i"%InstallShield12Script%\SQLRuntime\Include" -i"%InstallShield12Script%\IISRuntime\Include" -i"%InstallShield12Script%\XMLRuntime\Include" -i"tpTools\script files"

"%InstallShield12Build%\isbuild.exe" -p"tpTools.ism" -m"SINGLE_EXE_IMAGE"

copy /Y tpTools\Media\SINGLE_EXE_IMAGE\Package\Setup.exe "..\..\..\10-common\version\release\win32\tpTools\Íø³ÊÎ¬»¤¹¤¾ß-4k_setup.exe"
