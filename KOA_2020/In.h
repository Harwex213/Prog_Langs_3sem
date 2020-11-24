#pragma once
#include <vector>
#pragma warning(disable: 4996)

#define IN_MAX_LEN_TEXT 1024*1024
#define IN_CODE_ENDL	'\n'
#define	IN_VERT_LINE	'|'
#define	IN_WHITE_SPACE  ' '
#define	IN_NULL_STR	'\0'

/*	ALLOWED SYMBOLS:
	a-Z A-Z _								- enum T (True)
	Табуляция && пробелы					- enum W (Whitespace)
	& () * + , / ; <> =  ? 					- enum S (Separate)
	А-Я а-я - . : @	^						- enum A (Allowed)
	' 1-9									- enum L (Literal)

	I - Ignor
	F - False
*/
#define IN_CODE_TABLE {\
/* 0  | 1-a | 2-b | 3-c | 4-d | 5-e |  6  |  7  | 8-h |  9  |  A  |  B  |  C  |  D  |  E  |  F  |    */\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::W,'|'  ,IN::F,IN::F,IN::F,IN::F,IN::F, /*0*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*1*/\
 IN::W,IN::F,IN::T,IN::F,IN::F,IN::F,IN::S,IN::L,IN::S,IN::S,IN::S,IN::S,IN::S,IN::S,IN::A,IN::S, /*2*/\
 IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::L,IN::A,IN::S,IN::S,IN::S,IN::S,IN::S, /*3*/\
 IN::A,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T, /*4*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::S,IN::F,IN::S,IN::A,IN::T, /*5*/\
 IN::F,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T, /*6*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::S,IN::F,IN::S,IN::F,IN::F, /*7*/\
     																								   \
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*8*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*9*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*A*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*B*/\
 IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A, /*C*/\
 IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A, /*D*/\
 IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A, /*E*/\
 IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A,IN::A, /*F*/\
}

namespace In
{
	struct PARSED_WORDS
	{
		char* text;			 //word
		int position = 1;	 //Position of word
		int line = 1;		 //Line of word
	};

	struct IN
	{
		int size = 0;		//symbols amount of in_text
		int ignor = 0;		//ingored symbols
		int	lines = 1;		//how many lines in in_text
		unsigned char* text;
		enum { L = 64, A = 128, S = 256, W = 512, T = 1024, F = 2048, I = 4096 };
		int code[256] = IN_CODE_TABLE;

		int overageAmount = 0;
		int wordCounter = 0;
		PARSED_WORDS* alfaLxmTable;
	};

	IN getin(wchar_t* infile);
	void addword(IN& in, PARSED_WORDS entry);
	void expandAlfaLxmTable(IN& in);
}