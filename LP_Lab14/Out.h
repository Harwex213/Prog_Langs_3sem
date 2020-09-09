#pragma once
#include <fstream>
#include "Parm.h"
#include "In.h"
#include "Log.h"
using namespace std;
#pragma warning(disable: 4996)

namespace Out {

	struct OUT {
		wchar_t logfile[PARM_MAX_SIZE];
		ofstream* stream;
	};

	OUT getout(wchar_t outfile[]);
	void WriteAnalyze(OUT out, In::IN in, Log::LOG log);
	void OutClose(OUT out);
}