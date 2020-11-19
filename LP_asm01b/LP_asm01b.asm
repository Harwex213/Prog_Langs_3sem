.586					                       
.MODEL FLAT, STDCALL						        
includelib	kernel32.lib
includelib	user32.lib
includelib  libucrt
includelib	../Debug/LP_asm01a.lib
; Proto of Functions
ExitProcess		PROTO : DWORD
WriteConsoleA	PROTO : DWORD, : DWORD, : DWORD, : DWORD, : DWORD
GetStdHandle	PROTO : DWORD
IntToChar		PROTO : DWORD, : DWORD	
CPrint			PROTO : DWORD
getmin			PROTO : DWORD, : DWORD
getmax			PROTO : DWORD, : DWORD
.STACK 4096                                     

.CONST
strEnd EQU 0

.DATA
; Array
arr		DWORD   -3, -5, -17, 3, 2, 8, -7, 0, 13, 32
; Vars
min		dword	?
result	dword	?
; Console
resultIntToChar dword ?
msg		byte "getmax - getmin = "

.CODE
main PROC 
START:
	; Find min, put to min var
	push lengthof arr
	push OFFSET arr
	call getmin
	mov min, eax
	; Find max, find max - min
	push lengthof arr
	push OFFSET arr
	call getmax
	sub eax, min
	; result var to char
	invoke IntToChar, OFFSET resultIntToChar, eax
	invoke CPrint, OFFSET msg
	invoke CPrint, OFFSET resultIntToChar

	push 0
	call ExitProcess
main ENDP

CPrint PROC pstr : dword
	invoke GetStdHandle, -11

	mov esi, pstr
	mov edi, -1
count:
	inc edi
	cmp byte ptr [esi + edi], 0
	jne count

	invoke WriteConsoleA, eax, pstr, edi, 0, 0
	ret
CPrint ENDP

IntToChar PROC pstr		: dword,		; ����� ������ ����������
			   intfield : dword		; ����� ��� ��������������

	mov edi, pstr		; �������� �� pstr � edi
	mov esi, 0			; ���������� �������� � ����������
	mov eax, intfield	; ����� -> � ���
	cdq					; ���� ����� ���������������� � ��� �� edx
	mov ebx, 10			; ��������� ������� ��������� (10) -> ebx
	idiv ebx			; ��� - eax/ebx, ������� � edx (������� ����� �� ������)
	test eax, 80000000h ; ��������� �������� ���
	jz plus				; ���� ������������� ����� - �� plus
	neg eax				; ����� ������ ���� ���
	neg edx				; edx = -edx
	mov cl, '-'			; ������ ������ ���������� '-'
	mov[edi], cl		; ������ ������ ����������
	inc edi				; ++edi
	plus:				; ���� ���������� �� �������� 10
	push dx				; ������� -> ����
	inc esi				; ++esi
	test eax, eax		; ��� == ?
	jz fin				; ���� ��, �� �� fin
	cdq					; ���� ���������������� � ��� �� edx
	idiv ebx			; ��� = eax/ebx, ������� � edx
	jmp plus			; ����������� ������� �� plus
	fin: mov ecx, esi	; � ��� ���������� �� 0-��� �������� = ���������� �������� ����������
	write:				; ���� ������ ����������
	pop bx				; ������� �� ����� -> b�
	add bl, '0'			; ������������ ������ � �1
	mov[edi], bl		; �1 -> � ���������
	inc edi				; edi++
	loop write			; ���� (--���)>0 ������� �� write
	ret
IntToChar ENDP

end main



