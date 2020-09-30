#pragma once
#include "FST.h"

namespace Automat
{
	struct AUTOMAT
	{
		FST::FST* KeyWord = NULL;

		FST::FST& operator[] (const char index);
	};

	void createAutomat(AUTOMAT& sample, FST::FST array[]);
}