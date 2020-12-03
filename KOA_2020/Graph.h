#pragma once
#include "LT.h"
#define GRAPH_UINT LEX_UINT, string, 5, \
FST::NODE(1, FST::RELATION('u', 1)), \
FST::NODE(1, FST::RELATION('i', 2)), \
FST::NODE(1, FST::RELATION('n', 3)), \
FST::NODE(1, FST::RELATION('t', 4)), \
FST::NODE()

#define GRAPH_STRING LEX_STRING, string, 7, \
FST::NODE(1, FST::RELATION('s', 1)), \
FST::NODE(1, FST::RELATION('t', 2)), \
FST::NODE(1, FST::RELATION('r', 3)), \
FST::NODE(1, FST::RELATION('i', 4)), \
FST::NODE(1, FST::RELATION('n', 5)), \
FST::NODE(1, FST::RELATION('g', 6)), \
FST::NODE()

#define GRAPH_BOOL LEX_BOOL, string, 5, \
FST::NODE(1, FST::RELATION('b', 1)), \
FST::NODE(1, FST::RELATION('o', 2)), \
FST::NODE(1, FST::RELATION('o', 3)), \
FST::NODE(1, FST::RELATION('l', 4)), \
FST::NODE()

#define GRAPH_FLOAT LEX_FLOAT, string, 6, \
FST::NODE(1, FST::RELATION('f', 1)), \
FST::NODE(1, FST::RELATION('l', 2)), \
FST::NODE(1, FST::RELATION('o', 3)), \
FST::NODE(1, FST::RELATION('a', 4)), \
FST::NODE(1, FST::RELATION('t', 5)), \
FST::NODE()

#define GRAPH_INCLUDE LEX_INCLUDE, string, 9, \
FST::NODE(1, FST::RELATION('i', 1)), \
FST::NODE(1, FST::RELATION('n', 2)), \
FST::NODE(1, FST::RELATION('c', 3)), \
FST::NODE(1, FST::RELATION('l', 4)), \
FST::NODE(1, FST::RELATION('u', 6)), \
FST::NODE(1, FST::RELATION('d', 7)), \
FST::NODE(1, FST::RELATION('e', 8)), \
FST::NODE()

#define GRAPH_FUNCTION LEX_FUNCTION, string, 9, \
FST::NODE(1, FST::RELATION('f', 1)), \
FST::NODE(1, FST::RELATION('u', 2)), \
FST::NODE(1, FST::RELATION('n', 3)), \
FST::NODE(1, FST::RELATION('c', 4)), \
FST::NODE(1, FST::RELATION('t', 5)), \
FST::NODE(1, FST::RELATION('i', 6)), \
FST::NODE(1, FST::RELATION('o', 7)), \
FST::NODE(1, FST::RELATION('n', 8)), \
FST::NODE()

#define GRAPH_IF LEX_IF, string, 3, \
FST::NODE(1, FST::RELATION('i', 1)), \
FST::NODE(1, FST::RELATION('f', 2)), \
FST::NODE()

#define GRAPH_WHILE LEX_WHILE, string, 6, \
FST::NODE(1, FST::RELATION('w', 1)), \
FST::NODE(1, FST::RELATION('h', 2)), \
FST::NODE(1, FST::RELATION('i', 3)), \
FST::NODE(1, FST::RELATION('l', 4)), \
FST::NODE(1, FST::RELATION('e', 5)), \
FST::NODE()

#define GRAPH_MAIN LEX_MAIN, string, 5, \
FST::NODE(1, FST::RELATION('m', 1)), \
FST::NODE(1, FST::RELATION('a', 2)), \
FST::NODE(1, FST::RELATION('i', 3)), \
FST::NODE(1, FST::RELATION('n', 4)), \
FST::NODE()

#define GRAPH_RETURN LEX_RETURN, string, 7, \
FST::NODE(1, FST::RELATION('r', 1)), \
FST::NODE(1, FST::RELATION('e', 2)), \
FST::NODE(1, FST::RELATION('t', 3)), \
FST::NODE(1, FST::RELATION('u', 4)), \
FST::NODE(1, FST::RELATION('r', 5)), \
FST::NODE(1, FST::RELATION('n', 6)), \
FST::NODE()

#define GRAPH_PARENTHESES_LEFT LEX_PARENTHESES_LEFT, string, 2, \
FST::NODE(1, FST::RELATION('(', 0)), \
FST::NODE()


