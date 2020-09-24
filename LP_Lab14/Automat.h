#pragma once
#include "FST.h"

namespace Automat
{
	struct AUTOMAT
	{
		FST::FST* KeyWord = NULL;

		FST::FST& operator[] (const int index);
	};

	void createAutomat(AUTOMAT& sample);
}