.586												; ������� ������                        
.MODEL FLAT, STDCALL								; ������ ������        
includelib	kernel32.lib							; ���������� 
includelib	user32.lib								; ���������� 
ExitProcess PROTO : DWORD
getmin		PROTO : DWORD, : DWORD
.STACK 4096                                         ; ����   

.DATA                                               ; ������� ������ 
arr			DWORD   3, 5, -17, 3, 2, 8, -7, 0, 13, 32
joker		dword	10

.CODE												; ������� ����  
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
	mov joker[4], 15
	mov eax, joker[4]
	invoke getmin, OFFSET Arr, lengthof Arr

	push 0
	call ExitProcess

main ENDP

end main



