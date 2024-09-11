@echo on

set CUR_DIR="%~dp0"
mkdir "%CUR_DIR%\obj"

copy "%CUR_DIR%\ModInfo.xml" "%CUR_DIR%\obj\"

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x86

devenv "%~dp0\TextBubbleLimitBreak\TextBubbleLimitBreak.sln" /Build "Release"

copy "%programdata%\SporeModManagerStorage\mLibs\TextBubbleLimitBreak.dll" "%CUR_DIR%\obj\"

smfx pack "%~dp0\SMFX\AdventureTextLimitBreak-Full"  "%~dp0\obj\AdventureTextLimitBreak-Full.package"

smfx pack "%~dp0\SMFX\AdventureTextLimitBreak-ShareFriendly"  "%~dp0\obj\AdventureTextLimitBreak-ShareFriendly.package"

cd "%CUR_DIR%\obj\"

"C:\Program Files\7-Zip\7z" a -tzip %CUR_DIR%\AdventureTextLimitBreak.sporemod *

cd "%CUR_DIR%"

rmdir /s /q "%CUR_DIR%\obj\"