.586					                       
.MODEL FLAT, STDCALL						        
includelib	kernel32.lib
includelib	user32.lib
includelib  libucrt
includelib	../Debug/LP_asm01d.lib
; Static lib
EXTRN getmin: proc
EXTRN getmax: proc
; Proto of Functions
ExitProcess		PROTO : DWORD
WriteConsoleA	PROTO : DWORD, : DWORD, : DWORD, : DWORD, : DWORD
GetStdHandle	PROTO : DWORD
IntToChar		PROTO : DWORD, : DWORD	
CPrint			PROTO : DWORD
.STACK 4096                                     

.CONST
strEnd EQU 0
literal db "GWEQROEW"
literal1 db 1

.DATA
; Array
arr		DWORD   -3, -5, -17, 3, 2, 8, -7, 0, 13, 32
; Vars
min		dword	?
result	dword	?
tempArr db      255 DUP(0)
tempArr1 db		2
; Console
resultIntToChar dword ?
msg		byte "getmax - getmin = "

.CODE
main PROC 
START:
	push literal1
   	invoke CPrint, OFFSET literal
	mov eax, sizeof msg
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

IntToChar PROC pstr		: dword,		; адрес строки результата
			   intfield : dword		; число для преобразования

	mov edi, pstr		; копирует из pstr в edi
	mov esi, 0			; количество символов в результате
	mov eax, intfield	; число -> в еах
	cdq					; знак числа распространяется с еах на edx
	mov ebx, 10			; основание системы счисления (10) -> ebx
	idiv ebx			; еах - eax/ebx, остаток в edx (деление целых со знаком)
	test eax, 80000000h ; тестируем знаковый бит
	jz plus				; если положительное число - на plus
	neg eax				; иначе мнеяем знак еах
	neg edx				; edx = -edx
	mov cl, '-'			; первый символ результата '-'
	mov[edi], cl		; первый символ результата
	inc edi				; ++edi
	plus:				; цикл разложения по степеням 10
	push dx				; остаток -> стек
	inc esi				; ++esi
	test eax, eax		; еах == ?
	jz fin				; если да, то на fin
	cdq					; знак распространяется с еах на edx
	idiv ebx			; еах = eax/ebx, остаток в edx
	jmp plus			; безусловный переход на plus
	fin: mov ecx, esi	; в есх количество не 0-вых остатков = количеству символов результата
	write:				; цикл записи результата
	pop bx				; остаток из стека -> bх
	add bl, '0'			; сформировали символ в Ь1
	mov[edi], bl		; Ь1 -> в результат
	inc edi				; edi++
	loop write			; если (--есх)>0 переход на write
	ret
IntToChar ENDP

;------------------------------------------------------------
; Функция перевода вещественного числа в строку
;------------------------------------------------------------
; Портирование с MASM, доработка и оптимизация - ManHunter
; Параметры:
;   lpFloat - указатель на вещественное число TBYTE
;   lpResult - указатель на строку-приемник результата
;------------------------------------------------------------

end main



