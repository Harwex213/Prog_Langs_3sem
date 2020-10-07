#include "stdafx.h"

namespace Analysis
{
	void StartAnalysis(In::IN in, LT::LexTable& lxmTable, IT::IdTable& idTable)
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
			iData.line = in.AlfaLexTable[i].line;
			iData.position = in.AlfaLexTable[i].position;
			FST::FST interimfst = automats[string[0]];
			if (FST::execute(automats[string[0]]))
			{
				iData = UpdateInterimData(interimfst, iData);
				CreateEntry(iData, lxmTable);
			}
			else
			{
				interimfst = automats.KeyWord[IDENTIFY_INDEX];
				if (FST::execute(automats.KeyWord[IDENTIFY_INDEX]))
				{
					iData = UpdateInterimData(interimfst, iData);
					CreateEntry(iData, lxmTable);
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
		//Chek is it Global Function? (Declare + Function)
		if (idata.idtype == IT::F && fst.interim_data.lexema == LEX_DECLARE)
			idata.idtype = IT::GF;
		//Integer/String -> Parametr=1, Declare -> Value=2, Function -> Function=3
		if (idata.idtype < fst.interim_data.idtype)
			idata.idtype = fst.interim_data.idtype;
		//First Integer/String make IdDataType
		if (idata.iddatatype != IT::UNDEF)
			idata.iddatatype = fst.interim_data.iddatatype;
		//Current lexema
		idata.lexema = fst.interim_data.lexema;
		return idata;
	};

	void CreateEntry(FST::INTERIM_DATA idata, LT::LexTable& lxmTable)
	{
		LT::Entry sampleLex;
		sampleLex.lexema[LEXEMA_FIXSIZE] = '\0';
		sampleLex.psn = idata.position;
		sampleLex.sn = idata.line;
		sampleLex.lexema[LEXEMA_FIXSIZE - 1] = idata.lexema;
		LT::Add(lxmTable, sampleLex);
	};
}