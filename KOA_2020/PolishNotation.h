#pragma once
#include "LT.h"
#include "IT.h"
#include "Error.h"
// | Priority	| Operation |
// | 0			| {			|
// | 0			| }			|
// | 1			| , 		|
// | 2			| |			|
// | 3			| &			|
// | 4			| != == 	|
// | 5			| > < 		|
// | 5			| >= <= 	|
// | 6			| +			|
// | 6			| -			|
// | 7			| *			|
// | 7			| /			|
// | 8			| ~			|
// | 9			| [ 		|
// | 9			| ]			|
#define PARETHESIS_PRIORITY 0
#define COMMA_PRIORITY		1
#define OR_PRIORITY			2
#define AND_PRIORITY		3
#define COMPARE_EQ_PRIORITY	4
#define COMPARE_ML_PRIORITY	5
#define PM_PRIORITY			6
#define MD_PRIORITY			7
#define UNARY_PRIORITY		8
#define BRACKETS_PRIORITY	9

#define LEX_CALL_FUNCTION (char)-5
#define LEX_ARRAY_ADDRES (char)-6

namespace PolishNotation 
{
	struct Operator
	{
		LT::Entry savedEntryOperation;
		int priority;
	};
	struct StackCalledFunction
	{
		vector<LT::Entry> calledFunction;
		vector<int> stackParams;
		int countFunction = 0;
		bool isParams = false;
	};
	struct PolishNotationData
	{
		stack<Operator> operationStack;
		Operator tempOperationEntry;

		vector<LT::Entry> resultChain;
		LT::Entry tempLexEntry;

		StackCalledFunction stackCFunc;

		bool transformDone = false;

		void SetOperationPriority()
		{
			tempOperationEntry.savedEntryOperation = tempLexEntry;
			switch (tempLexEntry.operationType)
			{
			case LT::OR:
				tempOperationEntry.priority = OR_PRIORITY;
				break;
			case LT::AND:
				tempOperationEntry.priority = AND_PRIORITY;
				break;
			case LT::EQUALLY:
			case LT::NON_EQUALLY:
				tempOperationEntry.priority = COMPARE_EQ_PRIORITY;
			case LT::MORE:
			case LT::LESS:
			case LT::MORE_OR_EQUAL:
			case LT::LESS_OR_EQUAL:
				tempOperationEntry.priority = COMPARE_ML_PRIORITY;
				break;
			case LT::PLUS:
			case LT::MINUS:
				tempOperationEntry.priority = PM_PRIORITY;
				break;
			case LT::MULTIPLY:
			case LT::DIVISION:
				tempOperationEntry.priority = MD_PRIORITY;
				break;
			case LT::INVERSION:
				tempOperationEntry.priority = UNARY_PRIORITY;
				break;
			}
		}

		void AnalyzePriority()
		{
			// ���� ���� �������� ������ ��� �� ��� ��� ����������� ������ -> ������� ������� Entry.
			if (operationStack.empty() ||
				operationStack.top().savedEntryOperation.lexema == LEX_PARENTHESES_LEFT ||
				operationStack.top().savedEntryOperation.lexema == LEX_BRACES_LEFT)
			{
				operationStack.push(tempOperationEntry);
			}
			else
			{
				// ����������� ��� �������� � �������, ���� ������ �����������. ����� �������� ������� ��������.
				while (!operationStack.empty() && operationStack.top().priority >= tempOperationEntry.priority)
				{
					resultChain.push_back(operationStack.top().savedEntryOperation);
					operationStack.pop();
				}
				operationStack.push(tempOperationEntry);
			}
		}

		void MetParethesisLeft()
		{
			tempOperationEntry.priority = PARETHESIS_PRIORITY;
			tempOperationEntry.savedEntryOperation = tempLexEntry;
			operationStack.push(tempOperationEntry);
		}

		void MetParethesisRight()
		{
			// ������� �� ����� ��� �������� �� ������.
			while (operationStack.top().savedEntryOperation.lexema != LEX_PARENTHESES_LEFT)
			{
				resultChain.push_back(operationStack.top().savedEntryOperation);
				operationStack.pop();
			}
			// � ���������� ������.
			operationStack.pop();
		}

		void MetBracketsLeft()
		{
			tempOperationEntry.priority = BRACKETS_PRIORITY;
			tempOperationEntry.savedEntryOperation = tempLexEntry;
			operationStack.push(tempOperationEntry);
		}

		void MetBracketsRight()
		{
			// ������� �� ����� ��� �������� �� ������.
			while (operationStack.top().savedEntryOperation.lexema != LEX_BRACKETS_LEFT)
			{
				resultChain.push_back(operationStack.top().savedEntryOperation);
				operationStack.pop();
			}
			// � ���������� ������.
			operationStack.pop();
		}
		
		void PushFunctionInfo(const IT::IdTable& idTable)
		{
			// ��������� ����� ���������� ����������� � ��������� ���������� ���� ���������.
			if (!Semantic::CheckFunctionCountParams(stackCFunc.stackParams[stackCFunc.countFunction], stackCFunc.calledFunction[stackCFunc.countFunction], idTable))
				throw ERROR_THROW_IN(SEMANTICS_ERROR_SERIES + 1, tempLexEntry.line, tempLexEntry.position);
			stackCFunc.countFunction--;
			// ������� ���� �� ���� � ����������� ����������. ���� �� -> ������� �����������. ���� ��� -> ������� ��������� ������� �� �������.
			if (stackCFunc.stackParams.empty())
				stackCFunc.isParams = false;
			if (stackCFunc.isParams)
			{
				stackCFunc.calledFunction.pop_back();
				stackCFunc.calledFunction.shrink_to_fit();
				stackCFunc.stackParams.pop_back();
				stackCFunc.stackParams.shrink_to_fit();
			}
		}

		void MetComma()
		{
			bool check = true;
			while (check)
			{
				if (operationStack.top().savedEntryOperation.lexema == LEX_PARENTHESES_LEFT || operationStack.top().savedEntryOperation.lexema == LEX_BRACKETS_LEFT)
					check = false;
				else
				{
					resultChain.push_back(operationStack.top().savedEntryOperation);
					operationStack.pop();
				}
			}
		}

		void PopLastOperations()
		{
			while (!operationStack.empty())
			{
				resultChain.push_back(operationStack.top().savedEntryOperation);
				operationStack.pop();
			}
		}
	};
	void TransformToPolishNotation(LT::LexTable& lextable, IT::IdTable& idtable);
	bool PolishNotationExpression(int positionAfterAssignment, LT::LexTable& lextable, IT::IdTable& idtable);
};