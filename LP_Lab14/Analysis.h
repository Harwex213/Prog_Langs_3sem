#pragma once
#include "IT.h"
#include "LT.h"
#include "In.h"

namespace Analysis
{
	struct INTERIM_DATA
	{
		IT::IDDATATYPE iddatatype;
		IT::IDDATATYPE idtype;
	};

	void MakeAnalysis(In::IN in, LT::LexTable& lxmTable, IT::IdTable& idTable);
}