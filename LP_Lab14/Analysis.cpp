//#include "stdafx.h"
//
//namespace Analysis
//{
//	void StartAnalysis(const In::IN& in, LT::LexTable& lxmTable, IT::IdTable& idTable)
//	{
//		//Our parsed string
//		char* string = NULL;
//
//		//Array of fst
//		Automat::AUTOMAT automats;
//		GRAPHES;
//		automats.KeyWord = graphArray;
//
//		//Interim datas
//		INTERIM_DATA* iData = new INTERIM_DATA;
//
//		for (int i = 0; i < in.lxmCounter; i++)
//		{
//			string = in.AlfaLexTable[i].text;
//
//			iData->line = in.AlfaLexTable[i].line;
//			iData->position = in.AlfaLexTable[i].position;
//
//			//Create Interim fst to put necessary interim datas
//			FST::FST interimfst = automats[string[0]];
//
//			if (FST::execute(automats[string[0]]))
//			{
//				UpdateInterimData(interimfst, iData);
//				CreateEntry(iData, lxmTable);
//				if (iData->IsIdentificator)
//				{
//					iData->idxfirstLE = lxmTable.current_size;
//					CreateEntry(iData, idTable);
//					iData = ZeroizeInterimData(iData);
//				}
//			}
//			else
//			{
//				interimfst = automats.KeyWord[IDENTIFY_INDEX];
//				if (FST::execute(automats.KeyWord[IDENTIFY_INDEX]))
//				{
//					UpdateInterimData(interimfst, iData);
//					CreateEntry(iData, lxmTable);
//					if (iData->IsIdentificator)
//					{
//						iData->idxfirstLE = lxmTable.current_size;
//						CreateEntry(iData, idTable);
//						iData = ZeroizeInterimData(iData);
//					}
//				}
//				else
//					throw ERROR_THROW_IN(111, in.AlfaLexTable[i].line, in.AlfaLexTable[i].position);
//			}
//		}
//		
//		int counter = 0;
//		for (int i = 0; i < in.lines; i++)
//		{
//			cout << lxmTable.table[counter].sn << ' ';
//			while (lxmTable.table[counter].sn == i+1)
//			{
//				cout << lxmTable.table[counter++].lexema;
//			}
//			cout << endl;
//		}
//
//		cout << "\Params\n";
//		for (int i = 0; i < idTable.maxsize; i++)
//		{
//			cout.width(15);
//			if (idTable.table[i].idtype == IT::P)
//			{
//				cout << idTable.table[i].id << endl;
//			}
//		}
//	};
//
//	void UpdateInterimData(const FST::FST& fst, INTERIM_DATA* idata)
//	{
//		//Current lexema
//		idata->lexema = fst.interim_data.lexema;
//
//		switch (idata->lexema)
//		{
//		case LEX_LITERAL:
//			idata->IsIdentificator = true;
//			idata->idtype = fst.interim_data.idtype;
//			idata->iddatatype = fst.interim_data.iddatatype;
//			idata->idName[0] = '\0';
//
//			if (idata->iddatatype == IT::STR)
//			{
//				short txt_temp = strlen(*fst.string) - 2;
//				idata->value.vstr.str[0] = txt_temp;
//				//Превышение TI_STR_MAXSIZE
//				strncpy(idata->value.vstr.str, *fst.string, txt_temp);
//				idata->value.vstr.str[txt_temp] = '\0';
//			}
//			else
//			{
//				//Chek on Min-Max values
//				idata->value.vint = atoi(*fst.string);
//			}
//
//			break;
//		case LEX_ID:
//			if (idata->iddatatype != IT::UNDEF)
//			{
//				idata->IsIdentificator = true;
//
//				if (idata->idtype != IT::GF)
//				{
//					idata->idName[ID_MAXSIZE] = '\0';
//					strncpy(idata->idName, *fst.string, ID_MAXSIZE);
//				}
//				else
//					idata->idGFName = *fst.string;
//
//				if (idata->iddatatype == IT::STR)
//				{
//					idata->value.vstr.str[0] = 0;
//					strcpy(idata->value.vstr.str + 1, "");
//				}
//				else
//					idata->value.vint = 0;
//			}
//			else
//				idata->IsIdentificator = false;
//
//			break;
//		case LEX_FUNCTION:
//			if (idata->IsGlobalFunction)
//			{
//				idata->idtype = IT::GF;
//				idata->IsGlobalFunction = false;
//			};
//		case LEX_DECLARE:
//			idata->IsGlobalFunction = true;
//		case LEX_RIGHTHESIS:
//			//visibility
//		default:
//			if (idata->idtype < fst.interim_data.idtype)
//				idata->idtype = fst.interim_data.idtype;
//
//			if (fst.interim_data.iddatatype != IT::UNDEF)
//				idata->iddatatype = fst.interim_data.iddatatype;
//
//			break;
//		}
//	};
//
//	INTERIM_DATA* ZeroizeInterimData(INTERIM_DATA* idata)
//	{
//		delete idata;
//		INTERIM_DATA* iData = new INTERIM_DATA;
//		return iData;
//	};
//
//	void CreateEntry(INTERIM_DATA* idata, LT::LexTable& lxmTable)
//	{
//		LT::Entry sample;
//		sample.lexema[LEXEMA_FIXSIZE] = '\0';
//		sample.lexema[LEXEMA_FIXSIZE - 1] = idata->lexema;
//		sample.psn = idata->position;
//		sample.sn = idata->line;
//		LT::Add(lxmTable, sample);
//	};
//
//	void CreateEntry(const INTERIM_DATA* idata, IT::IdTable& idTable)
//	{
//		IT::Entry sample;
//		sample.iddatatype = idata->iddatatype;
//		sample.idtype = idata->idtype;
//		sample.idxfirstLE = idata->idxfirstLE;
//
//		if (idata->idtype == IT::GF)
//			sample.id = idata->idGFName;
//		else
//			sample.id = (char*)idata->idName;
//
//		if (idata->iddatatype == IT::STR)
//			strcpy(sample.value.vstr.str, idata->value.vstr.str);
//		else
//			sample.value.vint = idata->value.vint;
//		IT::Add(idTable, sample);
//	};
//}