#define GRAPH_PARENTHESES_RIGHT LEX_PARENTHESES_RIGHT, string, 2, \
FST::NODE(1, FST::RELATION(')', 0)), \
FST::NODE()


#define GRAPH_BRACKETS_LEFT LEX_BRACKETS_LEFT, string, 2, \
FST::NODE(1, FST::RELATION('[', 0)), \
FST::NODE()


#define GRAPH_BRACKETS_RIGHT LEX_BRACKETS_RIGHT, string, 2, \
FST::NODE(1, FST::RELATION(']', 0)), \
FST::NODE()


#define GRAPH_BRACES_LEFT LEX_BRACES_LEFT, string, 2, \
FST::NODE(1, FST::RELATION('{', 0)), \
FST::NODE()


#define GRAPH_BRACES_RIGHT LEX_BRACES_RIGHT, string, 2, \
FST::NODE(1, FST::RELATION('}', 0)), \
FST::NODE()


#define GRAPH_PLUS LEX_PLUS, string, 2, \
FST::NODE(1, FST::RELATION('+', 0)), \
FST::NODE()


#define GRAPH_MINUS LEX_MINUS, string, 2, \
FST::NODE(1, FST::RELATION('-', 0)), \
FST::NODE()


#define GRAPH_MULTIPLY LEX_MULTIPLY, string, 2, \
FST::NODE(1, FST::RELATION('*', 0)), \
FST::NODE()


#define GRAPH_DIVISION LEX_DIVISION, string, 2, \
FST::NODE(1, FST::RELATION('/', 0)), \
FST::NODE()


#define GRAPH_EQUALLY LEX_EQUALLY, string, 3, \
FST::NODE(1, FST::RELATION('=', 1)), \
FST::NODE(1, FST::RELATION('=', 2)), \
FST::NODE()

#define GRAPH_NON_EQUALLY LEX_NON_EQUALLY, string, 3, \
FST::NODE(1, FST::RELATION('!', 1)), \
FST::NODE(1, FST::RELATION('=', 2)), \
FST::NODE()

#define GRAPH_MORE LEX_MORE, string, 2, \
FST::NODE(1, FST::RELATION('>', 0)), \
FST::NODE()


#define GRAPH_LESS LEX_LESS, string, 2, \
FST::NODE(1, FST::RELATION('<', 0)), \
FST::NODE()


#define GRAPH_MORE_OR_EQUAL LEX_MORE_OR_EQUAL, string, 3, \
FST::NODE(1, FST::RELATION('>', 1)), \
FST::NODE(1, FST::RELATION('=', 2)), \
FST::NODE()

#define GRAPH_LESS_OR_EQUAL LEX_LESS_OR_EQUAL, string, 3, \
FST::NODE(1, FST::RELATION('<', 1)), \
FST::NODE(1, FST::RELATION('=', 2)), \
FST::NODE()

#define GRAPH_OR LEX_OR, string, 2, \
FST::NODE(1, FST::RELATION('|', 0)), \
FST::NODE()


#define GRAPH_AND LEX_AND, string, 2, \
FST::NODE(1, FST::RELATION('&', 0)), \
FST::NODE()


#define GRAPH_INVERSION LEX_INVERSION, string, 2, \
FST::NODE(1, FST::RELATION('~', 0)), \
FST::NODE()


#define GRAPH_ASSIGNMENT LEX_ASSIGNMENT, string, 2, \
FST::NODE(1, FST::RELATION('=', 0)), \
FST::NODE()


#define GRAPH_COMMA LEX_COMMA, string, 2, \
FST::NODE(1, FST::RELATION(',', 0)), \
FST::NODE()


#define GRAPH_SEMICOLON LEX_SEMICOLON, string, 2, \
FST::NODE(1, FST::RELATION(';', 0)), \
FST::NODE()


