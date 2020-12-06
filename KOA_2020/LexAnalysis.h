#pragma once
#include "In.h"
#include "LT.h"
#include "IT.h"
#include "FST.h"

namespace LexAnalysis
{
	struct AnalysisData
	{
		bool ExecuteDone = false;
		enum 
	};

	void Lexer(const In::IN& in, LT::LexTable& lextable, IT::IdTable& idtable);
	bool FindGraph(const std::vector<FST::FST*> graph, FST::FST*& temp);
	void CheckLexema(const FST::FST& temp);
}