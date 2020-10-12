#pragma once
#include "LT.h"
#define GRAPH_INT LEX_INTEGER, string, 8, \
FST::NODE(1, FST::RELATION('i', 1)), \
FST::NODE(1, FST::RELATION('n', 2)), \
FST::NODE(1, FST::RELATION('t', 3)), \
FST::NODE(1, FST::RELATION('e', 4)), \
FST::NODE(1, FST::RELATION('g', 5)), \
FST::NODE(1, FST::RELATION('e', 6)), \
FST::NODE(1, FST::RELATION('r', 7)), \
FST::NODE()

#define GRAPH_STR LEX_INTEGER, string, 7, \
FST::NODE(1, FST::RELATION('s', 1)), \
FST::NODE(1, FST::RELATION('t', 2)), \
FST::NODE(1, FST::RELATION('r', 3)), \
FST::NODE(1, FST::RELATION('i', 4)), \
FST::NODE(1, FST::RELATION('n', 5)), \
FST::NODE(1, FST::RELATION('g', 6)), \
FST::NODE()

#define GRAPH_FUN LEX_FUNCTION, string, 9, \
FST::NODE(1, FST::RELATION('f', 1)), \
FST::NODE(1, FST::RELATION('u', 2)), \
FST::NODE(1, FST::RELATION('n', 3)), \
FST::NODE(1, FST::RELATION('c', 4)), \
FST::NODE(1, FST::RELATION('t', 5)), \
FST::NODE(1, FST::RELATION('i', 6)), \
FST::NODE(1, FST::RELATION('o', 7)), \
FST::NODE(1, FST::RELATION('n', 8)), \
FST::NODE()

#define GRAPH_DEC LEX_DECLARE, string, 8, \
FST::NODE(1, FST::RELATION('d', 1)), \
FST::NODE(1, FST::RELATION('e', 2)), \
FST::NODE(1, FST::RELATION('c', 3)), \
FST::NODE(1, FST::RELATION('l', 4)), \
FST::NODE(1, FST::RELATION('a', 5)), \
FST::NODE(1, FST::RELATION('r', 6)), \
FST::NODE(1, FST::RELATION('e', 7)), \
FST::NODE()

#define GRAPH_RET LEX_RETURN, string, 7, \
FST::NODE(1, FST::RELATION('r', 1)), \
FST::NODE(1, FST::RELATION('e', 2)), \
FST::NODE(1, FST::RELATION('t', 3)), \
FST::NODE(1, FST::RELATION('u', 4)), \
FST::NODE(1, FST::RELATION('r', 5)), \
FST::NODE(1, FST::RELATION('n', 6)), \
FST::NODE()

#define GRAPH_PRINT LEX_PRINT, string, 6, \
FST::NODE(1, FST::RELATION('p', 1)), \
FST::NODE(1, FST::RELATION('r', 2)), \
FST::NODE(1, FST::RELATION('i', 3)), \
FST::NODE(1, FST::RELATION('n', 4)), \
FST::NODE(1, FST::RELATION('t', 5)), \
FST::NODE()

#define GRAPH_MAIN LEX_MAIN, string, 5, \
FST::NODE(1, FST::RELATION('m', 1)), \
FST::NODE(1, FST::RELATION('a', 2)), \
FST::NODE(1, FST::RELATION('i', 3)), \
FST::NODE(1, FST::RELATION('n', 4)), \
FST::NODE()

#define GRAPH_SEMICOLON LEX_SEMICOLON, string, 1, \
FST::NODE(1, FST::RELATION(';', 0))

#define GRAPH_COMMA LEX_COMMA, string, 1, \
FST::NODE(1, FST::RELATION(',', 0))

#define GRAPH_PARENTHESES_LEFT LEX_LEFTHESIS, string, 1, \
FST::NODE(1, FST::RELATION('{', 0))

#define GRAPH_PARENTHESES_RIGHT LEX_RIGHTHESIS, string, 1, \
FST::NODE(1, FST::RELATION('}', 0))

#define GRAPH_BRACES_LEFT LEX_LEFTBRACE, string, 1, \
FST::NODE(1, FST::RELATION('(', 0))

#define GRAPH_BRACES_RIGHT LEX_RIGHTBRACE, string, 1, \
FST::NODE(1, FST::RELATION(')', 0))

#define GRAPH_COMPUTATION LEX_COMPUTATION, string, 1, \
FST::NODE(4, \
	FST::RELATION('+', 0), \
	FST::RELATION('-', 0), \
	FST::RELATION('/', 0), \
	FST::RELATION('*', 0))

#define GRAPH_ASSIGN LEX_EQUAL_SIGN, string, 1, \
FST::NODE(1, FST::RELATION('=', 0))

#define GRAPH_LTRL_INT LEX_LITERAL, string, 1, \
FST::NODE(10, \
	FST::RELATION('1', 0), \
	FST::RELATION('2', 0), \
	FST::RELATION('3', 0), \
	FST::RELATION('4', 0), \
	FST::RELATION('5', 0), \
	FST::RELATION('6', 0), \
	FST::RELATION('7', 0), \
	FST::RELATION('8', 0), \
	FST::RELATION('9', 0), \
	FST::RELATION('0', 0))

#define GRAPH_LTRL_STR LEX_LITERAL, string, 3, \
FST::NODE(1, FST::RELATION('\'', 1)), \
FST::NODE(86, \
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
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('�', 1), \
	FST::RELATION('=', 1), \
	FST::RELATION('+', 1), \
	FST::RELATION('-', 1), \
	FST::RELATION('*', 1), \
	FST::RELATION('/', 1), \
	FST::RELATION('(', 1), \
	FST::RELATION(')', 1), \
	FST::RELATION('{', 1), \
	FST::RELATION('}', 1), \
	FST::RELATION(';', 1), \
	FST::RELATION(',', 1), \
	FST::RELATION('?', 1), \
	FST::RELATION('!', 1), \
	FST::RELATION('\'', 2)), \
	FST::NODE()

#define GRAPH_IDENTIFY LEX_ID, string, 1, \
FST::NODE(27, \
	FST::RELATION('a', 0), \
	FST::RELATION('b', 0), \
	FST::RELATION('c', 0), \
	FST::RELATION('d', 0), \
	FST::RELATION('e', 0), \
	FST::RELATION('f', 0), \
	FST::RELATION('g', 0), \
	FST::RELATION('h', 0), \
	FST::RELATION('i', 0), \
	FST::RELATION('j', 0), \
	FST::RELATION('k', 0), \
	FST::RELATION('l', 0), \
	FST::RELATION('m', 0), \
	FST::RELATION('n', 0), \
	FST::RELATION('o', 0), \
	FST::RELATION('p', 0), \
	FST::RELATION('q', 0), \
	FST::RELATION('r', 0), \
	FST::RELATION('s', 0), \
	FST::RELATION('t', 0), \
	FST::RELATION('u', 0), \
	FST::RELATION('v', 0), \
	FST::RELATION('w', 0), \
	FST::RELATION('x', 0), \
	FST::RELATION('y', 0), \
	FST::RELATION('z', 0), \
	FST::RELATION('_', 0))

#define INTEGER_INDEX 0
#define STRING_INDEX 1
#define FUNCTION_INDEX 2
#define DECLARE_INDEX 3
#define RETURN_INDEX 4
#define PRINT_INDEX 5
#define MAIN_INDEX 6
#define SEMICOLON_INDEX 7
#define COMMA_INDEX 8
#define PARENTHESES_LEFT_INDEX 9
#define PARENTHESES_RIGHT_INDEX 10
#define BRACES_LEFT_INDEX 11
#define BRACES_RIGHT_INDEX 12
#define LITERAL_INT_INDEX 13
#define LITERAL_STR_INDEX 14
#define CUMPUTATION_INDEX 15
#define ASSIGN_INDEX 16
#define IDENTIFY_INDEX 17
#define GRAPHS_SIZE 18
#define GRAPH_SELECT_SIZE 49

