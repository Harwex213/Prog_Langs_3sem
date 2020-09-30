#include "stdafx.h"

namespace Analysis
{
	void MakeAnalysis(LT::LexTable& lxmTable, IT::IdTable& idTable)
	{
		Automat::AUTOMAT automats;
		char* string = NULL;
		GRAPHES;
		Automat::createAutomat(automats, graphArray);
		FST::FST fstN = automats['i'];
		cout << string << endl;
		if (FST::execute(automats[string[0]]))
			cout << "WE DONE IT\n";
		else
			cout << "F*CK\n";
		char text1[] = "function";
		string = text1;
		cout << string << endl;
		if (FST::execute(automats[string[0]]))
			cout << "WE DONE IT\n";
		else
			cout << "F*CK\n";
	};
}