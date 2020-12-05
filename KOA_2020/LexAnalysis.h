#pragma once
#include "In.h"
#include "LT.h"
#include "IT.h"
#include "FST.h"

namespace LexAnalysis
{
	void Lexer(const In::IN& in, LT::LexTable& lextable, IT::IdTable& idtable);
}