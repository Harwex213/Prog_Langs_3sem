#include "stdafx.h"
#define GRB_ERROR_SERIES 140

namespace GRB
{
	// ��� ����� ��������:
	// 1) ���������� ��������� � ���������.
	// 2) ...
	Greibach greibach(
		NS('S'),
		TS('$'),
		6,
		Rule(
				// Functions and Main.
				NS('S'),
				GRB_ERROR_SERIES + 1,
				3,
				Rule::Chain(3, TS('d'), TS('l'), NS('S')),
				Rule::Chain(8, TS('m'), TS('{'), NS('I'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
				Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('P'), TS(')'), TS('{'), NS('I'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S'))
			),
		Rule(
				// Instructions. 
				NS('I'),
				GRB_ERROR_SERIES + 2,
				18,
				// ���� �������������.
				// ���������� � ������������.
				Rule::Chain(6, TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('I')),
				// ����������.
				Rule::Chain(4, TS('t'), TS('i'), TS(';'), NS('I')),
				// ���������� �������.
				Rule::Chain(7, TS('t'), TS('i'), TS('['), NS('E'), TS(']'), TS(';'), NS('I')),
				// ���������� ���������.
				Rule::Chain(7, TS('c'), TS('t'), TS('i'), TS('='), TS('l'), TS(';'), NS('I')),
				// ������������.
				Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('I')),
				// ������������ �������.
				Rule::Chain(8, TS('i'), TS('['), NS('E'), TS(']'), TS('='), NS('E'), TS(';'), NS('I')),
				// ����
				Rule::Chain(8, TS('w'), TS('('), NS('E'), TS(')'), TS('{'), NS('I'), TS('}'), NS('I')),
				// if -> else
				Rule::Chain(12, TS('q'), TS('('), NS('E'), TS(')'), TS('{'), NS('I'), TS('}'), TS('e'), TS('{'), NS('I'), TS('}'), NS('I')),
				// if
				Rule::Chain(8, TS('q'), TS('('), NS('E'), TS(')'), TS('{'), NS('I'), TS('}'), NS('I')),
				
				// ���� ��������.
				// ���������� � ������������.
				Rule::Chain(5, TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
				// ����������.
				Rule::Chain(3, TS('t'), TS('i'), TS(';')),
				// ���������� �������.
				Rule::Chain(6, TS('t'), TS('i'), TS('['), NS('E'), TS(']'), TS(';')),
				// ���������� ���������.
				Rule::Chain(6, TS('c'), TS('t'), TS('i'), TS('='), TS('l'), TS(';')),
				// ������������.
				Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
				// ������������ �������.
				Rule::Chain(7, TS('i'), TS('['), NS('E'), TS(']'), TS('='), NS('E'), TS(';')),
				// ����
				Rule::Chain(7, TS('w'), TS('('), NS('E'), TS(')'), TS('{'), NS('I'), TS('}')),
				// if -> else
				Rule::Chain(11, TS('q'), TS('('), NS('E'), TS(')'), TS('{'), NS('I'), TS('}'), TS('e'), TS('{'), NS('I'), TS('}')),
				// if
				Rule::Chain(7, TS('q'), TS('('), NS('E'), TS(')'), TS('{'), NS('I'), TS('}'))
			),
		Rule(
				// Expressions.
				NS('E'),
				GRB_ERROR_SERIES + 3,
				12,
				// ���� � ����������.
				// �������������.
				Rule::Chain(2, TS('i'), NS('O')),
				// ������.
				Rule::Chain(5, TS('i'), TS('['), NS('E'), TS(']'), NS('O')),
				// �������.
				Rule::Chain(2, TS('l'), NS('O')),
				// ����� �������.
				Rule::Chain(5, TS('i'), TS('('), NS('C'), TS(')'), NS('O')),
				// ��������� �� ��������.
				Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('O')),
				// Unary { ~ }
				Rule::Chain(3, TS('b'), NS('E'), NS('O')),

				// ���� ��� ��������.
				// �������������.
				Rule::Chain(1, TS('i')),
				// ������.
				Rule::Chain(4, TS('i'), TS('['), NS('E'), TS(']')),
				// �������.
				Rule::Chain(1, TS('l')),
				// ����� �������.
				Rule::Chain(4, TS('i'), TS('('), NS('C'), TS(')')),
				// ��������� �� ��������.
				Rule::Chain(3, TS('('), NS('E'), TS(')')),
				// Unary { ~ }
				Rule::Chain(2, TS('b'), NS('E'))
			),
		Rule(
				// Operations: {+ - * / | & ~}. (and == > < >= <=)?
				NS('O'),
				GRB_ERROR_SERIES + 3,
				8,
				// Binaries: {+ - * / | &}
				Rule::Chain(3, TS('v'), NS('E'), NS('O')),
				Rule::Chain(2, TS('v'), NS('E')),
				Rule::Chain(4, TS('v'), TS('b'), NS('E'), NS('O')),
				Rule::Chain(3, TS('v'), TS('b'), NS('E')),
				// Comparisons { == > < >= <=}
				Rule::Chain(3, TS('g'), NS('E'), NS('O')),
				Rule::Chain(2, TS('g'), NS('E')),
				Rule::Chain(4, TS('g'), TS('b'), NS('E'), NS('O')),
				Rule::Chain(3, TS('g'), TS('b'), NS('E'))
			),
		Rule(
				// Params while creating.
				NS('P'),
				GRB_ERROR_SERIES + 4,
				4,
				Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('P')),
				Rule::Chain(6, TS('t'), TS('i'), TS('['), TS(']'), TS(','), NS('P')),
				Rule::Chain(2, TS('t'), TS('i')),
				Rule::Chain(4, TS('t'), TS('i'), TS('['), TS(']'))
			),
		Rule(
				// Params while calling.
				NS('C'),
				GRB_ERROR_SERIES + 5,
				12,
				Rule::Chain(3, TS('i'), TS(','), NS('C')),
				Rule::Chain(4, TS('i'), NS('O'), TS(','), NS('C')),
				Rule::Chain(6, TS('i'), TS('['), NS('E'), TS(']'), TS(','), NS('C')),
				Rule::Chain(7, TS('i'), TS('['), NS('E'), TS(']'), NS('O'), TS(','), NS('C')),
				Rule::Chain(3, TS('l'), TS(','), NS('C')),
				Rule::Chain(4, TS('l'), TS(','), NS('O'), NS('C')),

				Rule::Chain(1, TS('i')),
				Rule::Chain(2, TS('i'), NS('O')),
				Rule::Chain(4, TS('i'), TS('['), NS('E'), TS(']')),
				Rule::Chain(5, TS('i'), TS('['), NS('E'), TS(']'), NS('O')),
				Rule::Chain(1, TS('l')),
				Rule::Chain(2, TS('l'), NS('O'))
			)
	);

	Greibach getGreibach() { return greibach; }

	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
	{
		nt = new GRBALPHABET[size = psize];
		int* p = (int*)&s;						//����� �������� � int
		for (short i = 0; i < size; i++)
			nt[i] = (GRBALPHABET)p[i];			//����� ����� �������� � short
	}

	Rule::Rule(GRBALPHABET pnn, int iderror, short psize, Chain c, ...)
	{
		nn = pnn;
		idError = iderror;
		chains = new Chain[size = psize];
		Chain* p = &c;
		for (short i = 0; i < size; i++)
			chains[i] = p[i];
	}

	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...)
	{
		startN = pstartN;
		stbottomT = pstbottomT;
		rules = new Rule[size = psize];
		Rule* p = &r;
		for (short i = 0; i < size; i++)
			rules[i] = p[i];
	}

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1;
		short k = 0;
		while (k < this->size && this->rules[k].nn != pnn)
			k++;
		if (k < this->size)
			prule = this->rules[rc = k];
		return rc;
	}

	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < this->size)
			rc = this->rules[n];
		return rc;
	}

	char* Rule::getCRule(char* b, short nchain)
	{
		char bchain[200];		//������ �����������?
		b[0] = Chain::alphabet_to_char(this->nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0x00;
		chains[nchain].getCChain(bchain);		//��� ���������� ������������?
		strcat_s(b, sizeof(bchain) + 5, bchain);	//������ (+5) � ���������� 
		return b;
	}

	short Rule::getNextChain(GRBALPHABET t, Chain& pchain, short j)
	{
		short rc = -1;
		while (j < size && chains[j].nt[0] != t)
			j++;
		rc = (j < size ? j : -1);
		if (rc >= 0)				//����� �� �������� �� (rc != -1)???
			pchain = chains[rc];
		return rc;
	}
	
	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < size; i++)
			b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	}
}