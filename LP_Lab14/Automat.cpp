#include "stdafx.h"

namespace Automat
{
	FST::FST& AUTOMAT::operator[] (const int index)
	{
		return	KeyWord[index];
	};

	void createAutomat(AUTOMAT& sample, FST::FST* array)
	{
		char* string = NULL;
		FST::FST fst1(GRAPH_INT);
		FST::FST fst2(GRAPH_STR);
		FST::FST fst3(GRAPH_FUN);
		FST::FST fst4(GRAPH_DEC);
		FST::FST fst5(GRAPH_RET);
		FST::FST fst6(GRAPH_PRINT);
		FST::FST fst7(GRAPH_LTRL_INT);
		FST::FST fst8(GRAPH_LTRL_STR);
		FST::FST fst9(GRAPH_IDENTIFY);
		FST::FST fst10(GRAPH_INT);
		FST::FST graphArray[GRAPHS_SIZE] = {fst1, fst2, fst3, fst4, fst5, fst6, fst7, fst8, fst9, fst10};
	};
}
