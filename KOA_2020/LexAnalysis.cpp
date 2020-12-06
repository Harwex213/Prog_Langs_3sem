#include "stdafx.h"
#define LEX_ERROR_SERIES 120
#define SEMANTICS_ERROR_SERIES 400

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
					SetIdTypeAndIdDataType(*temp, analysisData, entryId);
					SetName(*temp, analysisData, entryId);
					SetVisibility(*temp, analysisData, entryId);
					SetValue(*temp, analysisData, entryId);
					if (CheckForIdentificator(idTable, entryId))
						IT::AddEntry(idTable, entryId);
					else
						throw ERROR_THROW_IN(SEMANTICS_ERROR_SERIES + 1, in.alfaLxmTable[i].line, in.alfaLxmTable[i].position)
					if (!SetIdxTI(idTable, entryId, entryLex))
						throw ERROR_THROW_IN(SEMANTICS_ERROR_SERIES, in.alfaLxmTable[i].line, in.alfaLxmTable[i].position)
					IT::AddEntry(idTable, entryId);
					ResetAnalysisData(analysisData, entryId);
				}
				else
					CheckLexema(*temp, analysisData);
				SetLexEntry(entryLex, temp->lexema, in.alfaLxmTable[i].line, in.alfaLxmTable[i].position);
				LT::AddEntry(lexTable, entryLex);
			}
			else
				throw ERROR_THROW_IN(LEX_ERROR_SERIES + 1, in.alfaLxmTable[i].line, in.alfaLxmTable[i].position)
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
			analysisData.mainWas++;
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

	void SetIdTypeAndIdDataType(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry)
	{
		if (temp.lexema == LEX_LITERAL)
		{
			analysisData.idType = IT::LITERAL;
			analysisData.idDataType = temp.idDataType;
		}
		entry.idType = analysisData.idType;
		entry.idDataType = analysisData.idDataType;
	}

	void SetName(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry)
	{
		int length = 0;
		if (entry.idType == IT::LITERAL)
		{
			char idNumber[ID_MAXSIZE - 1];
			itoa(analysisData.literalId++, idNumber, 10);
			strcat(analysisData.literalIdChar, idNumber);
			length = strlen(analysisData.literalIdChar);
			entry.idName = new char[length + 1];
			entry.idName[length] = IN_NULL_STR;
			strncpy(entry.idName, analysisData.literalIdChar, length);
			analysisData.literalIdChar[1] = IN_NULL_STR;
		}
		else
		{
			length = strlen(*temp.string);
			if (length > ID_MAXSIZE)
			{
				cout << "Произошло усечение идентификатора: " << *temp.string << endl;
				length = ID_MAXSIZE;
			}
			entry.idName = new char[length + 1];
			entry.idName[length] = IN_NULL_STR;
			strncpy(entry.idName, *temp.string, length);
		}
	}

	void SetVisibility(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry)
	{
		if (entry.idType != IT::LITERAL)
		{
			entry.visibility = analysisData.visibility;
			if (analysisData.idType == IT::FUNCTION)
				analysisData.visibility.push_back(entry.idName);
		}
		else
			entry.visibility.push_back(LITERAL_VISIBILITY);
	}

	void SetValue(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry)
	{

	}

	bool CheckForIdentificator(const IT::IdTable& idTable, IT::Entry& entryId)
	{
		auto tempVisibility = entryId.visibility.rbegin();
		// Проверяем не объявлена ли переменная вне функции.
		if (*tempVisibility == MAIN_VISIBILITY && entryId.idType == IT::VARIABLE)
			return false;
		for (int i = 0; i < idTable.current_size; i++)
		{
			if (*tempVisibility == *idTable.table[i].visibility.rbegin() && (strcmp(entryId.idName, idTable.table[i].idName) == 0) && entryId.idType != IT::U)
				return false;
		}
		return true;
	}

	bool SetIdxTI(const IT::IdTable& idTable, const IT::Entry& entryId, LT::Entry& entryLex)
	{
		// Выставляем у лексемы ссылку на id в таблице идентификаторов.
		entryLex.idxTI = IT::GetId(idTable, entryId.idName, entryId.visibility);
		// Проверка семантики: Необъявленная переменная.
		if (entryLex.idxTI == LT_TI_NULLXDX)
			return false;
		return true;
	}

	void SetLexEntry(LT::Entry& entry, char lexema, int line, int position)
	{	
		entry.lexema = lexema;
		entry.line = line;
		entry.position = position;
	}

	void ResetAnalysisData(AnalysisData& analysisData, IT::Entry& entry)
	{
		entry.visibility.clear();
		delete[] entry.idName;
		analysisData.idDataType = IT::UNDEF;
		analysisData.idType = IT::U;
	}
}