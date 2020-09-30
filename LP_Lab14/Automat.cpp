#include "stdafx.h"
char string = NULL;

namespace Automat
{
	FST::FST& AUTOMAT::operator[] (const char index)
	{
		char* nothing = NULL;
		FST::FST sample(GRAPH_SELECT);
		for (short j = 0; j < sample.nodes[0].n_relation; j++)
		{
			if (sample.nodes[0].relations[j].symbol == index)
				return	KeyWord[sample.nodes[0].relations[j].nnode];
		};
		throw ERROR_THROW(121);
	};

	void createAutomat(AUTOMAT& sample, FST::FST array[])
	{
		sample.KeyWord = array;
		/*sample.AutomatSelect = ;*/
	};
}
