@echo off
tasklist /FI "IMAGENAME eq %1" /FO LIST|findstr "PID:">.ps 
set /P pid=<.ps 
if "%pid%" == "" goto exit
set pid=%pid: =%
set pid=%pid:~4,16% 

ver | findstr /IL "5.0" > NUL
if %ERRORLEVEL% EQU 0 goto tsk

ver | findstr /IL "5.1." > NUL
if %ERRORLEVEL% EQU 0 goto tsk

ver | findstr /IL "5.2." > NUL
if %ERRORLEVEL% EQU 0 goto taskk

ver | findstr /IL "6.0." > NUL
if %ERRORLEVEL% EQU 0 goto taskk

ver | findstr /IL "6.1." > NUL
if %ERRORLEVEL% EQU 0 goto taskk

:taskk
taskkill /IM "%1" /F
goto exit

:tsk
tskill %pid%

:exit