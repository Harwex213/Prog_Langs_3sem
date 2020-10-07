#include "stdafx.h"

namespace Analysis
{
	void MakeAnalysis(In::IN in, LT::LexTable& lxmTable, IT::IdTable& idTable)
	{
		char* string = NULL;

		Automat::AUTOMAT automats;
		Automat::fillAutomat(automats, string);

		LT::Entry sampleLex;
		sampleLex.lexema[LEXEMA_FIXSIZE] = '\0';

		IT::Entry sampleIden;
		sampleIden.id[LEXEMA_FIXSIZE] = '\0';

		Analysis::INTERIM_DATA iData = { '\0', IT::UNDEF, IT::U };

		for (int i = 0; i < in.lxmCounter; i++)
		{
			FST::FST* interimfst = new FST::FST{ iData, string, 1, FST::NODE() };
			//does it normal to do that?
			sampleLex.psn = in.AlfaLexTable[i].position;
			sampleLex.sn = in.AlfaLexTable[i].line;
			string = in.AlfaLexTable[i].text;
			*interimfst = automats[string[0]];
			sampleLex.lexema[LEXEMA_FIXSIZE - 1] = FST::execute(*interimfst);
			LT::Add(lxmTable, sampleLex);
			delete interimfst;
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