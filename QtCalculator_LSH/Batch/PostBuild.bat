@echo on

set "Configuration=%1%"
set "Platform=%2%"

IF %1 == Debug goto DEBUG
IF %1 == Release goto RELEASE

:DEBUG
set Config=Debug

:RELEASE
set Config=Release

echo %2\bin\windeployqt.exe .\x64\%Config%\
%2\bin\windeployqt.exe .\x64\%Config%\
