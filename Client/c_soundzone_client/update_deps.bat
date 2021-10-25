
@ECHO OFF

ECHO I will now copy deps
xcopy /s/e /y ..\..\c_shared_modules\ .\
ECHO Deps are up to date