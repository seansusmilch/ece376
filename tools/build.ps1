# Executing: "C:\Program Files (x86)\HI-TECH Software\PICC-18\PRO\9.63\bin\picc18.exe" --pass1 "C:\Users\seant\Nextcloud\Documents\School\2022 Fall\ECE 376 Embedded Systems\MPLABC\1234.c" -q --chip=18F4620 -P --runtime=default,+clear,+init,-keep,-download,+stackwarn,-config,+clib,-plib --opt=default,+asm,-speed,+space,9 --warn=0 -D__DEBUG=1 --mode=pro -g --asmlist "--errformat=Error   [%n] %f; %l.%c %s" "--msgformat=Advisory[%n] %s" "--warnformat=Warning [%n] %f; %l.%c %s" 
# Executing: "C:\Program Files (x86)\HI-TECH Software\PICC-18\PRO\9.63\bin\picc18.exe" -omplabc.cof -mmplabc.map --summary=default,-psect,-class,+mem,-hex --output=default,-inhx032 --codeoffset=0x800 1234.p1 --chip=18F4620 -P --runtime=default,+clear,+init,-keep,-download,+stackwarn,-config,+clib,-plib --opt=default,+asm,-speed,+space,9 --warn=0 -D__DEBUG=1 --mode=pro -g --asmlist "--errformat=Error   [%n] %f; %l.%c %s" "--msgformat=Advisory[%n] %s" "--warnformat=Warning [%n] %f; %l.%c %s" 

$file = $args[0]
if($file -like ""){
    Write-Output "No file in arguments! Exiting..."
    exit
}

Write-Output "Compiling $file"

$src = "./src"
$tmp = "./tmp"
$comp_exe = "C:\Program Files (x86)\HI-TECH Software\PICC-18\PRO\9.63\bin\picc18.exe"

if(Test-Path -Path $tmp){
    Set-Location $tmp
}else{
    Set-Location "../$tmp"
}
& $comp_exe --pass1 "../$src/$file.c" -q --chip=18F4620 -P --runtime=default,+clear,+init,-keep,-download,+stackwarn,-config,+clib,-plib --opt=default,+asm,-speed,+space,9 --warn=0 -D__DEBUG=1 --mode=pro -g --asmlist "--errformat=Error   [%n] %f; %l.%c %s" "--msgformat=Advisory[%n] %s" "--warnformat=Warning [%n] %f; %l.%c %s"

& $comp_exe --summary=default,-psect,-class,+mem,-hex --output=default,-inhx032 --codeoffset=0x800 "$file.p1" --chip=18F4620 -P --runtime=default,+clear,+init,-keep,-download,+stackwarn,-config,+clib,-plib --opt=default,+asm,-speed,+space,9 --warn=0 -D__DEBUG=1 --mode=pro -g --asmlist "--errformat=Error   [%n] %f; %l.%c %s" "--msgformat=Advisory[%n] %s" "--warnformat=Warning [%n] %f; %l.%c %s"
# & $comp_exe -omplabc.cof -mmplabc.map --summary=default,-psect,-class,+mem,-hex --output=default,-inhx032 --codeoffset=0x800 1234.p1 --chip=18F4620 -P --runtime=default,+clear,+init,-keep,-download,+stackwarn,-config,+clib,-plib --opt=default,+asm,-speed,+space,9 --warn=0 -D__DEBUG=1 --mode=pro -g --asmlist "--errformat=Error   [%n] %f; %l.%c %s" "--msgformat=Advisory[%n] %s" "--warnformat=Warning [%n] %f; %l.%c %s"

Move-Item "./$file.hex" ../builds -Force