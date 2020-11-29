#pragma once
#include <vector>
#pragma warning(disable: 4996)

#define IN_MAX_LEN_TEXT 1024*1024
#define IN_CODE_ENDL	'\n'
#define	IN_VERT_LINE	'|'
#define	IN_WHITE_SPACE  ' '
#define	IN_NULL_STR	'\0'

/*	SYMBOLS:
	[a-z] [A-Z] [0-9] _	! .	:				TRUE SYMBOLS/Long Symbols	(T)
	пробел табул€ци€						WHITESPACE/Wait				(W)
	+ - * / () {} [] ; , | & ~ = <>	~ ^		SEPARATORS/					(S)
	F										FALSE SYMBOLS/Error			(F)
*/
#define IN_CODE_TABLE {\
/* 0  | 1-a | 2-b | 3-c | 4-d | 5-e |  6  |  7  | 8-h |  9  |  A  |  B  |  C  |  D  |  E  |  F  |    */\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::W,  '|',IN::F,IN::F,IN::F,IN::F,IN::F, /*0*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*1*/\
 IN::W,IN::T,IN::F,IN::F,IN::F,IN::F,IN::S,IN::T,IN::S,IN::S,IN::S,IN::S,IN::S,IN::S,IN::T,IN::S, /*2*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::S,IN::S,IN::S,IN::S,IN::S, /*3*/\
 IN::F,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T, /*4*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::S,IN::F,IN::S,IN::S,IN::T, /*5*/\
 IN::F,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T, /*6*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::S,IN::S,IN::S,IN::S,IN::F, /*7*/\
     																								   \
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*8*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*9*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*A*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*B*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T, /*C*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T, /*D*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T, /*E*/\
 IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T,IN::T, /*F*/\
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
		int size = 0;
		int ignor = 0;
		int	lines = 1;

		enum { L = 64, A = 128, S = 256, W = 512, T = 1024, F = 2048, I = 4096 };
		int code[256] = IN_CODE_TABLE;

		std::list<char> symbols;
		std::list<int>  symbolCounter;

		int overageAmount = 0;
		int wordCounter = 0;
		PARSED_WORDS* alfaLxmTable;
	};

	struct ANALYSIS_DATA
	{
		int symbolCounter = 0;
		int positionNumber = 1;
		int lineNumber = 1;
		bool literalIn = false;
		bool wasTrueSymbol = false;

		void WasTrueSymbol(IN& in)
		{
			in.symbolCounter.push_back(symbolCounter);
			symbolCounter = 0;
			wasTrueSymbol = false;
		}
	};

	IN getin(wchar_t* infile);
	void AddWord(IN& in, PARSED_WORDS entry);
	void AnalyzeLetter(int symbol_type, char symbol, ANALYSIS_DATA& interimData, IN& in);
	void ExpandAlfaLxmTable(IN& in);
}