#include "stdafx.h"

namespace Analysis
{
	void MakeAnalysis(In::IN in, LT::LexTable& lxmTable, IT::IdTable& idTable)
	{
		Automat::AUTOMAT automats;
		char* string = NULL;
		GRAPHES;
		Automat::createAutomat(automats, graphArray);

		LT::Entry sampleLex;
		sampleLex.lexema[LEXEMA_FIXSIZE] = '\0';
		FST::FST interimfst = { string, '\0', 1, FST::NODE() };

		for (int i = 0; i < in.lxmCounter; i++)
		{
			sampleLex.psn = in.AlfaLexTable[i].position;
			sampleLex.sn = in.AlfaLexTable[i].line;
			string = in.AlfaLexTable[i].text;
			interimfst = automats[string[0]]; //Как удалять память?
			sampleLex.lexema[LEXEMA_FIXSIZE - 1] = FST::execute(interimfst);
			LT::Add(lxmTable, sampleLex);
		}
		
		int counter = 0;
		for (int i = 0; i < in.lines; i++)
		{
			cout << lxmTable.table[counter].sn << ' ';
			while (lxmTable.table[counter].sn == i+1)
			{
				cout << lxmTable.table[counter++].lexema;
			}
			cout << endl;
		}
	};
}