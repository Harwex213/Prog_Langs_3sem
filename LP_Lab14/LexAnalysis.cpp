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
			if (true)
			{

			}
		}
	};

	void FillIdTable(const In::IN& in, const LT::LexTable& lextable, IT::IdTable& idtable)
	{

	};
}