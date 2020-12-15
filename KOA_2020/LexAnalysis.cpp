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

		for (int i = 0; i < in.wordCounter; i++)
		{
			automat.string = in.alfaLxmTable[i].text;

			if (FindGraph(automat.tests[automat.string[0]], temp))
			{
				if (temp->lexema == LEX_IDENTIFICATOR || temp->lexema == LEX_LITERAL)
				{
					SetIdType_IdDataType_IdxFirstLE(*temp, analysisData, entryId, lexTable.current_size, idTable.current_size);
					if (analysisData.infoFunctionParamsNeedUpdate)
						SetFunctionParams(analysisData, idTable.current_size);
					SetName(*temp, analysisData, entryId);
					SetVisibility(*temp, analysisData, entryId);
					switch (SetValue(*temp, analysisData, entryId))
					{
					case GOING_BEYOND_UINT:
						throw ERROR_THROW_IN(SEMANTICS_ERROR_SERIES + 3, LINE, POSITION);
						break;
					case GOING_BEYOND_FLOAT:
						throw ERROR_THROW_IN(SEMANTICS_ERROR_SERIES + 5, LINE, POSITION);
						break;
					case GOING_BEYOND_STRING:
						throw ERROR_THROW_IN(SEMANTICS_ERROR_SERIES + 4, LINE, POSITION);
						break;
					case SUCCESS:
						break;
					}
					switch (CheckForIdentificator(idTable, entryId, analysisData))
					{
					case OK:
						IT::AddEntry(idTable, entryId);
						break;
					case VARIABLE_ALREADY_DEAD:
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
						if (entryId.idType == IT::LITERAL)
							analysisData.literalId--;
						break;
					}
					SetIdxTI(idTable, entryId, entryLex);
					ResetAnalysisData(analysisData, entryId);
				}
				else
					CheckLexema(*temp, analysisData, entryLex);
				SetLexEntry(entryLex, temp->lexema, LINE, POSITION);
				if (analysisData.functionNeedUpdate)
					UpdateFunctionParamsInfo(analysisData, idTable);
				LT::AddEntry(lexTable, entryLex);
				ResetEntryLex(entryLex);
			}
			else
				throw ERROR_THROW_IN(LEX_ERROR_SERIES + 1, LINE, POSITION)
		}
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

	void CheckLexema(const FST::FST& temp, AnalysisData& analysisData, LT::Entry& entryLex)
	{
		switch (temp.lexema)
		{
		case LEX_DATATYPE:
			// ������������� ��� ������ �������� �������������� � ��� �������������� ��� ����������.
			analysisData.idType = IT::VARIABLE;
			// ���� �� � ������� -> ������������� ��� �������������� ��� ��������
			if (analysisData.functionIn)
			{
				analysisData.idType = IT::PARAM;
				analysisData.infoFunctionParamsNeedUpdate = true;
			}
			analysisData.idDataType = temp.idDataType;
			break;
		case LEX_FUNCTION:
			// ������������ ��� �� � ������� � ������������� ��� �������������� ��� �������.
			analysisData.functionIn = true;
			analysisData.idType = IT::FUNCTION;
			break;
		case LEX_PARENTHESES_LEFT:
			break;
		case LEX_PARENTHESES_RIGHT:
			if (analysisData.functionIn)
				analysisData.functionNeedUpdate = true;
			// � ����� ������ ������� �� �������.
			analysisData.functionIn = false;
			break;
		case LEX_MAIN:
			// ������������� ��������� "main"
			analysisData.visibilityList.push_front(*temp.string);
			analysisData.mainWas++;
			break;
		case LEX_WHILE:
		{
			analysisData.whileIdString += std::to_string(analysisData.whileId++);
			analysisData.visibilityList.push_front(analysisData.whileIdString);
			analysisData.whileIdString.resize(RESET_TO_ONE);
			analysisData.whileIdString.shrink_to_fit();
			break;
		}
		case LEX_IF:
		{
			analysisData.ifIdString += std::to_string(analysisData.ifId++);
			analysisData.visibilityList.push_front(analysisData.ifIdString);
			analysisData.ifIdString.resize(RESET_TO_ONE);
			analysisData.ifIdString.shrink_to_fit();
			break;
		}
		case LEX_ELSE:
		{
			analysisData.elseIdString += std::to_string(analysisData.elseId++);
			analysisData.visibilityList.push_front(analysisData.elseIdString);
			analysisData.elseIdString.resize(RESET_TO_ONE);
			analysisData.elseIdString.shrink_to_fit();
			break;
		}
		case LEX_BRACES_LEFT:
			analysisData.bracesCounter++;
			break;
		case LEX_BRACES_RIGHT:
			analysisData.bracesCounter--;
			if (analysisData.visibilityList.empty())
			{
				// Error! ������ ����������� ������.
			}
			analysisData.visibilityList.pop_front();
			break;
		case LEX_BRACKETS_LEFT:
			break;
		case LEX_BRACKETS_RIGHT:
			break;
		case LEX_BINARIES:
		case LEX_COMPARISONS:
		case LEX_UNARY:
			entryLex.operationType = temp.operationType;
			break;
		default:
			break;
		}
	}

	void SetIdType_IdDataType_IdxFirstLE(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry, int idxLex, int idxId)
	{
		if (temp.lexema == LEX_LITERAL)
		{
			analysisData.idType = IT::LITERAL;
			analysisData.idDataType = temp.idDataType;
		}
		entry.idType = analysisData.idType;
		entry.idDataType = analysisData.idDataType;
		entry.idxfirstLE = idxLex;
		// ��������� id ������� �������.
		if (analysisData.functionIn && entry.idType == IT::FUNCTION)
			analysisData.currentFunctionId = idxId;
	}

	void SetFunctionParams(AnalysisData& analysisData, int idx)
	{
		// ������ ���������� �� �������������� ���������� �������.
		analysisData.functionParamsCounter++;
		analysisData.paramsIdx.push_front(idx);
		analysisData.infoFunctionParamsNeedUpdate = false;
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
				cout << "��������� �������� ��������������: " << *temp.string << endl;
				length = ID_MAXSIZE;
			}
			entry.idName = new char[length + 1];
			entry.idName[length] = IN_NULL_STR;
			strncpy(entry.idName, *temp.string, length);
		}
	}

	void SetVisibility(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry)
	{
		switch (entry.idType)
		{
		case IT::LITERAL:
			entry.visibility.push_front(LITERAL_VISIBILITY);
			break;
		case IT::FUNCTION:
			entry.visibility = analysisData.visibilityList;
			analysisData.visibilityList.push_front(entry.idName);
			break;
		default:
			entry.visibility = analysisData.visibilityList;
			break;
		}
	}

	SetValueReturnCode SetValue(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry)
	{
		if (entry.idType == IT::LITERAL)
		{
			switch (entry.idDataType)
			{
			case IT::UINT:
			{
				// ����� ��� ��������� �� 8-�� �����
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

	CheckIdentificatorReturnCode CheckForIdentificator(const IT::IdTable& idTable, IT::Entry& entryId, AnalysisData& analysisData)
	{
		// ��������� �� ��������� �� ���������� ��� �������.
		if (*entryId.visibility.begin() == STANDART_VISIBILITY && entryId.idType == IT::VARIABLE)
			return GLOBAL_DECLARATION;
		for (int i = 0; i < idTable.current_size; i++)
		{
			// ��������� �� �������� ��������, �� ��� �� ������ ����� �� �����.
			if (entryId.visibility == idTable.table[i].visibility && entryId.idType == IT::LITERAL)
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
			// ������� �� ��������� + ���������� ����� ��������������.
			// ����� ������� �� ���� ��������������. U - ���������� ��� ����. 
			if (ViewVisibility(entryId.visibility, idTable.table[i].visibility) && (strcmp(entryId.idName, idTable.table[i].idName) == 0))
			{
				switch (entryId.idType)
				{
				case IT::U:
					return ALREADY_EXIST;
					break;
				default:
					return RE_DECLARATION;
					break;
				}
			}
		}
		// ���� ���������� ����� �� �����, �� ��� �������������� �� ��������
		// (�� ���� ��������� ����� �����) ==> ������������� �������������� ��������������.
		if (entryId.idType == IT::U)
			return NOT_DECLARED;
		return OK;
	}

	bool ViewVisibility(std::forward_list<std::string> visibilityCurrentId, std::forward_list<std::string> visibilityExistingId)
	{
		visibilityCurrentId.reverse();
		visibilityExistingId.reverse();
		auto iterator_currentId = visibilityCurrentId.begin();
		auto iterator_existingId = visibilityExistingId.begin();
		bool coincide = true;
		for (; (iterator_currentId != visibilityCurrentId.end()) && (iterator_existingId != visibilityExistingId.end()); ++iterator_currentId, ++iterator_existingId)
		{
			if (*iterator_currentId != *iterator_existingId)
				coincide = false;
		}
		if (iterator_existingId != visibilityExistingId.end())
			coincide = false;
		visibilityCurrentId.reverse();
		visibilityExistingId.reverse();
		return coincide;
	}

	void SetIdxTI(const IT::IdTable& idTable, const IT::Entry& entryId, LT::Entry& entryLex)
	{
		// ���������� � ������� ������ �� id � ������� ���������������.
		entryLex.idxTI = IT::GetId(idTable, entryId);
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
		entry.idxfirstLE = LT_TI_NULLXDX;

		analysisData.idDataType = IT::UNDEF;
		analysisData.idType = IT::U;
	}
	void ResetEntryLex(LT::Entry& entry)
	{
		entry.idxTI = LT_TI_NULLXDX;
		entry.operationType = LT::NONE;
	}

	void UpdateFunctionParamsInfo(AnalysisData& analysisData, IT::IdTable& idTable)
	{
		analysisData.functionNeedUpdate = false;
		idTable.table[analysisData.currentFunctionId].paramsIdx = analysisData.paramsIdx;
		idTable.table[analysisData.currentFunctionId].functionParamsCount = analysisData.functionParamsCounter;
		analysisData.paramsIdx.clear();
		analysisData.functionParamsCounter = 0;
	}
}