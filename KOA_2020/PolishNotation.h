#pragma once
#include "LT.h"
#include "IT.h"
#define LEX_PARAMS_COUNT '@'

namespace PolishNotation 
{
	struct Operator
	{
		char operation;
		int priority;
	};
	void TransformToPolishNotation(LT::LexTable& lextable, IT::IdTable& idtable);
	bool PolishNotationExpression(int positionAfterAssignment, LT::LexTable& lextable, IT::IdTable& idtable);
}	