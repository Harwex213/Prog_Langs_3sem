#include "stdafx.h"
#define LEX_ERROR_SERIES 120
#define SEMANTICS_ERROR_SERIES 400
#define LINE in.alfaLxmTable[i].line
#define POSITION in.alfaLxmTable[i].position

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
					switch (SetValue(*temp, analysisData, entryId))
					{
					case GOING_BEYOND_UINT:
						throw ERROR_THROW_IN(SEMANTICS_ERROR_SERIES + 4, LINE, POSITION);
						break;
					case GOING_BEYOND_FLOAT:
						throw ERROR_THROW_IN(SEMANTICS_ERROR_SERIES + 5, LINE, POSITION);
						break;
					case GOING_BEYOND_STRING:
						throw ERROR_THROW_IN(SEMANTICS_ERROR_SERIES + 6, LINE, POSITION);
						break;
					case SUCCESS:
						break;
					}
					switch (CheckForIdentificator(idTable, entryId))
					{
					case OK:
						IT::AddEntry(idTable, entryId);
						break;
					case NOT_DECLARED:
						throw ERROR_THROW_IN(SEMANTICS_ERROR_SERIES, LINE, POSITION)
						break;
					case RE_DECLARATION:
						throw ERROR_THROW_IN(SEMANTICS_ERROR_SERIES + 1, LINE, POSITION);
						break;
					case GLOBAL_DECLARATION:
						throw ERROR_THROW_IN(SEMANTICS_ERROR_SERIES + 2, LINE, POSITION);
						break;
					case ALREADY_EXIST:
						analysisData.literalId--;
						break;
					}
					SetIdxTIandIdxFirstLE(idTable, lexTable, entryId, entryLex);
					ResetAnalysisData(analysisData, entryId);
				}
				else
					CheckLexema(*temp, analysisData);
				SetLexEntry(entryLex, temp->lexema, LINE, POSITION);
				LT::AddEntry(lexTable, entryLex);
			}
			else
				throw ERROR_THROW_IN(LEX_ERROR_SERIES + 1, LINE, POSITION)
		}
		cout << "DONE";
	}

	bool FindGraph(const std::vector<FST::FST*> graph, FST::FST*& temp)
	{
		bool ExecuteDone = false;
		for (unsigned int i = 0; !ExecuteDone && i < graph.size(); i++)
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
			// Если мы в функции -> устанавливаем тип идентификатора как параметр
			if (analysisData.functionIn)
				analysisData.idType = IT::PARAM;
			analysisData.idDataType = temp.idDataType;
			break;
		case LEX_FUNCTION:
			// Предполагаем что мы в функции и устанавливаем тип идентификатора как функцию.
			analysisData.functionIn = true;
			analysisData.idType = IT::FUNCTION;
			break;
		case LEX_PARENTHESES_LEFT:
			analysisData.bracesCounter++;
			break;
		case LEX_PARENTHESES_RIGHT:
			// В любом случае выходим из функции.
			analysisData.functionIn = false;
			analysisData.bracesCounter--;
			break;
		case LEX_MAIN:
			// Устанавливаем видимость "main"
			analysisData.visibility.push_back(*temp.string);
			analysisData.mainWas++;
			break;
		case LEX_WHILE:
		{
			char idNumber[ID_MAXSIZE - 1];
			itoa(analysisData.whileId++, idNumber, DEC_NUMBER_SYMBOL);
			strcat(analysisData.WhileIdChar, idNumber);
			analysisData.visibility.push_back(analysisData.WhileIdChar);
			analysisData.WhileIdChar[1] = IN_NULL_STR;
			analysisData.whileIn = true;
			break;
		}
		case LEX_IF:
		{
			char idNumber[ID_MAXSIZE - 1];
			itoa(analysisData.ifId++, idNumber, DEC_NUMBER_SYMBOL);
			strcat(analysisData.IfIdChar, idNumber);
			analysisData.visibility.push_back(analysisData.IfIdChar);
			analysisData.IfIdChar[1] = IN_NULL_STR;
			break;
		}
		case LEX_ELSE:
		{
			char idNumber[ID_MAXSIZE - 1];
			itoa(analysisData.elseId++, idNumber, DEC_NUMBER_SYMBOL);
			strcat(analysisData.ElseIdChar, idNumber);
			analysisData.visibility.push_back(analysisData.ElseIdChar);
			analysisData.ElseIdChar[1] = IN_NULL_STR;
			break;
		}
		case LEX_BRACES_LEFT:
			break;
		case LEX_BRACES_RIGHT:
			if (!analysisData.visibility.empty())
				analysisData.visibility.pop_back();
			if (analysisData.whileIn)
				analysisData.whileIn = false;
			break;
		case LEX_BRACKETS_LEFT:
			break;
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
			itoa(analysisData.literalId++, idNumber, DEC_NUMBER_SYMBOL);
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

	SetValueReturnCode SetValue(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry)
	{
		if (entry.idType == IT::LITERAL)
		{
			switch (entry.idDataType)
			{
			case IT::UINT:
			{
				long long checkNumber = strtoll(*temp.string, NULL, DEC_NUMBER_SYMBOL);
				if (checkNumber >= UINT_MIN && checkNumber <= UINT_MAX)
					entry.value.vUint = checkNumber;
				else
					return GOING_BEYOND_UINT;
				break;
			}
			case IT::BOOL:
			{
				if (*temp.string[FIRST_SYMBOL] == FIRST_SYMBOL_TRUE)
					entry.value.vBool = true;
				if (*temp.string[FIRST_SYMBOL] == FIRST_SYMBOL_FALSE)
					entry.value.vBool = false;
				break;
			}
			case IT::FLOAT:
			{
				double checkNumber = strtod(*temp.string, NULL);
				if (checkNumber >= FLT_MIN && checkNumber <= FLT_MAX)
					entry.value.vFloat = checkNumber;
				else
					return GOING_BEYOND_FLOAT;
				break;
			}
			case IT::STRING:
			{
				int checkString = strlen(*temp.string);
				if (checkString > TI_STR_MAXSIZE)
					return GOING_BEYOND_STRING;
				entry.value.vString.length = checkString;
				strcpy(entry.value.vString.string, *temp.string);
				break;
			}
			}
		}
		else
		{
			switch (entry.idDataType)
			{
			case IT::UINT:
				entry.value.vUint = 0;
				break;
			case IT::BOOL:
				entry.value.vBool = false;
				break;
			case IT::FLOAT:
				entry.value.vFloat = 0;
				break;
			case IT::STRING:
				entry.value.vString.string[0] = TI_STR_DEFAULT;
				entry.value.vString.length = 0;
				break;
			}
		}
		return SUCCESS;
	}

	CheckIdentificatorReturnCode CheckForIdentificator(const IT::IdTable& idTable, IT::Entry& entryId)
	{
		auto tempVisibility = entryId.visibility.rbegin();
		// Проверяем не объявлена ли переменная вне функции.
		if (*tempVisibility == MAIN_VISIBILITY && entryId.idType == IT::VARIABLE)
			return GLOBAL_DECLARATION;
		for (int i = 0; i < idTable.current_size; i++)
		{
			// Смотрим по видимости + совпадении имени идентификатора.
			// Далее смотрим по типу идентификатора. U - объявление уже было. 
			if (*tempVisibility == *idTable.table[i].visibility.rbegin() && (strcmp(entryId.idName, idTable.table[i].idName) == 0))
				switch (entryId.idType)
				{
				case IT::U:
					return ALREADY_EXIST;
					break;
				default:
					return RE_DECLARATION;
					break;
				}
			// Проверяем по значению литерала, не был ли создан такой же ранее.
			if (*tempVisibility == *idTable.table[i].visibility.rbegin() && *tempVisibility == LITERAL_VISIBILITY)
			{
				switch (entryId.idDataType)
				{
				case IT::UINT:
					if (entryId.value.vUint == idTable.table[i].value.vUint)
						return ALREADY_EXIST;
					break;
				case IT::BOOL:
					if (entryId.value.vBool == idTable.table[i].value.vBool)
						return ALREADY_EXIST;
					break;
				case IT::FLOAT:
					if (entryId.value.vFloat == idTable.table[i].value.vFloat)
						return ALREADY_EXIST;
					break;
				case IT::STRING:
					if (strcmp(entryId.value.vString.string, idTable.table[i].value.vString.string) == 0)
						return ALREADY_EXIST;
					break;
				}
			}
		}
		// Если совпадений ранее не нашли, но тип идентификатора не определён
		// (не было ключевого слова ранее) ==> использование необъявленного идентификатора.
		if (entryId.idType == IT::U)
			return NOT_DECLARED;
		return OK;
	}

	bool ViewVisibility(std::list<std::string> visibilityThis, std::list<std::string> visibilityThat)
	{
		for (size_t i = 0; i < visibilityThis.size(); i++)
		{

		}
		return false;
	}

	void SetIdxTIandIdxFirstLE(const IT::IdTable& idTable, const LT::LexTable& lexTable, IT::Entry& entryId, LT::Entry& entryLex)
	{
		// Выставляем у лексемы ссылку на id в таблице идентификаторов.
		entryLex.idxTI = IT::GetId(idTable, entryId.idName, entryId.visibility);
		// Выставляем EntryId ссылку в таблице Лексем.
		entryId.idxfirstLE = lexTable.current_size;
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
		entry.idDataType = IT::UNDEF;
		entry.idType = IT::U;
		analysisData.idDataType = IT::UNDEF;
		analysisData.idType = IT::U;
	}
}