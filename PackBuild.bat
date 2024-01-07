::
:: Yu-Gi-Oh! Tag Force - MultiFix pack script (Windows CMD batch processor edition) 
:: by xan1242 / Tenjoin
::
:: This packages any found MultiFix build into a shippable zip archive.
:: Use only after building.
:: 7z is required to be installed in your system's PATH.
::

@echo off
cd %~dp0
if not exist "build" exit /b 1

:: TF6
if exist "build\TF6-MultiFix.prx" (
    :: PPSSPP
    if exist "build\TF6-MultiFix-PPSSPP.zip" del /Q "build\TF6-MultiFix-PPSSPP.zip"
    if not exist "build\TF6-MultiFix-PPSSPP" mkdir "build\TF6-MultiFix-PPSSPP"
    if not exist "build\TF6-MultiFix-PPSSPP\TF6-MultiFix" mkdir "build\TF6-MultiFix-PPSSPP\TF6-MultiFix"
    copy /y "build\TF6-MultiFix.prx" "build\TF6-MultiFix-PPSSPP\TF6-MultiFix\TF6-MultiFix.prx"
    copy /y "data\TF6-MultiFix\plugin.ini" "build\TF6-MultiFix-PPSSPP\TF6-MultiFix\plugin.ini"
    copy /y "README.md" "build\TF6-MultiFix-PPSSPP\README.md"
    :: a bit janky but can't think of anything else atm...
    cd "build\TF6-MultiFix-PPSSPP"
    7z a "..\TF6-MultiFix-PPSSPP.zip" "*"
    cd "..\.."
    
    :: PSP - only packs if the bootstrapper exists
    if exist "build\TF-MultiFixBoot.prx" (
        if exist "build\TF6-MultiFix-CFW.zip" del /Q "build\TF6-MultiFix-CFW.zip"
        if not exist "build\TF6-MultiFix-CFW" mkdir "build\TF6-MultiFix-CFW"
        copy /y "build\TF6-MultiFix.prx" "build\TF6-MultiFix-CFW\TF-MultiFix.prx"
        copy /y "build\TF-MultiFixBoot.prx" "build\TF6-MultiFix-CFW\TF-MultiFixBoot.prx"
        copy /y "README.md" "build\TF6-MultiFix-CFW\README.md"
        cd "build\TF6-MultiFix-CFW"
        7z a "..\TF6-MultiFix-CFW.zip" "*"
        cd "..\.."
    )
)
