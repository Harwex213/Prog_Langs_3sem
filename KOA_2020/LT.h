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
#define	LEX_ELSE					'e'
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

#define PARM_LEX_DEFAULT_EXT L".lex.txt" //для файла с итогом лексического анализa(идентификаторы и литералы)

namespace LT							// таблица лексем
{
	struct Entry						// строка таблицы лексем
	{
		char lexema = '\0';
		int line = 0;
		int position = 0;
		int idxTI = LT_TI_NULLXDX;
	};

	struct LexTable						// экземпляр таблицы лексем
	{
		int maxsize;					// емкость таблицы лексем < LT_MAXSIZE
		int current_size;				// текущий размер таблицы лексем < maxsize
		Entry* table;					// массив строк таблицы лексем
	};

	LexTable Create(int size);					// создать таблицу лексем
	void AddEntry(LexTable& lextable, Entry entry);	// добавление лексем
	Entry GetEntry(LexTable& lextable, int n);	// получить строку таблицы лексем
	void Delete(LexTable& lextable);			// удалить таблицу лексем (освободить память)
}