#define GRAPH_IDENTIFICATOR LEX_IDENTIFICATOR, string, 2, \
FST::NODE(52, \
	FST::RELATION('a', 1), \
	FST::RELATION('b', 1), \
	FST::RELATION('c', 1), \
	FST::RELATION('d', 1), \
	FST::RELATION('e', 1), \
	FST::RELATION('f', 1), \
	FST::RELATION('g', 1), \
	FST::RELATION('h', 1), \
	FST::RELATION('i', 1), \
	FST::RELATION('j', 1), \
	FST::RELATION('k', 1), \
	FST::RELATION('l', 1), \
	FST::RELATION('m', 1), \
	FST::RELATION('n', 1), \
	FST::RELATION('o', 1), \
	FST::RELATION('p', 1), \
	FST::RELATION('q', 1), \
	FST::RELATION('r', 1), \
	FST::RELATION('s', 1), \
	FST::RELATION('t', 1), \
	FST::RELATION('u', 1), \
	FST::RELATION('v', 1), \
	FST::RELATION('w', 1), \
	FST::RELATION('x', 1), \
	FST::RELATION('y', 1), \
	FST::RELATION('z', 1), \
	FST::RELATION('A', 1), \
	FST::RELATION('B', 1), \
	FST::RELATION('C', 1), \
	FST::RELATION('D', 1), \
	FST::RELATION('E', 1), \
	FST::RELATION('F', 1), \
	FST::RELATION('G', 1), \
	FST::RELATION('H', 1), \
	FST::RELATION('I', 1), \
	FST::RELATION('J', 1), \
	FST::RELATION('K', 1), \
	FST::RELATION('L', 1), \
	FST::RELATION('M', 1), \
	FST::RELATION('N', 1), \
	FST::RELATION('O', 1), \
	FST::RELATION('P', 1), \
	FST::RELATION('Q', 1), \
	FST::RELATION('R', 1), \
	FST::RELATION('S', 1), \
	FST::RELATION('T', 1), \
	FST::RELATION('U', 1), \
	FST::RELATION('V', 1), \
	FST::RELATION('W', 1), \
	FST::RELATION('X', 1), \
	FST::RELATION('Y', 1), \
	FST::RELATION('Z', 1)), \
FST::NODE(63, \
	FST::RELATION('a', 1), \
	FST::RELATION('b', 1), \
	FST::RELATION('c', 1), \
	FST::RELATION('d', 1), \
	FST::RELATION('e', 1), \
	FST::RELATION('f', 1), \
	FST::RELATION('g', 1), \
	FST::RELATION('h', 1), \
	FST::RELATION('i', 1), \
	FST::RELATION('j', 1), \
	FST::RELATION('k', 1), \
	FST::RELATION('l', 1), \
	FST::RELATION('m', 1), \
	FST::RELATION('n', 1), \
	FST::RELATION('o', 1), \
	FST::RELATION('p', 1), \
	FST::RELATION('q', 1), \
	FST::RELATION('r', 1), \
	FST::RELATION('s', 1), \
	FST::RELATION('t', 1), \
	FST::RELATION('u', 1), \
	FST::RELATION('v', 1), \
	FST::RELATION('w', 1), \
	FST::RELATION('x', 1), \
	FST::RELATION('y', 1), \
	FST::RELATION('z', 1), \
	FST::RELATION('A', 1), \
	FST::RELATION('B', 1), \
	FST::RELATION('C', 1), \
	FST::RELATION('D', 1), \
	FST::RELATION('E', 1), \
	FST::RELATION('F', 1), \
	FST::RELATION('G', 1), \
	FST::RELATION('H', 1), \
	FST::RELATION('I', 1), \
	FST::RELATION('J', 1), \
	FST::RELATION('K', 1), \
	FST::RELATION('L', 1), \
	FST::RELATION('M', 1), \
	FST::RELATION('N', 1), \
	FST::RELATION('O', 1), \
	FST::RELATION('P', 1), \
	FST::RELATION('Q', 1), \
	FST::RELATION('R', 1), \
	FST::RELATION('S', 1), \
	FST::RELATION('T', 1), \
	FST::RELATION('U', 1), \
	FST::RELATION('V', 1), \
	FST::RELATION('W', 1), \
	FST::RELATION('X', 1), \
	FST::RELATION('Y', 1), \
	FST::RELATION('Z', 1), \
	FST::RELATION('_', 1), \
	FST::RELATION('1', 1), \
	FST::RELATION('1', 1), \
	FST::RELATION('2', 1), \
	FST::RELATION('3', 1), \
	FST::RELATION('4', 1), \
	FST::RELATION('5', 1), \
	FST::RELATION('6', 1), \
	FST::RELATION('7', 1), \
	FST::RELATION('8', 1), \
	FST::RELATION('9', 1))

