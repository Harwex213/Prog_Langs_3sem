#pragma once

#define LEXEMA_FIXSIZE	1
#define	LT_MAXSIZE		4096
#define	LT_TI_NULLXDX	0xffffffff
#define	LEX_UINT					't'
#define	LEX_STRING					't'
#define	LEX_BOOL					't'
#define	LEX_FLOAT					't'
#define LEX_DATATYPE				't'
#define	LEX_INCLUDE					'd'
#define	LEX_FUNCTION				'f'
#define	LEX_IF						'q'
#define	LEX_WHILE					'w'
#define	LEX_MAIN					'm'
#define	LEX_RETURN					'r'
#define	LEX_PARENTHESES_LEFT		'('
#define	LEX_PARENTHESES_RIGHT		')'
#define	LEX_BRACKETS_LEFT			'['
#define	LEX_BRACKETS_RIGHT			']'
#define	LEX_BRACES_LEFT				'{'
#define	LEX_BRACES_RIGHT			'}'
#define	LEX_PLUS					'v'
#define	LEX_MINUS					'v'
#define	LEX_MULTIPLY				'v'
#define	LEX_DIVISION				'v'
#define	LEX_EQUALLY					'v'
#define	LEX_NON_EQUALLY				'v'
#define	LEX_MORE					'v'
#define	LEX_LESS					'v'
#define	LEX_MORE_OR_EQUAL			'v'
#define	LEX_LESS_OR_EQUAL			'v'
#define	LEX_OR						'v'
#define	LEX_AND						'v'
#define	LEX_INVERSION				'v'
#define	LEX_ASSIGNMENT				'='
#define	LEX_COMMA					','
#define	LEX_SEMICOLON				';'
#define	LEX_IDENTIFICATOR			'i'
#define	LEX_LITERAL					'l'
#define	LEX_TRUE					'l'
#define	LEX_FALSE					'l'

#define PARM_LEX_DEFAULT_EXT L".lex.txt" //��� ����� � ������ ������������ ������a(�������������� � ��������)

namespace LT							// ������� ������
{
	enum ArithmeticSymbol {UNDEFINED = 0, PLUS = 1, MINUS = 2, MULTIPLY = 3, FISSION = 4};
	struct Entry						// ������ ������� ������
	{
		char lexema[LEXEMA_FIXSIZE+1];	// �������
		int sn;							// ����� ������ � �������� ������
		int psn;
		int idxTI;						// ������ � ������� ��������������� ��� LT_TI_NULLIDX
		ArithmeticSymbol arithmeticdata = UNDEFINED;
	};

	struct LexTable						// ��������� ������� ������
	{
		int maxsize;					// ������� ������� ������ < LT_MAXSIZE
		int current_size;				// ������� ������ ������� ������ < maxsize
		Entry* table;					// ������ ����� ������� ������
	};

	LexTable Create(int size);					// ������� ������� ������
	void AddEntry(LexTable& lextable, Entry entry);	// ���������� ������
	Entry GetEntry(LexTable& lextable, int n);	// �������� ������ ������� ������
	void Delete(LexTable& lextable);			// ������� ������� ������ (���������� ������)
}