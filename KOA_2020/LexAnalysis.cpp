#include "stdafx.h"

namespace LexAnalysis
{
	void Lexer(const In::IN& in, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		Graphs::GRAPHS automat;
		AnalysisData analysisData;
		FST::FST* temp;
		LT::Entry entryLex;
		IT::Entry entryId;

		analysisData.SetGlobalVisibility();

		for (int i = 0; i < in.wordCounter; i++)
		{
			automat.string = in.alfaLxmTable[i].text;

			if (FindGraph(automat.tests[automat.string[0]], temp))
			{
				if (temp->lexema == LEX_IDENTIFICATOR || temp->lexema == LEX_LITERAL)
				{
					SetName(*temp, analysisData, entryId);
					SetVisibility(*temp, analysisData, entryId);
					SetValue(*temp, analysisData, entryId);
				}
				else
				{
					CheckLexema(*temp, analysisData);
					LT::AddEntry(lexTable, entryLex);
				}
			}
			else
				throw ERROR_THROW_IN(122, in.alfaLxmTable[i].line, in.alfaLxmTable[i].position)
		}
		cout << "DONE";
	}

	bool FindGraph(const std::vector<FST::FST*> graph, FST::FST*& temp)
	{
		bool ExecuteDone = false;
		for (int i = 0; !ExecuteDone && i < graph.size(); i++)
		{
			ExecuteDone = FST::execute(*graph[i]);
			temp = graph[i];
		}
		return ExecuteDone;
	}

	void CheckLexema(const FST::FST& temp, AnalysisData& analysisData)
	{
		switch (temp.lexema)
		{
		case LEX_DATATYPE:
			// Устанавливаем тип данных будущего идентификатора и тип идентификатора как переменная.
			analysisData.idType = IT::VARIABLE;
			analysisData.idDataType = temp.idDataType;
			break;
		case LEX_FUNCTION:
			// Предполагаем что мы в функции и устанавливаем тип идентификатора как функцию.
			analysisData.functionIn = true;
			analysisData.idType = IT::FUNCTION;
		case LEX_PARENTHESES_LEFT:
			// Если мы в функции -> устанавливаем тип идентификатора как параметр
			if (analysisData.functionIn)
				analysisData.idType = IT::PARAM;
			analysisData.bracesCounter++;
			break;
		case LEX_PARENTHESES_RIGHT:
			// В любом случае выходим из функции.
			analysisData.functionIn = false;
			analysisData.bracesCounter++;
			break;
		case LEX_MAIN:
			// Устанавливаем видимость "main"
			analysisData.visibility.push_back(*temp.string);
			break;
		case LEX_BRACES_RIGHT:
			if (!analysisData.visibility.empty())
				analysisData.visibility.pop_back();
		case LEX_BRACES_LEFT:
		case LEX_BRACKETS_LEFT:
		case LEX_BRACKETS_RIGHT:
			analysisData.bracesCounter++;
			break;
		default:
			break;
		}
	}

	void SetName(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry)
	{
		int length = strlen(*temp.string);
		if (analysisData.idType == IT::LITERAL)
		{
			entry.idName = (char*)"LITERAL";
		}
		else
		{
			if (length > ID_MAXSIZE)
			{
				cout << "Произошло усечение идентификатора: " << *temp.string << endl;
				length -= ID_MAXSIZE;
			}
			entry.idName = new char[length + 1];
			entry.idName[length] = IN_NULL_STR;
			strncpy(entry.idName, *temp.string, length);
		}
	}

	void SetVisibility(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry)
	{
		if (analysisData.idType == IT::FUNCTION)
		{
			analysisData.visibility.push_back(entry.idName);
			entry.visibility = analysisData.visibility;
		}
	}

	void SetValue(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry)
	{

	}

	void ResetAnalysisData(AnalysisData& analysisData)
	{
		analysisData.idDataType = IT::UNDEF;
		analysisData.idType = IT::U;
	}
}