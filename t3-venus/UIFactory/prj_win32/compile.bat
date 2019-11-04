echo off
echo UIFactory.lib build begin

if /I "%1" == "noclean" (
	echo build noclean debug
	@msdev UIFactory.dsp /MAKE "UIFactory - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\CompileInfo\UIFactory_d.txt

	echo build noclean release
	@msdev UIFactory.dsp /MAKE "UIFactory - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\CompileInfo\UIFactory_r.txt
) else (
	echo build clean debug
	@msdev UIFactory.dsp /MAKE "UIFactory - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\CompileInfo\UIFactory_d.txt

	echo build clean release
	@msdev UIFactory.dsp /MAKE "UIFactory - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\CompileInfo\UIFactory_r.txt
)

echo UIFactory.lib build over
echo on