#define GRAPH_LITERAL_INT LEX_LITERAL, string, 3, \
FST::NODE(10, \
	FST::RELATION('1', 1), \
	FST::RELATION('2', 1), \
	FST::RELATION('3', 1), \
	FST::RELATION('4', 1), \
	FST::RELATION('5', 1), \
	FST::RELATION('6', 1), \
	FST::RELATION('7', 1), \
	FST::RELATION('8', 1), \
	FST::RELATION('9', 1), \
	FST::RELATION('0', 1)), \
FST::NODE(11, \
	FST::RELATION('1', 1), \
	FST::RELATION('2', 1), \
	FST::RELATION('3', 1), \
	FST::RELATION('4', 1), \
	FST::RELATION('5', 1), \
	FST::RELATION('6', 1), \
	FST::RELATION('7', 1), \
	FST::RELATION('8', 1), \
	FST::RELATION('9', 1), \
	FST::RELATION('0', 1), \
	FST::RELATION('.', 2)), \
FST::NODE(10, \
	FST::RELATION('1', 2), \
	FST::RELATION('2', 2), \
	FST::RELATION('3', 2), \
	FST::RELATION('4', 2), \
	FST::RELATION('5', 2), \
	FST::RELATION('6', 2), \
	FST::RELATION('7', 2), \
	FST::RELATION('8', 2), \
	FST::RELATION('9', 2), \
	FST::RELATION('0', 2))

