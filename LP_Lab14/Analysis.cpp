#include "stdafx.h"

namespace Analysis
{
	void MakeAnalysis(In::IN in, LT::LexTable& lxmTable, IT::IdTable& idTable)
	{
		char* string = NULL;

		Automat::AUTOMAT automats;
		GRAPHES;
		automats.KeyWord = graphArray;

		LT::Entry sampleLex;
		sampleLex.lexema[LEXEMA_FIXSIZE] = '\0';
		IT::Entry sampleIden;
		sampleIden.id[LEXEMA_FIXSIZE] = '\0';

		FST::INTERIM_DATA iData = { '\0', IT::UNDEF, IT::U };

		for (int i = 0; i < in.lxmCounter; i++)
		{
			string = in.AlfaLexTable[i].text;
			FST::FST interimfst = automats[string[0]];
			if (FST::execute(automats[string[0]]))
			{
				iData = UpdateInterimData(interimfst, iData);
				sampleLex.psn = in.AlfaLexTable[i].position;
				sampleLex.sn = in.AlfaLexTable[i].line;
				sampleLex.lexema[LEXEMA_FIXSIZE - 1] = iData.lexema;
				LT::Add(lxmTable, sampleLex);
			}
			else
			{
				interimfst = automats.KeyWord[IDENTIFY_INDEX];
				if (FST::execute(automats.KeyWord[IDENTIFY_INDEX]))
				{
					iData = UpdateInterimData(interimfst, iData);
					sampleLex.psn = in.AlfaLexTable[i].position;
					sampleLex.sn = in.AlfaLexTable[i].line;
					sampleLex.lexema[LEXEMA_FIXSIZE - 1] = iData.lexema;
					LT::Add(lxmTable, sampleLex);
				}
				else
					throw ERROR_THROW_IN(111, in.AlfaLexTable[i].line, in.AlfaLexTable[i].position);
			}
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

	FST::INTERIM_DATA UpdateInterimData(const FST::FST& fst, FST::INTERIM_DATA idata)
	{
		idata.iddatatype = fst.interim_data.iddatatype;
		idata.idtype = fst.interim_data.idtype;
		idata.lexema = fst.interim_data.lexema;
		return idata;
	};
}