.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib "Mylib.lib"
ExitProcess PROTO:DWORD 
.stack 4096

.data
	x real4	3.13123131
	y real4	?
	z0 dd 10
	joker dd 80, 10
	havok dd 102, 30

.const
	literal1 dd 1
	literal2 dd 0

.code

main PROC
; havok[0] = joker[1]
; 0@1 = 1@1
	push literal1			; встречаем 1, пихаем в стек
	pop ebx					; встречаем @, снимаем со стека и умножаем на type joker
	imul ebx, type joker
	push joker[0 + ebx]
	push literal2			; встречаем 0, пихаем в стек
	pop ebx					; встречаем @, снимаем со стека и умножаем на type havok
	imul ebx, type havok
	pop havok[0 + ebx]
;
	fild z0
	fld x
	fstp z0
	fld literal1
	fld literal2
	fadd ST(1), ST(0)
	fstp y
	
	

main ENDP
end main