#define GRAPH_LITERAL_STRING LEX_LITERAL, string, 3, \
FST::NODE(1, FST::RELATION('\"', 1)), \
FST::NODE(158, \
	FST::RELATION(' ', 1), \
	FST::RELATION('a', 1), \
	FST::RELATION('b', 1), \
	FST::RELATION('c', 1), \
	FST::RELATION('d', 1), \
	FST::RELATION('e', 1), \
	FST::RELATION('f', 1), \
	FST::RELATION('g', 1), \
	FST::RELATION('h', 1), \
	FST::RELATION('i', 1), \
	FST::RELATION('j', 1), \
	FST::RELATION('k', 1), \
	FST::RELATION('l', 1), \
	FST::RELATION('m', 1), \
	FST::RELATION('n', 1), \
	FST::RELATION('o', 1), \
	FST::RELATION('p', 1), \
	FST::RELATION('q', 1), \
	FST::RELATION('r', 1), \
	FST::RELATION('s', 1), \
	FST::RELATION('t', 1), \
	FST::RELATION('u', 1), \
	FST::RELATION('v', 1), \
	FST::RELATION('w', 1), \
	FST::RELATION('x', 1), \
	FST::RELATION('y', 1), \
	FST::RELATION('z', 1), \
	FST::RELATION('A', 1), \
	FST::RELATION('B', 1), \
	FST::RELATION('C', 1), \
	FST::RELATION('D', 1), \
	FST::RELATION('E', 1), \
	FST::RELATION('F', 1), \
	FST::RELATION('G', 1), \
	FST::RELATION('H', 1), \
	FST::RELATION('I', 1), \
	FST::RELATION('J', 1), \
	FST::RELATION('K', 1), \
	FST::RELATION('L', 1), \
	FST::RELATION('M', 1), \
	FST::RELATION('N', 1), \
	FST::RELATION('O', 1), \
	FST::RELATION('P', 1), \
	FST::RELATION('Q', 1), \
	FST::RELATION('R', 1), \
	FST::RELATION('S', 1), \
	FST::RELATION('T', 1), \
	FST::RELATION('U', 1), \
	FST::RELATION('V', 1), \
	FST::RELATION('W', 1), \
	FST::RELATION('X', 1), \
	FST::RELATION('Y', 1), \
	FST::RELATION('Z', 1), \
	FST::RELATION('0', 1), \
	FST::RELATION('1', 1), \
	FST::RELATION('2', 1), \
	FST::RELATION('3', 1), \
	FST::RELATION('4', 1), \
	FST::RELATION('5', 1), \
	FST::RELATION('6', 1), \
	FST::RELATION('7', 1), \
	FST::RELATION('8', 1), \
	FST::RELATION('9', 1), \
	FST::RELATION('à', 1), \
	FST::RELATION('á', 1), \
	FST::RELATION('â', 1), \
	FST::RELATION('ã', 1), \
	FST::RELATION('ä', 1), \
	FST::RELATION('å', 1), \
	FST::RELATION('¸', 1), \
	FST::RELATION('æ', 1), \
	FST::RELATION('ç', 1), \
	FST::RELATION('è', 1), \
	FST::RELATION('é', 1), \
	FST::RELATION('ê', 1), \
	FST::RELATION('ë', 1), \
	FST::RELATION('ì', 1), \
	FST::RELATION('í', 1), \
	FST::RELATION('î', 1), \
	FST::RELATION('ï', 1), \
	FST::RELATION('ð', 1), \
	FST::RELATION('ñ', 1), \
	FST::RELATION('ò', 1), \
	FST::RELATION('ó', 1), \
	FST::RELATION('ô', 1), \
	FST::RELATION('õ', 1), \
	FST::RELATION('ö', 1), \
	FST::RELATION('÷', 1), \
	FST::RELATION('ø', 1), \
	FST::RELATION('ù', 1), \
	FST::RELATION('ü', 1), \
	FST::RELATION('ú', 1), \
	FST::RELATION('û', 1), \
	FST::RELATION('ý', 1), \
	FST::RELATION('þ', 1), \
	FST::RELATION('ÿ', 1), \
	FST::RELATION('À', 1), \
	FST::RELATION('Á', 1), \
	FST::RELATION('Â', 1), \
	FST::RELATION('Ã', 1), \
	FST::RELATION('Ä', 1), \
	FST::RELATION('Å', 1), \
	FST::RELATION('¨', 1), \
	FST::RELATION('Æ', 1), \
	FST::RELATION('Ç', 1), \
	FST::RELATION('È', 1), \
	FST::RELATION('É', 1), \
	FST::RELATION('Ê', 1), \
	FST::RELATION('Ë', 1), \
	FST::RELATION('Ì', 1), \
	FST::RELATION('Í', 1), \
	FST::RELATION('Î', 1), \
	FST::RELATION('Ï', 1), \
	FST::RELATION('Ð', 1), \
	FST::RELATION('Ñ', 1), \
	FST::RELATION('Ò', 1), \
	FST::RELATION('Ó', 1), \
	FST::RELATION('Ô', 1), \
	FST::RELATION('Õ', 1), \
	FST::RELATION('Ö', 1), \
	FST::RELATION('×', 1), \
	FST::RELATION('Ø', 1), \
	FST::RELATION('Ù', 1), \
	FST::RELATION('Ü', 1), \
	FST::RELATION('Ú', 1), \
	FST::RELATION('Û', 1), \
	FST::RELATION('Ý', 1), \
	FST::RELATION('Þ', 1), \
	FST::RELATION('ß', 1), \
	FST::RELATION('=', 1), \
	FST::RELATION('+', 1), \
	FST::RELATION('-', 1), \
	FST::RELATION('*', 1), \
	FST::RELATION('/', 1), \
	FST::RELATION('(', 1), \
	FST::RELATION(')', 1), \
	FST::RELATION('{', 1), \
	FST::RELATION('}', 1), \
	FST::RELATION('[', 1), \
	FST::RELATION(']', 1), \
	FST::RELATION(';', 1), \
	FST::RELATION(',', 1), \
	FST::RELATION('?', 1), \
	FST::RELATION('!', 1), \
	FST::RELATION('#', 1), \
	FST::RELATION('\'', 1), \
	FST::RELATION('`', 1), \
	FST::RELATION('^', 1), \
	FST::RELATION('@', 1), \
	FST::RELATION('_', 1), \
	FST::RELATION('\\', 1), \
	FST::RELATION('%', 1), \
	FST::RELATION('¹', 1), \
	FST::RELATION('&', 1), \
	FST::RELATION('~', 1), \
	FST::RELATION('|', 1), \
	FST::RELATION('?', 1), \
	FST::RELATION('\"', 2)), \
FST::NODE()

#define GRAPH_TRUE LEX_TRUE, string, 5, \
FST::NODE(1, FST::RELATION('t', 1)), \
FST::NODE(1, FST::RELATION('r', 2)), \
FST::NODE(1, FST::RELATION('u', 3)), \
FST::NODE(1, FST::RELATION('e', 4)), \
FST::NODE()

#define GRAPH_FALSE LEX_FALSE, string, 6, \
FST::NODE(1, FST::RELATION('f', 1)), \
FST::NODE(1, FST::RELATION('a', 2)), \
FST::NODE(1, FST::RELATION('l', 3)), \
FST::NODE(1, FST::RELATION('s', 4)), \
FST::NODE(1, FST::RELATION('e', 5)), \
FST::NODE()

