bash -c make
@echo off
echo Lancer la VM o/N? [N] 
set INPUT=
set /P INPUT=%=%

if "%INPUT%"=="o" (
	goto vm
) else (
	exit
)

:vm
"C:\Program Files (x86)\VMware\VMware Workstation\vmrun.exe" start D:\VirtualMachine\Os_0.0x\Os_0.0x.vmx
goto qstop

:qstop
echo Stopper la VM o/N? [N] 
set INPUT=
set /P INPUT=%=%

if "%INPUT%"=="o" (  
	goto vmstop
) else (
	goto qstop
)

:vmstop
"C:\Program Files (x86)\VMware\VMware Workstation\vmrun.exe" stop D:\VirtualMachine\Os_0.0x\Os_0.0x.vmx
exit
