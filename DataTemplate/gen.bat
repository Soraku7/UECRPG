set WORKSPACE=..\
set LUBAN_DLL=%WORKSPACE%\Plugins\Luban\Luban.dll
set CONF_ROOT=.

dotnet %LUBAN_DLL% ^
    -t all ^
    -c cpp-sharedptr-bin^
    -d bin ^
    --conf %CONF_ROOT%\luban.conf ^
    -x outputCodeDir=%WORKSPACE%\Source\UECRPG\Luban\Generated ^
    -x outputDataDir=%WORKSPACE%\Content\Data\LubanGenerated
pause