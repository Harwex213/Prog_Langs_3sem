#pragma once
#include "In.h"
#include "LT.h"
#include "IT.h"

#define NULL_STRING	char* nothing = NULL;
#define NULL_DATA	Analysis::INTERIM_DATA nullData = { '\0', IT::UNDEF, IT::U };

namespace Analysis
{
	struct INTERIM_DATA
	{
		char lexema;					//returnable lexema
		IT::IDDATATYPE iddatatype;
		IT::IDTYPE idtype;
	};

	void MakeAnalysis(In::IN in, LT::LexTable& lxmTable, IT::IdTable& idTable);
}