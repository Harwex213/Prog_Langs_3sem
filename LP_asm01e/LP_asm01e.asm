.586					                       
.MODEL FLAT, STDCALL						        
includelib	kernel32.lib
includelib	user32.lib
includelib win32a.inc
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
FloatToString   PROTO : DWORD, :DWORD
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
FloatToString PROC lpFloat:DWORD, lpResult:DWORD
        ; Локальные переменные
        local   digits_count:DWORD
        local   old_cw:WORD
        local   new_cw:WORD
        local   saved_float:TBYTE
        local   tmp1 rb 11h
        local   tmp2 rb 11h
 
        ; Сохранить все регистры
        pusha
 
        ; Указатель на строку-приемник
        mov     edi,[lpResult]
 
        ; Это ноль?
        mov     esi,[lpFloat]
        cmp     dword [esi],0
        jne     loc_not_zero
        cmp     dword [esi+4],0
        jne     loc_not_zero
        cmp     word [esi+8],0
        jne     loc_not_zero
        ; Записать в строку ноль
        mov     al,'0'
        stosb
        jmp     loc_ret
 
loc_not_zero:
        ; Скопировать число в локальную переменную
        push    edi
        mov     esi,[lpFloat]
        lea     edi,[saved_float]
        movsd
        movsd
        movsw
        pop     edi
        ; Число отрицательное?
        cmp     dword [saved_float+6],0
        jge     loc_not_signed
        ; Привести число к абсолютному значению
        and     byte [saved_float+9],7Fh
        ; Записать в строку минус
        mov     al,'-'
        stosb
 
loc_not_signed:
        ; Проверить число на наличие дробной части и
        ; подсчитать количество цифр в нем
        fclex
        ; Сохранить управляющее слово
        fstcw   [old_cw]
        ; Установить управляющее слово
        mov     [new_cw],0000001001111111b
        fldcw   [new_cw]
        lea     esi,[saved_float]
        fld     tbyte [esi]
        fld     st
        ; Выделить мантиссу и порядок
        fxtract
        fstp    st
        fldlg2
        ; Получить количество цифр в числе
        fmulp   st1,st
        fistp   [digits_count]
        ; Если цифр больше 16, то число отображается в
        ; нормализованном виде с мантиссой и экспонентой
        cmp     [digits_count],10h
        jnb     loc_not_integer
        ; У числа есть дробная часть?
        fld     st
        frndint
        fcomp   st1
        fstsw   ax
        test    ah,01000000b
        ; Да, отображать число с дробной частью
        jz      loc_not_integer
 
        ; Целое число без дробной части и экспоненты
        lea     eax,[tmp1]
        fbstp   [eax]
 
        ; Перевести BCD-число в строку
        push    edi
        lea     esi,[tmp1+8]
        lea     edi,[tmp2]
        mov     ecx, 9
@@:
        std
        xor     eax,eax
        lodsb
        cld
        rol     ax,12
        rol     ah,4
        add     ax,'00'
        stosw
        loop    @b
        pop     edi
 
        ; Пропустить лидирующий ноль
        mov     eax,11h
        mov     ecx,[digits_count]
        sub     eax,ecx
        inc     ecx
        lea     esi,[tmp2+eax]
        cmp     byte [esi],'0'
        jne     @f
        inc     esi
        dec     ecx
@@:
        ; Перенести полученное число из временного буфера
        rep     movsb
        jmp     loc_clear_stack
 
loc_not_integer:
        mov     eax,10h
        sub     eax,[digits_count]
 
        ; Преобразовать число в целое до 16 разрядов
        mov     ecx,eax
        cmp     eax,0
        jge     @f
        neg     eax
@@:
        ; Для чисел больше 0 корректировка округления в сторону 0
        mov     [new_cw],0000101001111111b
        cmp     ecx,0
        jge     @f
        mov     [new_cw],0000011001111111b
@@:
        ; Установить управляющее слово
        fldcw   [new_cw]
 
        ; Возвести 10 в степень количества цифр
        fld     [float2]
        fld     [float2]
@@:
        fmul    st,st1
        dec     eax
        cmp     eax,1
        ja      @b
 
        ; Почистить стек
        fxch    st1
        fstp    st
 
        ; Если число меньше 0, то умножить, иначе разделить
        cmp     ecx,0
        jge     @f
        fdivp   st1,st
        jmp     loc_rounded
@@:
        fmulp   st1,st
 
loc_rounded:
        ; Полученное значение меньше 1.0e16 ?
        fcom    [float1]
        fstsw   ax
        test    ah,1
        jz      @f
        fmul    [float2]
        dec     [digits_count]
@@:
        ; Целое число без дробной части и экспоненты
        lea     eax,[tmp1]
        fbstp   [eax]
 
        ; Перевести BCD-число в строку
        push    edi
        lea     esi,[tmp1+8]
        lea     edi,[tmp2]
        mov     ecx, 9
@@:
        std
        xor     eax,eax
        lodsb
        cld
        rol     ax,12
        rol     ah,4
        add     ax,'00'
        stosw
        loop    @b
        pop     edi
 
        ; Числу требуется мантисса и экспонента?
        lea     esi,[tmp2+1]
        mov     ecx,[digits_count]
        cmp     ecx,-0Fh
        jl      loc_mantiss_and_exponent
        cmp     ecx,10h
        jg      loc_mantiss_and_exponent
 
        ; Заполнить дробную часть числа
        inc     ecx
        cmp     ecx,0
        jg      @f
        mov     ax,'0.'
        stosw
        neg     ecx
        mov     al,'0'
        rep     stosb
        mov     ecx,10h
        jmp     loc_fraction_filled
@@:
        rep     movsb
        mov     al,'.'
        stosb
        mov     ecx,10h
        sub     ecx,[digits_count]
 
loc_fraction_filled:
        rep     movsb
        jmp     @f
 
loc_clear_fraction:
        ; Удалить завершающие нули дробной части
        dec     edi
@@:
        cmp     byte [edi-1],'0'
        jz      loc_clear_fraction
        cmp     byte [edi-1],'.'
        jnz     @f
        dec     edi
@@:
        jmp     loc_clear_stack
 
loc_mantiss_and_exponent:
        ; Дробная часть мантиссы
        movsb
        mov     al,'.'
        stosb
        movsd
        movsd
        movsw
        ; Удалить завершающие нули дробной части
@@:
        cmp     byte [edi-1],'0'
        jne     @f
        cmp     byte [edi-2],'.'
        je      @f
        dec     edi
        jmp     @b
@@:
        ; Символ и знак экспоненты
        mov     al,'e'
        stosb
        mov     al,'+'
        mov     ebx,[digits_count]
        cmp     ebx, 0
        jge     @f
        mov     al,'-'
        neg     ebx
@@:
        stosb
 
        ; Значение экспоненты
        mov     eax,ebx
        mov     ecx,10
        mov     ebx,4
@@:
        dec     ebx
        xor     edx,edx
        div     ecx
        add     dl,'0'
        mov     [tmp1+ebx],dl
        or      ebx,ebx
        jnz     @b
 
        ; Пропустить лидирующие нули экспоненты
        mov     ecx,4
        lea     esi,[tmp1]
@@:
        lodsb
        cmp     al,'0'
        jne     @f
        dec     ecx
        jmp     @b
@@:
        dec     esi
        rep     movsb
 
loc_clear_stack:
        ; Восстановить управляющее слово
        fldcw   [old_cw]
loc_ret:
        ; Окончание строки
        mov     al,0
        stosb
 
        ; Восстановить все регистры
        popa
        ret
 
float1  dq      1.0e16
float2  dq      10.0
 
endp

end main



