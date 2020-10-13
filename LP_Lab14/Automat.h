#pragma once
#include "FST.h"
#include "IT.h"
#include "Graph.h"

namespace Automat
{
	struct AUTOMAT
	{
		FST::FST* KeyWord = NULL;
		char* nothing = NULL;
		FST::FST selectGraph = { GRAPH_SELECT };

		FST::FST& operator[] (const char index);
	};
}