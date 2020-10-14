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

			//1) �������� ���� �� v
			//2) ��������� �������� �� ��������� ��� �������?
			//3) ��������� �������� ��������:
			//	 - ������� �������� int �� 2^31-1;
			//	 - ������� �������� str �� TI_STR_MAXSIZE (������ ������ - ���-�� �����)
			//	 - �������� ������������� ��������?
			//4) ���������� ���������?

			switch (entryLex.lexema[LEXEMA_FIXSIZE - 1])
			{
			case LEX_FUNCTION:
				if (entryId.idtype == IT::V)
					entryId.isGlobalFunction = true;
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
			case LEX_ID:
			{
				if (entryId.iddatatype != IT::UNDEF)
				{
					entryId.idxfirstLE = lexTable.current_size;
					
					if (entryId.isGlobalFunction)
					{
						int i = strlen(string);
						entryId.id = new char[i];
						entryId.id[i] = IN_NULL_STR;
						strcpy(entryId.id, string);
					}
					else
					{
						int idSize = ID_MAXSIZE;
						int i = strlen(string);
						if (i < idSize)
							idSize = i;
						entryId.id = new char[idSize+1];
						entryId.id[idSize] = IN_NULL_STR;
						strncpy(entryId.id, string, idSize);
					}

					if (entryId.iddatatype == IT::INT)
						entryId.value.vint = TI_INT_DEFAULT;
					else
					{
						entryId.value.vstr.len = TI_STR_DEFAULT;
						entryId.value.vstr.str[0] = entryId.value.vstr.len;
						strcpy(entryId.value.vstr.str + 1, "");
					}

					if (IsId(idTable, string) == LT_TI_NULLXDX)
						IT::Add(idTable, entryId);
				}
				if ((entryLex.idxTI = IsId(idTable, string)) == LT_TI_NULLXDX)
					throw ERROR_THROW_IN(141, entryLex.sn, entryLex.psn);

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
				entryId.idtype = IT::L;
				entryId.iddatatype = automats[string[0]].idatatype;


				break;
			default:
				break;
			}

			LT::Add(lexTable, entryLex);

		}

		//int counter = 0;
		//for (int i = 0; i < in.lines; i++)
		//{
		//	cout << lextable.table[counter].sn << ' ';
		//	while (lextable.table[counter].sn == i + 1)
		//	{
		//		cout << lextable.table[counter++].lexema;
		//	}
		//	cout << endl;
		//}

		int counter = 0;
		cout << "Params:\n";
		for (int i = 0; i < idTable.current_size; i++)
		{
			if (idTable.table[i].idtype == IT::P)
			{
				cout << "Param: " << idTable.table[i].id << "\tValue int: " << idTable.table[i].value.vint << "\tValue str: " << idTable.table[i].value.vstr.str << endl;
			}
		}
	};
}
		//����������� �� ������� ������ � ���� ��������������
		//���� �� ����� ������������� -	��������� � ������ idxTI "����"
		//����� ����� �������������:
		//1) ������ ���������� �������� �����
		//2) �� ������ �������� � ������� switch ���������� ��� ������ � ��� ��������
		//3) ���� ����� �� ������� �������������� - ��������� ��������
		//���� ������ �� ������� - ���� ������������� ��� ��������
		//���� ���-�� ����� - �������� � IsId(IsLiteral) � �����:
		//1) ��������� �� ��������������
		//2) �������� idxTI
		//���� ����� GF - ������� ������� ���������
		//� ����������� � ���������� ������� ��������� �� � entry
		//������� prefix
		//� ������� in (������� ���������) - ��������� �������� �������� (������� ��� L � GF!)
		//� ������� in - ��������� �������� � L
		//� !L ��������� ������������ ����������
