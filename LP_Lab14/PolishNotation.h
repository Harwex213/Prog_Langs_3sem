#pragma once
#include "LT.h"
#include "IT.h"

#define LEXEMA lextable.table[lextable_pos].lexema[LEXEMA_FIXSIZE - 1]
#define LEX_PARAMS_COUNT '@'

namespace PolishNotation 
{
	struct Operator
	{
		char operation;
		int priority;
	};
	void TransformToPolishNotation(const LT::LexTable& lextable, const IT::IdTable& idtable);
	void FindExpression(std::vector<int>& expressionsPos, const LT::LexTable& lextable);
	bool PolishNotation(
		int					lextable_pos,
		const LT::LexTable& lextable,
		const IT::IdTable& idtable
		);
}	