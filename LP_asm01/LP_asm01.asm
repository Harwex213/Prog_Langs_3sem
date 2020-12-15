.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib "Mylib.lib"
ExitProcess PROTO : DWORD 
test1		PROTO : DWORD, : DWORD
.stack 4096

.const
	literal1 dd 1
	literal2 dd 0

.data
	x real4	3.13123131
	y real4	?
	z0 dd 10
.code
test1 PROC, joker:  DWORD	, havok : DWORD
mov ebx, 10
mul ebx
mov eax, joker
ret
test1 ENDP
main PROC
	push literal1
	push literal2
	pop ebx
	pop eax
	invoke	test1, eax, ebx
	
	push 0
	call ExitProcess
main ENDP
end main