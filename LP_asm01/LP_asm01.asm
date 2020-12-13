.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib "Mylib.lib"
ExitProcess PROTO:DWORD 
.stack 4096

 outnum PROTO : DWORD

 outstr PROTO : DWORD

 outstrline PROTO : DWORD

 outnumline PROTO : DWORD

 system_pause PROTO 

 random PROTO  : DWORD

 lenght PROTO  : DWORD

 power PROTO : DWORD, : DWORD
.const
 null_division BYTE 'ERROR: DIVISION BY ZERO', 0
 overflow BYTE 'ERROR: VARIABLE OVERFLOW', 0 
	L1 SDWORD 5
	L2 BYTE '7', 0
	L3 BYTE 'empty', 0
.data
	mainout SDWORD 0
	maina DWORD ?
	mainstr DWORD ?

.code

main PROC
	push L1
	pop mainout

	push offset L2
	pop maina

	push offset L3
	pop mainstr


push mainstr
call outstr
call system_pause
push 0
call ExitProcess
SOMETHINGWRONG:
push offset null_division
call outstrline
call system_pause
push -1
call ExitProcess
EXIT_OVERFLOW:
push offset overflow
call outstrline
call system_pause
push -2
call ExitProcess
main ENDP
end main