#include "stdafx.h"
namespace PolishNotation
{
	void TransformToPolishNotation(const LT::LexTable& lextable, const IT::IdTable& idtable)
	{
		//Больше 9 параметров - сломается
		// Зачем нам [] для функций? (144 строчка)

		vector<int> expressionsPos;
		FindExpression(expressionsPos, lextable);

		for (int i = 0; i < expressionsPos.size(); i++)
		{
			if (PolishNotation(expressionsPos[i], lextable, idtable))
			{
				cout << expressionsPos[i] << ": польская запись построена\n";
			}
			else
				cout << expressionsPos[i] << ": польская запись не построена\n";
		}
	}
	
	void FindExpression(std::vector<int>& expressionsPos, const LT::LexTable& lextable)
	{
		for (int i = 0; i < lextable.current_size; i++)
			if (lextable.table[i].lexema[LEXEMA_FIXSIZE - 1] == LEX_EQUAL_SIGN)
				expressionsPos.push_back(i+1);
	}

	bool PolishNotation(int	lextable_pos, const LT::LexTable& lextable, const IT::IdTable& idtable)
	{
		list<char> resultString;
		stack<Operator> stack;
		std::stack<int> stackParams;
		bool transformDone = false;
		bool isParams = false;
		int countParams = 0;

		while (LEXEMA != LEX_SEMICOLON)
		{
			switch (LEXEMA)
			{
				case LEX_LITERAL:
				case LEX_ID:
				{
					char temp;
					if (isParams)
						countParams++;
					IT::Entry entry = IT::GetEntry(idtable, lextable.table[lextable_pos].idxTI);
					if (entry.idtype == IT::F)
					{
						isParams = true;
						if (countParams > 0)
						{
							stackParams.push(countParams);
							countParams = 0;
						}
					}
					else
						resultString.push_back(LEXEMA);
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
						char temp;
						while (!stack.empty() &&
							stack.top().priority >= tempOperation.priority &&
							stack.top().operation != LEX_LEFTBRACE			  &&
							stack.top().operation != LEX_LEFTBRACKETS)
						{
							temp = stack.top().operation;
							stack.pop();						
							resultString.push_back(temp);
						}
						stack.push(tempOperation);
					}
					if (isParams)
						countParams--;
					break;
				}
				case LEX_LEFTBRACE:
				{

					Operator tempOperation = { LEXEMA, 0 };
					stack.push(tempOperation);
					break;
				}
				case LEX_RIGHTBRACE:
				{
					char temp;
					while (stack.top().operation != LEX_LEFTBRACE)
					{
						temp = stack.top().operation;
						stack.pop();						//Вносим все операции стека в результ. строку
						resultString.push_back(temp);
					}
					stack.pop();							//Убираем левую скобку

					if (isParams)
					{
						temp = countParams + 48;
						resultString.push_back(LEX_PARAMS_COUNT);
						resultString.push_back(temp);

						while (!stackParams.empty())
						{
							temp = stackParams.top() + 48;
							resultString.push_back(LEX_PARAMS_COUNT);
							resultString.push_back(temp);
							stackParams.pop();
						}

						isParams = false;
						countParams = 0;
					}
					break;
				}
				case LEX_LEFTBRACKETS:
				{
					Operator tempOperation = { LEXEMA, 4 };
					stack.push(tempOperation);
					break;
				}
				case LEX_RIGHTBRACKETS:
				{
					char temp;
					while (stack.top().operation != LEX_LEFTBRACKETS)
					{
						temp = stack.top().operation;
						stack.pop();
						resultString.push_back(temp);
					}
					stack.pop();

					// Зачем нам [] для функций?
					if (isParams)
					{
						temp = countParams + 48;
						resultString.push_back(LEX_PARAMS_COUNT);
						resultString.push_back(temp);

						isParams = false;
						countParams = 0;
					}
					break;
				}
				case LEX_COMMA:
				{
					char temp;
					bool check = true;
					while (check)
					{
						if (stack.top().operation == LEX_LEFTBRACE || stack.top().operation != LEX_LEFTBRACKETS)
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

		{
			char temp;
			while (!stack.empty())
			{
				temp = stack.top().operation;
				stack.pop();						//Вносим все операции стека в результ. строку
				resultString.push_back(temp);
			}
		}

		{
			int count = resultString.size();
			for (int i = 0; i < count; i++)
			{
				cout << resultString.front();
				resultString.pop_front();
			}
			cout << endl;
		}

		return transformDone;
	}
}