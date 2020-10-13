#include "stdafx.h"

namespace LexAnalysis
{
	void FillLexTable(In::IN& in, LT::LexTable& lextable)
	{
		//��� ������ �������� ���������� �� ������� ����� ��� �������
		//������ ������
		//�� ������ ������������� �������� ������ ����� (���������� ��� ���)
		//���� ������� ������������� - ����������� in.idCounter
		//���������� ���������� ������ � ������� ������

		char* string = NULL;
		Automat::AUTOMAT automats;
		GRAPHES;
		automats.KeyWord = graphArray;
		LT::Entry entry;

		for (int i = 0; i < in.lexCounter; i++)
		{
			string = in.alfaLxmTable[i].text;
			entry.psn = in.alfaLxmTable[i].position;
			entry.sn = in.alfaLxmTable[i].line;
			entry.lexema[LEXEMA_FIXSIZE] = IN_NULL_STR;
			entry.lexema[LEXEMA_FIXSIZE - 1] = automats[string[0]].lexema;
			if (!FST::execute(automats[string[0]]))
			{
				entry.lexema[LEXEMA_FIXSIZE - 1] = LEX_ID;
				if (!FST::execute(automats['i']))
					throw ERROR_THROW_IN(111, entry.sn, entry.psn);
			}
			Add(lextable, entry);
		}

	};

	void FillIdTable(const In::IN& in, const LT::LexTable& lextable, IT::IdTable& idtable)
	{

	};
}