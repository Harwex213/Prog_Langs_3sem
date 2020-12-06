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

;------------------------------------------------------------
; ������� �������� ������������� ����� � ������
;------------------------------------------------------------
; ������������ � MASM, ��������� � ����������� - ManHunter
; ���������:
;   lpFloat - ��������� �� ������������ ����� TBYTE
;   lpResult - ��������� �� ������-�������� ����������
;------------------------------------------------------------
FloatToString PROC lpFloat:DWORD, lpResult:DWORD
        ; ��������� ����������
        local   digits_count:DWORD
        local   old_cw:WORD
        local   new_cw:WORD
        local   saved_float:TBYTE
        local   tmp1 rb 11h
        local   tmp2 rb 11h
 
        ; ��������� ��� ��������
        pusha
 
        ; ��������� �� ������-��������
        mov     edi,[lpResult]
 
        ; ��� ����?
        mov     esi,[lpFloat]
        cmp     dword [esi],0
        jne     loc_not_zero
        cmp     dword [esi+4],0
        jne     loc_not_zero
        cmp     word [esi+8],0
        jne     loc_not_zero
        ; �������� � ������ ����
        mov     al,'0'
        stosb
        jmp     loc_ret
 
loc_not_zero:
        ; ����������� ����� � ��������� ����������
        push    edi
        mov     esi,[lpFloat]
        lea     edi,[saved_float]
        movsd
        movsd
        movsw
        pop     edi
        ; ����� �������������?
        cmp     dword [saved_float+6],0
        jge     loc_not_signed
        ; �������� ����� � ����������� ��������
        and     byte [saved_float+9],7Fh
        ; �������� � ������ �����
        mov     al,'-'
        stosb
 
loc_not_signed:
        ; ��������� ����� �� ������� ������� ����� �
        ; ���������� ���������� ���� � ���
        fclex
        ; ��������� ����������� �����
        fstcw   [old_cw]
        ; ���������� ����������� �����
        mov     [new_cw],0000001001111111b
        fldcw   [new_cw]
        lea     esi,[saved_float]
        fld     tbyte [esi]
        fld     st
        ; �������� �������� � �������
        fxtract
        fstp    st
        fldlg2
        ; �������� ���������� ���� � �����
        fmulp   st1,st
        fistp   [digits_count]
        ; ���� ���� ������ 16, �� ����� ������������ �
        ; ��������������� ���� � ��������� � �����������
        cmp     [digits_count],10h
        jnb     loc_not_integer
        ; � ����� ���� ������� �����?
        fld     st
        frndint
        fcomp   st1
        fstsw   ax
        test    ah,01000000b
        ; ��, ���������� ����� � ������� ������
        jz      loc_not_integer
 
        ; ����� ����� ��� ������� ����� � ����������
        lea     eax,[tmp1]
        fbstp   [eax]
 
        ; ��������� BCD-����� � ������
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
 
        ; ���������� ���������� ����
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
        ; ��������� ���������� ����� �� ���������� ������
        rep     movsb
        jmp     loc_clear_stack
 
loc_not_integer:
        mov     eax,10h
        sub     eax,[digits_count]
 
        ; ������������� ����� � ����� �� 16 ��������
        mov     ecx,eax
        cmp     eax,0
        jge     @f
        neg     eax
@@:
        ; ��� ����� ������ 0 ������������� ���������� � ������� 0
        mov     [new_cw],0000101001111111b
        cmp     ecx,0
        jge     @f
        mov     [new_cw],0000011001111111b
@@:
        ; ���������� ����������� �����
        fldcw   [new_cw]
 
        ; �������� 10 � ������� ���������� ����
        fld     [float2]
        fld     [float2]
@@:
        fmul    st,st1
        dec     eax
        cmp     eax,1
        ja      @b
 
        ; ��������� ����
        fxch    st1
        fstp    st
 
        ; ���� ����� ������ 0, �� ��������, ����� ���������
        cmp     ecx,0
        jge     @f
        fdivp   st1,st
        jmp     loc_rounded
@@:
        fmulp   st1,st
 
loc_rounded:
        ; ���������� �������� ������ 1.0e16 ?
        fcom    [float1]
        fstsw   ax
        test    ah,1
        jz      @f
        fmul    [float2]
        dec     [digits_count]
@@:
        ; ����� ����� ��� ������� ����� � ����������
        lea     eax,[tmp1]
        fbstp   [eax]
 
        ; ��������� BCD-����� � ������
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
 
        ; ����� ��������� �������� � ����������?
        lea     esi,[tmp2+1]
        mov     ecx,[digits_count]
        cmp     ecx,-0Fh
        jl      loc_mantiss_and_exponent
        cmp     ecx,10h
        jg      loc_mantiss_and_exponent
 
        ; ��������� ������� ����� �����
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
        ; ������� ����������� ���� ������� �����
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
        ; ������� ����� ��������
        movsb
        mov     al,'.'
        stosb
        movsd
        movsd
        movsw
        ; ������� ����������� ���� ������� �����
@@:
        cmp     byte [edi-1],'0'
        jne     @f
        cmp     byte [edi-2],'.'
        je      @f
        dec     edi
        jmp     @b
@@:
        ; ������ � ���� ����������
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
 
        ; �������� ����������
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
 
        ; ���������� ���������� ���� ����������
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
        ; ������������ ����������� �����
        fldcw   [old_cw]
loc_ret:
        ; ��������� ������
        mov     al,0
        stosb
 
        ; ������������ ��� ��������
        popa
        ret
 
float1  dq      1.0e16
float2  dq      10.0
 
endp

end main



