@echo off
REM 这里把UV设置成Keil安�?�地址
set UV=G:\Keil_v5\UV4\UV4.exe
if "%1" == "" goto NOP
set UV_PRO_PATH=%cd%\USER\%1.uvprojX
if "%2" == "-b" (
    echo Init building ... 
    %UV% -j0 -b %UV_PRO_PATH% -o %cd%\build_log.txt 
    type build_log.txt
) else if "%2" == "-f" (
    echo Init flashing ...  
    %UV% -j0 -f %UV_PRO_PATH% -o %cd%\build_log.txt 
    type build_log.txt
) else (
    echo Init building ... 
    %UV% -j0 -b %UV_PRO_PATH% -o %cd%\build_log.txt 
    type build_log.txt
    echo Init flashing ... 
    %UV% -j0 -f %UV_PRO_PATH% -o %cd%\build_log.txt 
    type build_log.txt
)
if "%3" == "-f" (
    echo Init flashing ... 
    %UV% -j0 -f %UV_PRO_PATH% -o %cd%\build_log.txt 
    type build_log.txt
)
goto end

:NOP
echo No ProjectName
goto end

:end
exit