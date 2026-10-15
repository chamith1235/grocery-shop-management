@echo off
rem ---- Grocery Shop installer (run by Setup.exe). Installs for the current user, no admin needed.
setlocal
set "DEST=%LOCALAPPDATA%\Programs\GroceryShop"

mkdir "%DEST%" 2>nul
mkdir "%DEST%\images" 2>nul

copy /Y "GroceryShop.exe"      "%DEST%\" >nul
copy /Y "libmysql.dll"          "%DEST%\" >nul
copy /Y "libssl-3-x64.dll"      "%DEST%\" >nul
copy /Y "libcrypto-3-x64.dll"   "%DEST%\" >nul
copy /Y "background.png"        "%DEST%\images\" >nul
copy /Y "login_side.png"        "%DEST%\images\" >nul
copy /Y "uninstall.cmd"         "%DEST%\" >nul

rem ---- shortcuts on the Desktop and in the Start menu
powershell -NoProfile -ExecutionPolicy Bypass -Command "$s=New-Object -ComObject WScript.Shell; foreach($f in @([Environment]::GetFolderPath('Desktop'),[Environment]::GetFolderPath('Programs'))){ $l=$s.CreateShortcut($f+'\Grocery Shop.lnk'); $l.TargetPath='%DEST%\GroceryShop.exe'; $l.WorkingDirectory='%DEST%'; $l.IconLocation='%DEST%\GroceryShop.exe'; $l.Save() }"

rem ---- friendly reminder if MySQL is not installed on this PC
sc query MySQL80 >nul 2>&1
if errorlevel 1 (
  powershell -NoProfile -ExecutionPolicy Bypass -Command "Add-Type -AssemblyName System.Windows.Forms; [void][System.Windows.Forms.MessageBox]::Show('Grocery Shop is installed.' + [char]10 + [char]10 + 'MySQL Server 8.0 was NOT found on this PC. Install MySQL Server and start it before running the program.','Grocery Shop Setup','OK','Information')"
) else (
  powershell -NoProfile -ExecutionPolicy Bypass -Command "Add-Type -AssemblyName System.Windows.Forms; [void][System.Windows.Forms.MessageBox]::Show('Grocery Shop is installed.' + [char]10 + [char]10 + 'Use the Grocery Shop icon on your Desktop. When the program asks, type your MySQL root password.','Grocery Shop Setup','OK','Information')"
)
start "" "%DEST%\GroceryShop.exe"
endlocal