#define GRAPH_SELECT nothing, 1, \
FST::NODE(GRAPH_SELECT_SIZE, \
	FST::RELATION('i', INTEGER_INDEX), \
	FST::RELATION('s', STRING_INDEX), \
	FST::RELATION('f', FUNCTION_INDEX), \
	FST::RELATION('d', DECLARE_INDEX), \
	FST::RELATION('r', RETURN_INDEX), \
	FST::RELATION('p', PRINT_INDEX), \
	FST::RELATION('m', MAIN_INDEX), \
	FST::RELATION('a', IDENTIFY_INDEX), \
	FST::RELATION('b', IDENTIFY_INDEX), \
	FST::RELATION('c', IDENTIFY_INDEX), \
	FST::RELATION('e', IDENTIFY_INDEX), \
	FST::RELATION('g', IDENTIFY_INDEX), \
	FST::RELATION('h', IDENTIFY_INDEX), \
	FST::RELATION('j', IDENTIFY_INDEX), \
	FST::RELATION('k', IDENTIFY_INDEX), \
	FST::RELATION('l', IDENTIFY_INDEX), \
	FST::RELATION('n', IDENTIFY_INDEX), \
	FST::RELATION('o', IDENTIFY_INDEX), \
	FST::RELATION('q', IDENTIFY_INDEX), \
	FST::RELATION('t', IDENTIFY_INDEX), \
	FST::RELATION('u', IDENTIFY_INDEX), \
	FST::RELATION('v', IDENTIFY_INDEX), \
	FST::RELATION('w', IDENTIFY_INDEX), \
	FST::RELATION('x', IDENTIFY_INDEX), \
	FST::RELATION('y', IDENTIFY_INDEX), \
	FST::RELATION('z', IDENTIFY_INDEX), \
	FST::RELATION(';', SEMICOLON_INDEX), \
	FST::RELATION(',', COMMA_INDEX), \
	FST::RELATION('{', PARENTHESES_LEFT_INDEX), \
	FST::RELATION('}', PARENTHESES_RIGHT_INDEX), \
	FST::RELATION('(', BRACES_LEFT_INDEX), \
	FST::RELATION(')', BRACES_RIGHT_INDEX), \
	FST::RELATION('0', LITERAL_INT_INDEX), \
	FST::RELATION('1', LITERAL_INT_INDEX), \
	FST::RELATION('2', LITERAL_INT_INDEX), \
	FST::RELATION('3', LITERAL_INT_INDEX), \
	FST::RELATION('4', LITERAL_INT_INDEX), \
	FST::RELATION('5', LITERAL_INT_INDEX), \
	FST::RELATION('6', LITERAL_INT_INDEX), \
	FST::RELATION('7', LITERAL_INT_INDEX), \
	FST::RELATION('8', LITERAL_INT_INDEX), \
	FST::RELATION('9', LITERAL_INT_INDEX), \
	FST::RELATION('0', LITERAL_INT_INDEX), \
	FST::RELATION('\'', LITERAL_STR_INDEX), \
	FST::RELATION('+', CUMPUTATION_INDEX), \
	FST::RELATION('-', CUMPUTATION_INDEX), \
	FST::RELATION('/', CUMPUTATION_INDEX), \
	FST::RELATION('*', CUMPUTATION_INDEX), \
	FST::RELATION('=', ASSIGN_INDEX))

#define GRAPHES \
FST::FST fst1(GRAPH_INT); \
FST::FST fst2(GRAPH_STR); \
FST::FST fst3(GRAPH_FUN); \
FST::FST fst4(GRAPH_DEC); \
FST::FST fst5(GRAPH_RET); \
FST::FST fst6(GRAPH_PRINT); \
FST::FST fst7(GRAPH_MAIN); \
FST::FST fst8(GRAPH_SEMICOLON); \
FST::FST fst9(GRAPH_COMMA); \
FST::FST fst10(GRAPH_PARENTHESES_LEFT); \
FST::FST fst11(GRAPH_PARENTHESES_RIGHT); \
FST::FST fst12(GRAPH_BRACES_LEFT); \
FST::FST fst13(GRAPH_BRACES_RIGHT); \
FST::FST fst14(GRAPH_LTRL_INT); \
FST::FST fst15(GRAPH_LTRL_STR); \
FST::FST fst16(GRAPH_COMPUTATION); \
FST::FST fst17(GRAPH_ASSIGN); \
FST::FST fst18(GRAPH_IDENTIFY); \
FST::FST* graphArray = new FST::FST[GRAPHS_SIZE]{ fst1, fst2, fst3, fst4, fst5, fst6, fst7, fst8, fst9, fst10, fst11, fst12, fst13, fst14, fst15, fst16, fst17, fst18 };