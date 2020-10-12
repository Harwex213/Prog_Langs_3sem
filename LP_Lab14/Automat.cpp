#include "stdafx.h"

namespace Automat
{
	FST::FST& AUTOMAT::operator[] (const char index)
	{
		char* nothing = NULL;
		FST::FST sample(GRAPH_SELECT); //можно сунуть в struct AUTOMAT
		for (short j = 0; j < sample.nodes[0].n_relation; j++)
		{
			if (sample.nodes[0].relations[j].symbol == index)
				return	KeyWord[sample.nodes[0].relations[j].nnode];
		};
		cout << index;
		throw ERROR_THROW(121);
	};
}
