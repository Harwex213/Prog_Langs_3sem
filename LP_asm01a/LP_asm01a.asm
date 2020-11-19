.586P
.MODEL FLAT, STDCALL
getmin PROTO: DWORD, :DWORD
getmax PROTO: DWORD, :DWORD
.CODE
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

getmax PROC array :DWORD, len : DWORD
	mov esi, array
	mov eax, [esi]
	add esi, type array
	dec len
	mov ecx, len
CYCLE:
	mov ebx, [esi]
	cmp ebx, eax
	jl	NotMax
	mov eax, ebx
NotMax:
	add esi, type array
	loop CYCLE

 	ret
getmax ENDP

end



