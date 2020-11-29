#pragma once
#define LEXEMA_FIXSIZE	1			// фиксированный размер лексемы
#define	LT_MAXSIZE		4096		// максимальное количество строк в таблице лексем	
#define	LT_TI_NULLXDX	0xffffffff	// нет элемента таблицы идентификаторов				
#define	LEX_INTEGER		't'			// лексема для integer
#define	LEX_STRING		't'			// лексема для string
#define LEX_INTORSTR	't'			// 
#define	LEX_ID			'i'			// лексема для идентификатора
#define	LEX_LITERAL		'l'			// лексема для литерала
#define	LEX_FUNCTION	'f'			// лексема для function
#define	LEX_DECLARE		'd'			// лексема для declare
#define	LEX_RETURN		'r'			// лексема для return
#define	LEX_PRINT		'p'			// лексема для print
#define	LEX_MAIN		'm'			// лексема для main
#define	LEX_SEMICOLON	';'			// лексема для ;
#define	LEX_COMMA		','			// лексема для ,
#define	LEX_LEFTHESIS	'{'			// лексема для (
#define	LEX_RIGHTHESIS	'}'	
#define	LEX_LEFTBRACKETS  '['
#define	LEX_RIGHTBRACKETS ']'	
#define	LEX_LEFTBRACE	'('			// лексема для {
#define	LEX_RIGHTBRACE	')'			// лексема для }		// лексема для )
#define	LEX_COMPUTATION	'v'			// лексема для + - / *
#define	LEX_EQUAL_SIGN	'='			// лексема для =

namespace LT							// таблица лексем
{
	enum ArithmeticSymbol {UNDEFINED = 0, PLUS = 1, MINUS = 2, MULTIPLY = 3, FISSION = 4};
	struct Entry						// строка таблицы лексем
	{
		char lexema[LEXEMA_FIXSIZE+1];	// лексема
		int sn;							// номер строки в исходном тексте
		int psn;
		int idxTI;						// индекс в таблице идентификаторов или LT_TI_NULLIDX
		ArithmeticSymbol arithmeticdata = UNDEFINED;
	};

	struct LexTable						// экземпляр таблицы лексем
	{
		int maxsize;					// емкость таблицы лексем < LT_MAXSIZE
		int current_size;				// текущий размер таблицы лексем < maxsize
		Entry* table;					// массив строк таблицы лексем
	};

	LexTable Create(int size);					// создать таблицу лексем
	void Add(LexTable& lextable, Entry entry);	// добавление лексем
	Entry GetEntry(LexTable& lextable, int n);	// получить строку таблицы лексем
	void Delete(LexTable& lextable);			// удалить таблицу лексем (освободить память)
}