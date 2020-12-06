#pragma once
#include "In.h"
#include "LT.h"
#include "IT.h"
#include "FST.h"

#define MAIN_VISIBILITY "GLOBAL"
#define LITERAL_VISIBILITY "LITERAL"

namespace LexAnalysis
{
	struct AnalysisData
	{
		// See that we are in Function.
		bool functionIn = false;
		// Counter main. If > 1 ==> Error.
		int mainWas = 0;
		// Counter braces. If % 2 != 0 ==> Error.
		int bracesCounter = 0;
		// Vars for name-generator for literals.
		char literalIdChar[ID_MAXSIZE] = "L";
		int literalId = 0;
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
	void SetValue(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry);
	bool CheckForIdentificator(const IT::IdTable& idTable, IT::Entry& entryId);
	bool SetIdxTI(const IT::IdTable& idTable, const IT::Entry& entryId, LT::Entry& entryLex);
	void SetLexEntry(LT::Entry& entry, char lexema, int line, int position);
	void ResetAnalysisData(AnalysisData& analysisData, IT::Entry& entry);
}