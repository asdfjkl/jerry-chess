; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Jerry - Das Schachprogramm"
#define MyAppVersion "4.0"
#define MyAppPublisher "org.asdfjkl"
#define MyAppURL "https://github.com/asdfjkl/jerry"
#define MyAppExeName "jerryfx.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{392327C7-54CE-4790-B3A7-C337972BAAAF}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\JerryFX
DisableProgramGroupPage=yes
LicenseFile=C:\Users\user\MyFiles\workspace\IdeaProjects\jerryfx\LICENSE.TXT
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
OutputBaseFilename=SetupJerryChess
Compression=lzma
SolidCompression=yes
WizardStyle=modern
ArchitecturesInstallIn64BitMode=x64
SetupIconFile="C:\Users\user\MyFiles\workspace\build dir\jerry.ico"
OutputDir="C:\Users\user\MyFiles\workspace\build dir\JerrySetup"

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "C:\Users\user\MyFiles\workspace\build dir\output\jerryfx\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
;Source: "C:\Users\user\MyFiles\workspace\build dir\jerry.bat"; DestDir: "{app}"; Flags: ignoreversion
;Source: "C:\Users\user\MyFiles\workspace\build dir\jerryfx-4.0-jar-with-dependencies.jar"; DestDir: "{app}"; Flags: ignoreversion
;Source: "C:\Users\user\MyFiles\workspace\build dir\book\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
;Source: "C:\Users\user\MyFiles\workspace\build dir\engine\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
;Source: "C:\Users\user\MyFiles\workspace\build dir\jdk-11.0.8+10-jre\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\jerryfx.ico";
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon; IconFilename: "{app}\jerryfx.ico"

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: shellexec postinstall skipifsilent