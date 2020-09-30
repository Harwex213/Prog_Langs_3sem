#pragma once
#include "IT.h"
#include "LT.h"

namespace Analysis
{
	struct INTERIM_DATA
	{
		IT::IDDATATYPE iddatatype;
		IT::IDDATATYPE idtype;
	};

	void MakeAnalysis(LT::LexTable& lxmTable, IT::IdTable& idTable);
}