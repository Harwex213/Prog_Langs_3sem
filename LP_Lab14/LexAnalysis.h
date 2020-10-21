#pragma once
#include "In.h"
#include "LT.h"
#include "IT.h"
#include "FST.h"

#define LEX_PLUS		'+'
#define LEX_MINUS		'-'
#define LEX_MULTIPLY	'*'
#define LEX_FISSION		'/'

namespace LexAnalysis
{
	void FillTables(const In::IN& in, LT::LexTable& lextable, IT::IdTable& idtable);
}