#include "stdafx.h"
namespace PolishNotation
{
	void TransformToPolishNotation(LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		// Больше 9 параметров - сломается
		// Если в параметрах поставить просто арифмитическое действие, то сломается
		// Зачем нам [] для функций? (144 строчка)

		for (int i = 0; i < lexTable.current_size; i++)
		{
			if (lexTable.tableTest[i].lexema == LEX_ASSIGNMENT)
			{
				PolishNotationExpression(i + 1, lexTable, idTable);
			}
		}
	}

	bool PolishNotationExpression(int	positionAfterAssignment, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		int lexTablePosition = positionAfterAssignment;

		vector<LT::Entry> resultChain;
		LT::Entry tempLexEntry;
		stack<Operator> stack;
		bool transformDone = false;

		vector<int> stackParams(1, 0);
		int countFunction = 0;
		bool isParams = false;

		while (lexTable.tableTest[lexTablePosition].lexema != LEX_SEMICOLON)
		{
			tempLexEntry = lexTable.tableTest[lexTablePosition];
			switch (tempLexEntry.lexema)
			{
				case LEX_LITERAL:
				case LEX_IDENTIFICATOR:
				{
					if (isParams && !stackParams.empty())
						stackParams[countFunction]++;

					IT::Entry entry = IT::GetEntry(idTable, tempLexEntry.idxTI);
					if (entry.idType == IT::FUNCTION)
					{
						isParams = true;
						if (stackParams[countFunction] > 0)
						{
							stackParams.push_back(0);
							countFunction++;
						}
					}
					else
						resultChain.push_back(tempEntry);

					break;
				}
				case LEX_COMPUTATION:
				{
					transformDone = true;

					Operator tempOperation = { LEXEMA, -1 };
					switch (lextable.table[lextable_pos].arithmeticdata)
					{
						case LT::PLUS:
							tempOperation.operation = LEX_PLUS;
							tempOperation.priority = 1;
							break;
						case LT::MINUS:
							tempOperation.operation = LEX_MINUS;
							tempOperation.priority = 1;
							break;
						case LT::MULTIPLY:
							tempOperation.operation = LEX_MULTIPLY;
							tempOperation.priority = 2;
							break;
						case LT::FISSION:
							tempOperation.operation = LEX_FISSION;
							tempOperation.priority = 2;
							break;
					}

					if (stack.empty() || stack.top().operation == LEX_LEFTBRACE || stack.top().operation == LEX_LEFTBRACKETS)
					{
						stack.push(tempOperation);
					}
					else 
					{
						while (!stack.empty() &&
							stack.top().priority >= tempOperation.priority)
						{
							temp = stack.top().operation;
							stack.pop();						
							resultString.push_back(temp);
						}
						stack.push(tempOperation);
					}
					if (isParams && !stackParams.empty())
						stackParams[countFunction]--;
					break;
				}
				case LEX_LEFTBRACE:
				{
					//if (isParams)
					//	goto LeftBrackets;

					Operator tempOperation = { LEXEMA, 0 };
					stack.push(tempOperation);
					break;
				}
				case LEX_RIGHTBRACE:
				{
					while (stack.top().operation != LEX_LEFTBRACE)
					{
						temp = stack.top().operation;
						stack.pop();						//Вносим все операции стека в результ. строку
						resultString.push_back(temp);
					}
					stack.pop();							//Убираем левую скобку

					if (isParams)
						goto RightBrackets;

					break;
				}
				case LEX_LEFTBRACKETS:
				{
					//LeftBrackets:
					Operator tempOperation = { LEXEMA, 4 };
					stack.push(tempOperation);
					break;
				}
				case LEX_RIGHTBRACKETS:
				{
					while (stack.top().operation != LEX_LEFTBRACKETS)
					{
						temp = stack.top().operation;
						stack.pop();
						resultString.push_back(temp);
					}
					stack.pop();

					if (isParams)
					{
					RightBrackets:
						temp = stackParams[countFunction--] + 48;
						resultString.push_back(LEX_PARAMS_COUNT);
						resultString.push_back(temp);

						if (stackParams.empty())
							isParams = false;
						if (isParams)
							stackParams.pop_back();
					}
					break;
				}
				case LEX_COMMA:
				{
					bool check = true;
					while (check)
					{
						if (stack.top().operation == LEX_LEFTBRACE || stack.top().operation == LEX_LEFTBRACKETS)
							check = false;
						else
						{
							temp = stack.top().operation;
							stack.pop();						//Вносим все операции стека в результ. строку
							resultString.push_back(temp);
						}
					}
					break;
				}
			}
			lextable_pos++;
		}

		while (!stack.empty())
		{
			temp = stack.top().operation;
			stack.pop();						//Вносим все операции стека в результ. строку
			resultString.push_back(temp);
		}

		int count = resultString.size();
		for (int i = 0; i < count; i++)
		{
			cout << resultString.front();
			resultString.pop_front();
		}
		cout << endl;

		return transformDone;
	}
}