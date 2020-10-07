#pragma once
#include <iostream>
#include <tchar.h>
#include "Analysis.h"

namespace FST
{
	struct RELATION								// ����� :������->������� ����� ��������� ��
	{
		char symbol;							// ������ ��������
		short nnode;							// ����� ������� �������
		RELATION(char � = 0x00,					// ������ ��������
			short ns = NULL);					// ����� ���������												
	};

	struct NODE									// ������� ����� ���������
	{
		short n_relation;						// ���������� ������������ �����
		RELATION* relations;					// ����������� �����; 1 --a--> 2, ����� a ���������� �������� 1 � 2
		NODE();
		NODE(
			short n,							// ���������� ������������ �����
			RELATION rel, ...					// ������ �����
		);
	};

	struct FST
	{
		char** string;							//������� (������, ���������� 0x00 )
		Analysis::INTERIM_DATA interim_data;
		short position = 0;						//������� ������� � ������� 
		short nstates;							//���������� ��������� ��������
		NODE* nodes;							//���� ���������: [0] -��������� ���������, [nstate-1]-��������
		short* rstates;							//��������� ��������� �������� �� ������ �������
		FST(
			Analysis::INTERIM_DATA idata,
			char* &s,							//������� (������, ���������� 0x00 )
			short ns,							//���������� ��������� �������� 
			NODE n, ...							//������ ��������� (���� ���������)
		);

		void operator= (const FST& other)
		{
			this->string = other.string;
			this->interim_data = other.interim_data;
			this->position = other.position;
			this->nstates = other.nstates;
			this->nodes = new NODE[this->nstates];
			this->nodes = other.nodes;
			this->rstates = new short[this->nstates];
			memset(this->rstates, 0xff, sizeof(short) * this->nstates);
			this->rstates[0] = 0;
		};
	};

	char execute(								//��������� ������������� ������� 
		FST fst									//������������������ �������� �������
	);

};
