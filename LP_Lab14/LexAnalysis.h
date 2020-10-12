#pragma once
#include "In.h"
#include "LT.h"
#include "IT.h"
#include "FST.h"

namespace LexAnalysis
{
	void FillLexTable(In::IN& in, LT::LexTable& lextable);

	void FillIdTable(const In::IN& in, const LT::LexTable& lextable, IT::IdTable& idtable);
}