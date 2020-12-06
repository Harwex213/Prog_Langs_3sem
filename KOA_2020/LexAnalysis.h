#pragma once
#include "In.h"
#include "LT.h"
#include "IT.h"
#include "FST.h"

#define MAIN_VISIBILITY "GLOBAL"

namespace LexAnalysis
{
	struct AnalysisData
	{
		bool functionIn = false;
		std::list<std::string> visibility;
		int bracesCounter = 0;
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
	void SetName(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry);
	void SetVisibility(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry);
	void SetValue(const FST::FST& temp, AnalysisData& analysisData, IT::Entry& entry);
	void ResetAnalysisData(AnalysisData& analysisData);
}