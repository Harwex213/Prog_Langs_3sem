.586												; система команд                        
.MODEL FLAT, STDCALL								; модель памяти        
includelib	kernel32.lib							; библиотека 
includelib	user32.lib								; библиотека 
ExitProcess PROTO : DWORD
getmin		PROTO : DWORD, : DWORD
.STACK 4096                                         ; стек   

.DATA                                               ; сегмент данных 
arr			DWORD   3, 5, -17, 3, 2, 8, -7, 0, 13, 32

.CODE												; сегмент кода  
getmin PROC array : DWORD, len : DWORD
	mov esi, array
	mov eax, [esi]
	add esi, type array
	dec len
	mov ecx, len
CYCLE:
	mov ebx, [esi]
	cmp ebx, eax
	jg	NotMin
	mov eax, ebx
NotMin:
	add esi, type array
	loop CYCLE

 	ret
getmin ENDP

main PROC 
START:
	invoke getmin, OFFSET Arr, lengthof Arr

	push 0
	call ExitProcess

main ENDP

end main



