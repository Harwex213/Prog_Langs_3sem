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
			if (lexTable.table[i].lexema == LEX_ASSIGNMENT)
			{
				PolishNotationExpression(i + 1, lexTable, idTable);
			}
		}
	}

	bool PolishNotationExpression(int positionAfterAssignment, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		int lexTablePosition = positionAfterAssignment;
		PolishNotationData data;

		while (lexTable.table[lexTablePosition].lexema != LEX_SEMICOLON)
		{
			data.tempLexEntry = lexTable.table[lexTablePosition];
			switch (data.tempLexEntry.lexema)
			{
				case LEX_LITERAL:
				case LEX_IDENTIFICATOR:
				{
					// Если в параметрах + стек Параметров не пустой -> увеличиваем количество фактических параметров.
					if (data.stackCFunc.isParams && !data.stackCFunc.stackParams.empty())
						data.stackCFunc.stackParams[data.stackCFunc.countFunction]++;

					// Смотрим -> фунция или переменная.
					IT::Entry tempIdEntry = IT::GetEntry(idTable, data.tempLexEntry.idxTI);
					if (tempIdEntry.idType == IT::FUNCTION)
					{
						// Мы в параметрах.
						data.stackCFunc.isParams = true;
						// Сохраняем лексему вызванной функции.
						data.stackCFunc.calledFunction.push_back(data.tempLexEntry);
						// Заносим счётчик новой функции.
						data.stackCFunc.stackParams.push_back(0);
						data.stackCFunc.countFunction++;
					}
					else
						data.resultChain.push_back(data.tempLexEntry);

					break;
				}
				case LEX_COMPARISONS:
				case LEX_UNARY:
				case LEX_BINARIES:
				{
					data.transformDone = true;
					data.SetOperationPriority();
					data.AnalyzePriority();
					break;
				}
				case LEX_PARENTHESES_LEFT:
				{
					if (data.stackCFunc.isParams)
						goto LeftBrackets;
					data.MetParethesisLeft();
					break;
				}
				case LEX_PARENTHESES_RIGHT:
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
				case LEX_BRACES_LEFT:
				{
				LeftBrackets:
					data.MetBracketsLeft();
					break;
				}
				case LEX_BRACES_RIGHT:
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