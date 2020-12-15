.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib "Mylib.lib"
ExitProcess PROTO:DWORD 
.stack 4096

.const
	literal1 db "fsdfadf"
	literal2 dd 0

.data
	x real4	3.13123131
	y real4	?
	z0 dd 10
	joker dd 80, 10
	havok db literal1
.code

main PROC
	mov eax, havok
	mov edx, OFFSET literal1
	inc eax
	mov ebx, edx
	mov eax, 1
main ENDP
end main