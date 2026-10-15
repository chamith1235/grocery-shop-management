@echo off
rem run.bat - builds the Grocery Shop from the source code (this creates the .exe) and starts it.
rem Needs: Visual Studio (C++ desktop + C++/CLI) and MySQL Server 8.0 installed.

set MYSQLDIR=C:\Program Files\MySQL\MySQL Server 8.0
if not exist "%MYSQLDIR%\include\mysql.h" (
    echo MySQL Server 8.0 was not found in "%MYSQLDIR%".
    echo Install MySQL Server 8.0, or change MYSQLDIR in run.bat and MySqlDir in GroceryShop.vcxproj.
    pause
    exit /b 1
)

set VSWHERE="%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist %VSWHERE% (
    echo Visual Studio is not installed. Install it with the "Desktop development with C++" workload and C++/CLI support.
    pause
    exit /b 1
)

%VSWHERE% -latest -prerelease -products * -requires Microsoft.Component.MSBuild -find "MSBuild\**\Bin\MSBuild.exe" > "%TEMP%\msbuild_path.txt"
set /p MSBUILD=<"%TEMP%\msbuild_path.txt"
if "%MSBUILD%"=="" (
    echo MSBuild was not found. Install the "Desktop development with C++" workload in Visual Studio.
    pause
    exit /b 1
)

echo Building the program (the first build takes about a minute)...
"%MSBUILD%" "%~dp0GroceryShop.sln" /p:Configuration=Debug /p:Platform=x64 /p:MySqlDir="%MYSQLDIR%" /m /v:minimal
if errorlevel 1 (
    echo.
    echo Build failed. Check the messages above.
    pause
    exit /b 1
)

echo Done. The program is here: %~dp0x64\Debug\GroceryShop.exe
echo Starting the program...
start "" "%~dp0x64\Debug\GroceryShop.exe"
