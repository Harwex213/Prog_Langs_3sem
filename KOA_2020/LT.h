#pragma once
#define LEXEMA_FIXSIZE	1			// ������������� ������ �������
#define	LT_MAXSIZE		4096		// ������������ ���������� ����� � ������� ������	
#define	LT_TI_NULLXDX	0xffffffff	// ��� �������� ������� ���������������				
#define	LEX_INTEGER		't'			// ������� ��� integer
#define	LEX_STRING		't'			// ������� ��� string
#define LEX_INTORSTR	't'			// 
#define	LEX_ID			'i'			// ������� ��� ��������������
#define	LEX_LITERAL		'l'			// ������� ��� ��������
#define	LEX_FUNCTION	'f'			// ������� ��� function
#define	LEX_DECLARE		'd'			// ������� ��� declare
#define	LEX_RETURN		'r'			// ������� ��� return
#define	LEX_PRINT		'p'			// ������� ��� print
#define	LEX_MAIN		'm'			// ������� ��� main
#define	LEX_SEMICOLON	';'			// ������� ��� ;
#define	LEX_COMMA		','			// ������� ��� ,
#define	LEX_LEFTHESIS	'{'			// ������� ��� (
#define	LEX_RIGHTHESIS	'}'	
#define	LEX_LEFTBRACKETS  '['
#define	LEX_RIGHTBRACKETS ']'	
#define	LEX_LEFTBRACE	'('			// ������� ��� {
#define	LEX_RIGHTBRACE	')'			// ������� ��� }		// ������� ��� )
#define	LEX_COMPUTATION	'v'			// ������� ��� + - / *
#define	LEX_EQUAL_SIGN	'='			// ������� ��� =

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
	void Add(LexTable& lextable, Entry entry);	// ���������� ������
	Entry GetEntry(LexTable& lextable, int n);	// �������� ������ ������� ������
	void Delete(LexTable& lextable);			// ������� ������� ������ (���������� ������)
}