#pragma once
#include "FST.h"
#include "IT.h"

namespace Automat
{
	struct AUTOMAT
	{
		FST::FST* KeyWord = NULL;

		FST::FST operator[] (const char index);
	};

	void fillAutomat(AUTOMAT& sample, char* string);
}