#define GRAPHS_AMOUNT	37
#define FILL_NULES_10	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
#define FILL_NULES_100	FILL_NULES_10, FILL_NULES_10, FILL_NULES_10, FILL_NULES_10, FILL_NULES_10, \
						FILL_NULES_10, FILL_NULES_10, FILL_NULES_10, FILL_NULES_10, FILL_NULES_10
#define FILL_NULES_256	FILL_NULES_100, FILL_NULES_100, FILL_NULES_10, FILL_NULES_10, FILL_NULES_10, FILL_NULES_10, FILL_NULES_10, \
						NULL, NULL, NULL, NULL, NULL, NULL

#define GRAPHS_INITILIZATION \
FST::FST fst1(GRAPH_UINT); \
FST::FST fst2(GRAPH_STRING); \
FST::FST fst3(GRAPH_BOOL); \
FST::FST fst4(GRAPH_FLOAT); \
FST::FST fst5(GRAPH_INCLUDE); \
FST::FST fst6(GRAPH_FUNCTION); \
FST::FST fst7(GRAPH_IF); \
FST::FST fst8(GRAPH_WHILE); \
FST::FST fst9(GRAPH_MAIN); \
FST::FST fst10(GRAPH_RETURN); \
FST::FST fst11(GRAPH_PARENTHESES_LEFT); \
FST::FST fst12(GRAPH_PARENTHESES_RIGHT); \
FST::FST fst13(GRAPH_BRACKETS_LEFT); \
FST::FST fst14(GRAPH_BRACKETS_RIGHT); \
FST::FST fst15(GRAPH_BRACES_LEFT); \
FST::FST fst16(GRAPH_BRACES_RIGHT); \
FST::FST fst17(GRAPH_PLUS); \
FST::FST fst18(GRAPH_MINUS); \
FST::FST fst19(GRAPH_MULTIPLY); \
FST::FST fst20(GRAPH_DIVISION); \
FST::FST fst21(GRAPH_EQUALLY); \
FST::FST fst22(GRAPH_NON_EQUALLY); \
FST::FST fst23(GRAPH_MORE); \
FST::FST fst24(GRAPH_LESS); \
FST::FST fst25(GRAPH_MORE_OR_EQUAL); \
FST::FST fst26(GRAPH_LESS_OR_EQUAL); \
FST::FST fst27(GRAPH_OR); \
FST::FST fst28(GRAPH_AND); \
FST::FST fst29(GRAPH_INVERSION); \
FST::FST fst30(GRAPH_ASSIGNMENT); \
FST::FST fst31(GRAPH_COMMA); \
FST::FST fst32(GRAPH_SEMICOLON); \
FST::FST fst33(GRAPH_IDENTIFICATOR); \
FST::FST fst34(GRAPH_LITERAL_INT); \
FST::FST fst35(GRAPH_LITERAL_STRING); \
FST::FST fst36(GRAPH_TRUE); \
FST::FST fst37(GRAPH_FALSE);

namespace Graphs
{
	struct GRAPHS
	{
		char* string = NULL;
		FST::FST* graphs[256]= { FILL_NULES_256 };

		GRAPHS()
		{
			GRAPHS_INITILIZATION;
			FST::FST* fstArray = new FST::FST[GRAPHS_AMOUNT] { fst1, fst2, fst3, fst4, fst5, fst6, fst7, fst8, fst9, fst10,
						fst11, fst12, fst13, fst14, fst15, fst16, fst17, fst18, fst19, fst20,
						fst21, fst22, fst23, fst24, fst25, fst26, fst27, fst28, fst29, fst30,
						fst31, fst32, fst33, fst34, fst35, fst36, fst37};

			for (int i = 0; i < GRAPHS_AMOUNT; i++)
			{
				for (int j = 0; j < fstArray[i].nodes[0].n_relation; j++)
				{
					unsigned char tempSymbol = static_cast<unsigned char>(fstArray[i].nodes[0].relations[j].symbol);
					if (graphs[tempSymbol] == NULL)
						graphs[tempSymbol] = &fstArray[i];
					else
					{
						FST::FST* temp = graphs[tempSymbol];
						while (temp->nextFST != NULL)
							temp = temp->nextFST;
						temp->nextFST = &fstArray[i];
					}
				}
			}
		};
	};
}