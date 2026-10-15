@echo off
rem ---- Creates the "grocery_shop" database (tables + data) on this computer.
rem ---- WARNING: if grocery_shop already exists here, its tables are replaced by the ones in grocery_shop.sql.
setlocal
title Grocery Shop - Create database
cd /d "%~dp0"

set "MYSQL="
where mysql >nul 2>&1 && set "MYSQL=mysql"
if not defined MYSQL for /d %%D in ("%ProgramFiles%\MySQL\MySQL Server *") do if exist "%%D\bin\mysql.exe" set "MYSQL=%%D\bin\mysql.exe"
if not defined MYSQL for /d %%D in ("%ProgramFiles(x86)%\MySQL\MySQL Server *") do if exist "%%D\bin\mysql.exe" set "MYSQL=%%D\bin\mysql.exe"

if not defined MYSQL (
  echo MySQL Server was not found. Install MySQL Server 8.0 and start it, then run this file again.
  pause
  goto :end
)

echo.
echo This creates the database "grocery_shop" with the same tables and data as the original.
echo If it already exists on this computer, its tables will be REPLACED.
echo.
choice /M "Continue"
if errorlevel 2 goto :end

echo.
echo Type the MySQL root password when asked (nothing shows while you type), then press Enter.
"%MYSQL%" -u root -p --default-character-set=utf8mb4 < "%~dp0grocery_shop.sql"
if errorlevel 1 (
  echo.
  echo Failed. Check that MySQL is running and the password is correct.
) else (
  echo.
  echo Done! The database "grocery_shop" was created.
)
pause
:end
endlocal
