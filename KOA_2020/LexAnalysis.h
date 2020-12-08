#pragma once
#include "In.h"
#include "LT.h"
#include "IT.h"
#include "FST.h"

#define MAIN_VISIBILITY "GLOBAL"
#define LITERAL_VISIBILITY "LITERAL"

#define COUPLER_SYMBOL '_'
#define FIRST_SYMBOL_TRUE 't'
#define FIRST_SYMBOL_FALSE 'f'

#define UINT_MIN 0
#define DEC_NUMBER_SYMBOL 10
#define FIRST_SYMBOL 0

namespace LexAnalysis
{
	enum CheckIdentificatorReturnCode { OK = 1, GLOBAL_DECLARATION = 2, RE_DECLARATION = 3, ALREADY_EXIST = 4, NOT_DECLARED = 5 };
	enum SetValueReturnCode { SUCCESS = 1, GOING_BEYOND_UINT = 2, GOING_BEYOND_FLOAT = 3, GOING_BEYOND_STRING = 4};
	struct AnalysisData
	{
		// See that we are in Function.
		bool functionIn = false;
		bool whileIn = false;
		// Counter main. If > 1 ==> Error.
		int mainWas = 0;
		// Counter braces. If % 2 != 0 ==> Error.
		int bracesCounter = 0;
		// Vars for name-generator for literals.
		char literalIdChar[ID_MAXSIZE] = "L";
		int literalId = 0;
		// Vars for name-generator for Whule.
		char WhileIdChar[ID_MAXSIZE] = "W";
		int whileId = 0;
		// Vars for name-generator for If.
		char IfIdChar[ID_MAXSIZE] = "I";
		int ifId = 0;
		// Vars for name-generator for Else.
		char ElseIdChar[ID_MAXSIZE] = "E";
		int elseId = 0;
		// Visibility of Identificators.
		std::list<std::string> visibility;
		// IdType and IdDataType
		IT::IDDATATYPE idDataType = IT::UNDEF;
		IT::IDTYPE idType = IT::U;

		void SetGlobalVisibility()
		{
			visibility.push_back(MAIN_VISIBILITY);
		}
	};

	void Lexer(const In::IN& in, LT::LexTable& lextable, IT::IdTable& idtable);
	bool FindGraph(const std::vector<FST::FST*> graph, FST::FST*& temp);
	void CheckLexema(const FST::FST& temp, AnalysisData& analysisData);
	void SetIdTypeAndIdDataType(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry);
	void SetName(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry);
	void SetVisibility(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry);
	bool ViewVisibility(std::list<std::string> visibilityThis, std::list<std::string> visibilityThat);
	SetValueReturnCode SetValue(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry);
	CheckIdentificatorReturnCode CheckForIdentificator(const IT::IdTable& idTable, IT::Entry& entryId);
	void SetIdxTIandIdxFirstLE(const IT::IdTable& idTable, const LT::LexTable& lexTable, IT::Entry& entryId, LT::Entry& entryLex);
	void SetLexEntry(LT::Entry& entry, char lexema, int line, int position);
	void ResetAnalysisData(AnalysisData& analysisData, IT::Entry& entry);
}