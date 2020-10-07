#pragma once
#include "In.h"
#include "LT.h"
#include "IT.h"
#include "FST.h"

namespace Analysis
{
	void MakeAnalysis(In::IN in, LT::LexTable& lxmTable, IT::IdTable& idTable);
	FST::INTERIM_DATA UpdateInterimData(const FST::FST& fst, FST::INTERIM_DATA idata);
}