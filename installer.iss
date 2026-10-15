; Inno Setup script for Grocery Shop Management
; 1. Build the project in Visual Studio with Release / x64
; 2. Open this file in Inno Setup Compiler and press Compile (Ctrl+F9)
; 3. The installer appears in the "installer_output" folder

[Setup]
AppName=Grocery Shop Management
AppVersion=1.0
DefaultDirName={autopf}\GroceryShop
DefaultGroupName=Grocery Shop
OutputDir=installer_output
OutputBaseFilename=GroceryShop_Setup
Compression=lzma
SolidCompression=yes
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible
UninstallDisplayIcon={app}\GroceryShop.exe

[Files]
Source: "x64\Release\GroceryShop.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "x64\Release\libmysql.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "x64\Release\libssl-3-x64.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "x64\Release\libcrypto-3-x64.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "x64\Release\images\*"; DestDir: "{app}\images"; Flags: ignoreversion recursesubdirs

[Icons]
Name: "{group}\Grocery Shop"; Filename: "{app}\GroceryShop.exe"
Name: "{autodesktop}\Grocery Shop"; Filename: "{app}\GroceryShop.exe"; Tasks: desktopicon

[Tasks]
Name: "desktopicon"; Description: "Create a desktop shortcut"; Flags: unchecked

[Run]
Filename: "{app}\GroceryShop.exe"; Description: "Start Grocery Shop"; Flags: nowait postinstall skipifsilent
