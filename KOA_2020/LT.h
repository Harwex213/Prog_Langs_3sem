#pragma once

#define LEXEMA_FIXSIZE	1
#define	LT_MAXSIZE		4096
#define	LT_TI_NULLXDX	0xffffffff
#define	LEX_UINT					't'			// uint
#define	LEX_STRING					't'			// string
#define	LEX_BOOL					't'			// bool
#define	LEX_FLOAT					't'			// float
#define LEX_DATATYPE				't'
#define LEX_CONST					'c'			// const
#define	LEX_INCLUDE					'd'			// include
#define	LEX_FUNCTION				'f'			// function
#define	LEX_IF						'q'			// if
#define	LEX_ELSE					'e'			// else
#define	LEX_WHILE					'w'			// while
#define	LEX_MAIN					'm'			// main
#define	LEX_RETURN					'r'			// return
#define	LEX_PARENTHESES_LEFT		'('			
#define	LEX_PARENTHESES_RIGHT		')'
#define	LEX_BRACKETS_LEFT			'['
#define	LEX_BRACKETS_RIGHT			']'
#define	LEX_BRACES_LEFT				'{'
#define	LEX_BRACES_RIGHT			'}'
#define	LEX_PLUS					'v'			// +
#define	LEX_MINUS					'v'			// -
#define	LEX_MULTIPLY				'v'			// *
#define	LEX_DIVISION				'v'			// /
#define	LEX_EQUALLY					'g'			// ==
#define	LEX_NON_EQUALLY				'g'			// !=
#define	LEX_MORE					'g'			// >
#define	LEX_LESS					'g'			// <
#define	LEX_MORE_OR_EQUAL			'g'			// >=
#define	LEX_LESS_OR_EQUAL			'g'			// <=
#define	LEX_OR						'v'			// |
#define	LEX_AND						'v'			// &
#define	LEX_INVERSION				'b'			// ~
#define	LEX_BINARIES				'v'
#define	LEX_COMPARISONS				'g'
#define	LEX_UNARY					'b'
#define	LEX_ASSIGNMENT				'='
#define	LEX_COMMA					','
#define	LEX_SEMICOLON				';'
#define	LEX_IDENTIFICATOR			'i'
#define	LEX_LITERAL					'l'

#define SYMBOL_PLUS					'+'
#define SYMBOL_MINUS				'-'
#define SYMBOL_MULTIPLY				'*'
#define SYMBOL_DIVISION				'/'
#define SYMBOL_EQUALLY				'='
#define SYMBOL_NON_EQUALLY			'!'
#define SYMBOL_MORE					'>'
#define SYMBOL_LESS					'<'
#define SYMBOL_OR					'|'
#define SYMBOL_AND					'&'
#define SYMBOL_INVERSION			'~'

namespace LT							// ������� ������
{
	enum OperationType { NONE, PLUS, MINUS, MULTIPLY, DIVISION, EQUALLY, NON_EQUALLY, MORE, LESS, MORE_OR_EQUAL, LESS_OR_EQUAL, OR, AND, INVERSION };

	struct Entry						// ������ ������� ������
	{
		char lexema = '\0';
		int line = 0;
		int position = 0;
		int idxTI = LT_TI_NULLXDX;
		OperationType operationType = NONE;
	};

	struct LexTable						// ��������� ������� ������
	{
		int maxsize;					// ������� ������� ������ < LT_MAXSIZE
		int current_size = 0;				// ������� ������ ������� ������ < maxsize
		std::vector<Entry> table;
	};

	void AddEntry(LexTable& lextable, Entry& entry);	// ���������� ������
	Entry GetEntry(LexTable& lextable, int n);	// �������� ������ ������� ������
	void Delete(LexTable& lextable);			// ������� ������� ������ (���������� ������)
	char GetOperationSymbol(const Entry& entry);
}