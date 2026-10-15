@echo off
rem ---- removes Grocery Shop (your MySQL data is NOT deleted)
set "DEST=%LOCALAPPDATA%\Programs\GroceryShop"
taskkill /IM GroceryShop.exe /F >nul 2>&1
powershell -NoProfile -ExecutionPolicy Bypass -Command "foreach($f in @([Environment]::GetFolderPath('Desktop'),[Environment]::GetFolderPath('Programs'))){ $p=$f+'\Grocery Shop.lnk'; if(Test-Path -LiteralPath $p){ [IO.File]::Delete($p) } }"
start "" /min cmd /c "ping 127.0.0.1 -n 3 >nul & rmdir /s /q ""%DEST%"""
powershell -NoProfile -ExecutionPolicy Bypass -Command "Add-Type -AssemblyName System.Windows.Forms; [void][System.Windows.Forms.MessageBox]::Show('Grocery Shop was removed. Your MySQL database was not touched.','Grocery Shop Uninstall','OK','Information')"
