#include "stdafx.h"

namespace Automat
{
	FST::FST& AUTOMAT::operator[] (const char index)
	{
		for (short j = 0; j < selectGraph.nodes[0].n_relation; j++)
		{
			if (selectGraph.nodes[0].relations[j].symbol == index)
				return	KeyWord[selectGraph.nodes[0].relations[j].nnode];
		};
		cout << index;
		throw ERROR_THROW(121);
	};
}
