#include "stdafx.h"

namespace LexAnalysis
{
	void FillTables(const In::IN& in, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		char* string = NULL;
		Automat::AUTOMAT automats;
		GRAPHES;
		automats.KeyWord = graphArray;
		LT::Entry entryLex;
		IT::Entry entryId;
		entryId.prefix.push_back("GLOBAL");
		bool isItGlobalFunction = false;
		for (int i = 0; i < in.wordCounter; i++)
		{
			string = in.alfaLxmTable[i].text;
			entryLex.psn = in.alfaLxmTable[i].position;
			entryLex.sn = in.alfaLxmTable[i].line;
			entryLex.lexema[LEXEMA_FIXSIZE] = IN_NULL_STR;
			entryLex.lexema[LEXEMA_FIXSIZE - 1] = automats[string[0]].lexema;

			if (!FST::execute(automats[string[0]]))
			{
				entryLex.lexema[LEXEMA_FIXSIZE - 1] = LEX_ID;
				if (!FST::execute(automats.KeyWord[IDENTIFY_INDEX]))
					throw ERROR_THROW_IN(122, entryLex.sn, entryLex.psn);
			}
			entryLex.idxTI = LT_TI_NULLXDX;
			entryLex.arithmeticdata = LT::UNDEFINED;

			switch (entryLex.lexema[LEXEMA_FIXSIZE - 1])
			{
			case LEX_COMPUTATION:
				switch (string[0])
				{
				case LEX_PLUS:
					entryLex.arithmeticdata = LT::PLUS;
					break;
				case LEX_MINUS:
					entryLex.arithmeticdata = LT::MINUS;
					break;
				case LEX_MULTIPLY:
					entryLex.arithmeticdata = LT::MULTIPLY;
					break;
				case LEX_FISSION:
					entryLex.arithmeticdata = LT::FISSION;
					break;
				}
				break;
			case LEX_FUNCTION:
				if (entryId.idtype == IT::V)
					isItGlobalFunction = true;
				if (entryId.idtype < IT::F)
					entryId.idtype = IT::F;
				break;
			case LEX_DECLARE:
				if (entryId.idtype < IT::V)
					entryId.idtype = IT::V;
			case LEX_INTORSTR:
				if (entryId.idtype < IT::P)
					entryId.idtype = IT::P;
				entryId.iddatatype = automats[string[0]].idatatype;
				break;
			case LEX_MAIN:
				entryId.prefix.push_back(string);
				break;
			case LEX_SEMICOLON:
				if (entryId.isGlobalFunction)
				{
					entryId.isGlobalFunction = false;
					if (!entryId.prefix.empty())
						entryId.prefix.pop_back();
				}
				break;
			case LEX_RIGHTHESIS:
				if (!entryId.prefix.empty())
					entryId.prefix.pop_back();
				break;
			case LEX_ID:
			{
				if (entryId.iddatatype != IT::UNDEF)
				{
					entryId.idxfirstLE = lexTable.current_size;

					if (isItGlobalFunction)
					{
						entryId.isGlobalFunction = true;
						isItGlobalFunction = false;
						int i = strlen(string);
						entryId.id = new char[i+1];
						entryId.id[i] = IN_NULL_STR;
						strcpy(entryId.id, string);
					}
					else
					{
						int idSize = ID_MAXSIZE;
						int i = strlen(string);
						if (i < idSize)
							idSize = i;
						if (i > idSize)
							cout << "Произошло усечение идентификатора. Строка: " << entryLex.sn << ". Позиция: " << entryLex.psn << endl;
						entryId.id = new char[ID_MAXSIZE +1];
						entryId.id[idSize] = IN_NULL_STR;
						strncpy(entryId.id, string, idSize);
					}

					if (entryId.iddatatype == IT::INT)
						entryId.value.vint = TI_INT_DEFAULT;
					else
						entryId.value.vstr.len = TI_STR_DEFAULT;

					if (IT::IsId(idTable, entryId))
						IT::Add(idTable, entryId);
					else
						throw ERROR_THROW_IN(144, entryLex.sn, entryLex.psn);
				}
				if ((entryLex.idxTI = GetId(idTable, string, entryId.prefix, entryLex.sn, entryLex.psn)) == LT_TI_NULLXDX)
					throw ERROR_THROW_IN(141, entryLex.sn, entryLex.psn);

				if (entryId.idtype == IT::F)
					entryId.prefix.push_back(string);

				if (entryId.id)
				{
					delete[] entryId.id;
					entryId.id = NULL;
				}
				entryId.iddatatype = IT::UNDEF;
				entryId.idtype = IT::U;
				break;
			}
			case LEX_LITERAL:
			{
				entryId.idtype = IT::L;
				entryId.iddatatype = automats[string[0]].idatatype;
				entryId.idxfirstLE = lexTable.current_size;

				int idSize = LITERAL_MAXSIZE;
				int i = strlen(string);
				if (i < idSize)
					idSize = i;
				entryId.id = new char[idSize + 1];
				entryId.id[idSize] = IN_NULL_STR;
				strncpy(entryId.id, string, idSize);

				if (entryId.iddatatype == IT::INT)
				{
					long long buffer = 0;
					if (INT_MIN >= (buffer = atoll(string)) <= INT_MAX)
						entryId.value.vint = buffer;
					else
						throw ERROR_THROW_IN(142, entryLex.sn, entryLex.psn);
				}
				else
				{
					if (i > TI_STR_MAXSIZE)
						i = TI_STR_MAXSIZE;
					entryId.value.vstr.len = i - 2;
					entryId.value.vstr.str[entryId.value.vstr.len] = IN_NULL_STR;
					strncpy(entryId.value.vstr.str, string + 1, entryId.value.vstr.len);
				}

				if (IT::IsId(idTable, entryId))
					IT::Add(idTable, entryId);

				entryLex.idxTI = GetId(idTable, string, entryId.prefix, entryLex.sn, entryLex.psn);

				if (entryId.id)
				{
					delete[] entryId.id;
					entryId.id = NULL;
				}
				entryId.iddatatype = IT::UNDEF;
				entryId.idtype = IT::U;
				break;
			}
			default:
				break;
			}

			LT::Add(lexTable, entryLex);
		}

		//cout << endl << endl;

		//int counter = 0;
		//for (int i = 0; i < in.lines; i++)
		//{
		//	cout << lexTable.table[counter].sn << ' ';
		//	while (lexTable.table[counter].sn == i + 1)
		//	{
		//		cout << lexTable.table[counter].lexema;
		//		if (lexTable.table[counter].lexema[LEXEMA_FIXSIZE - 1] == LEX_ID ||
		//			lexTable.table[counter].lexema[LEXEMA_FIXSIZE - 1] == LEX_LITERAL)
		//		{
		//			cout << "(" << lexTable.table[counter].idxTI << ")";
		//		}
		//		if (lexTable.table[counter].lexema[LEXEMA_FIXSIZE - 1] == LEX_COMPUTATION)
		//		{
		//			cout << "(" << lexTable.table[counter].arithmeticdata << ")";
		//		}
		//		counter++;
		//	}
		//	cout << endl;
		//}

		//cout << endl << endl;

		//for (int i = 0; i < lexTable.current_size; i++)
		//{
		//	if (lexTable.table[i].lexema[LEXEMA_FIXSIZE-1] == LEX_ID)
		//	{
		//		cout << lexTable.table[i].lexema << "\tPosition: ";
		//		cout << lexTable.table[i].psn << "\tLine: ";
		//		cout << lexTable.table[i].sn << "\tID: ";
		//		cout << lexTable.table[i].idxTI <<  endl;
		//	}
		//}

		//cout << endl << endl;

		//int StringLength = 25;
		//cout.setf(ios::left);
		//cout << "|Params|\n";
		//cout.width(StringLength); cout << "Name";
		//cout.width(StringLength); cout << "Prefix";
		//cout.width(StringLength); cout << "DataType";
		//cout.width(StringLength); cout << "Value STR";
		//cout.width(StringLength); cout << "Value INT";
		//cout << endl;
		//for (int i = 0; i < idTable.current_size; i++)
		//{
		//	if (idTable.table[i].idtype == IT::P)
		//	{
		//		cout.width(StringLength); cout << idTable.table[i].id;
		//		cout.width(StringLength); cout << *idTable.table[i].prefix.rbegin();
		//		cout.width(StringLength); cout << idTable.table[i].iddatatype;
		//		if (idTable.table[i].iddatatype == IT::STR)
		//		{
		//			cout.width(StringLength); cout << (int)idTable.table[i].value.vstr.len;
		//			cout.width(StringLength); cout << idTable.table[i].value.vstr.str;
		//			cout.width(StringLength); cout << "-";
		//		}
		//		else
		//		{
		//			cout.width(StringLength); cout << "-";
		//			cout.width(StringLength); cout << "-";
		//			cout.width(StringLength); cout << idTable.table[i].value.vint;
		//		}
		//		cout << endl;
		//	}
		//}
		//cout << "|Functions|\n";
		//cout.width(StringLength); cout << "Name";
		//cout.width(StringLength); cout << "Prefix";
		//cout.width(StringLength); cout << "DataType";
		//cout.width(StringLength);
		//cout.width(StringLength);
		//cout.width(StringLength);
		//cout << endl;
		//for (int i = 0; i < idTable.current_size; i++)
		//{
		//	if (idTable.table[i].idtype == IT::F)
		//	{
		//		cout.width(StringLength); cout << idTable.table[i].id;
		//		cout.width(StringLength); cout << *idTable.table[i].prefix.rbegin();
		//		cout.width(StringLength); cout << idTable.table[i].iddatatype;
		//		cout.width(StringLength); cout << "-";
		//		cout.width(StringLength); cout << "-";
		//		cout.width(StringLength); cout << "-";
		//		cout << endl;
		//	}
		//}
		//cout << "|Variables|\n";
		//cout.width(StringLength); cout << "Name";
		//cout.width(StringLength); cout << "Prefix";
		//cout.width(StringLength); cout << "DataType";
		//cout.width(StringLength); cout << "STR length";
		//cout.width(StringLength); cout << "Value STR";
		//cout.width(StringLength); cout << "Value INT";
		//cout << endl;
		//for (int i = 0; i < idTable.current_size; i++)
		//{
		//	if (idTable.table[i].idtype == IT::V)
		//	{
		//		cout.width(StringLength); cout << idTable.table[i].id;
		//		cout.width(StringLength); cout << *idTable.table[i].prefix.rbegin();
		//		cout.width(StringLength); cout << idTable.table[i].iddatatype;
		//		if (idTable.table[i].iddatatype == IT::STR)
		//		{
		//			cout.width(StringLength); cout << (int)idTable.table[i].value.vstr.len;
		//			cout.width(StringLength); cout << idTable.table[i].value.vstr.str;
		//			cout.width(StringLength); cout << "-";
		//		}
		//		else
		//		{
		//			cout.width(StringLength); cout << "-";
		//			cout.width(StringLength); cout << "-";
		//			cout.width(StringLength); cout << idTable.table[i].value.vint;
		//		}
		//		cout << endl;
		//	}
		//}
		//cout << "|Literals|\n";
		//cout.width(StringLength); cout << "Name";
		//cout.width(StringLength); cout << "Prefix";
		//cout.width(StringLength); cout << "DataType";
		//cout.width(StringLength); cout << "STR length";
		//cout.width(StringLength); cout << "Value STR";
		//cout.width(StringLength); cout << "Value INT";
		//cout << endl;
		//for (int i = 0; i < idTable.current_size; i++)
		//{
		//	if (idTable.table[i].idtype == IT::L)
		//	{
		//		cout.width(StringLength); cout << idTable.table[i].id;
		//		cout.width(StringLength); cout << *idTable.table[i].prefix.rbegin();
		//		cout.width(StringLength); cout << idTable.table[i].iddatatype;
		//		if (idTable.table[i].iddatatype == IT::STR)
		//		{
		//			cout.width(StringLength); cout << (int)idTable.table[i].value.vstr.len;
		//			cout.width(StringLength); cout << idTable.table[i].value.vstr.str;
		//			cout.width(StringLength); cout << "-";
		//		}
		//		else
		//		{
		//			cout.width(StringLength); cout << "-";
		//			cout.width(StringLength); cout << "-";
		//			cout.width(StringLength); cout << idTable.table[i].value.vint;
		//		}
		//		cout << endl;
		//	}
		//}
	};
}