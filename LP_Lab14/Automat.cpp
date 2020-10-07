#include "stdafx.h"

namespace Automat
{
	FST::FST& AUTOMAT::operator[] (const char index)
	{
		NULL_DATA;
		NULL_STRING;
		FST::FST sample(GRAPH_SELECT); //можно сунуть в struct AUTOMAT
		for (short j = 0; j < sample.nodes[0].n_relation; j++)
		{
			if (sample.nodes[0].relations[j].symbol == index)
				return	KeyWord[sample.nodes[0].relations[j].nnode];
		};
		throw ERROR_THROW(121);
	};
}
