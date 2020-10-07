#pragma once
#include <iostream>
#include <tchar.h>
#include "IT.h"

#define NULL_STRING	char* nothing = NULL;
#define NULL_DATA	FST::INTERIM_DATA nullData = { '\0', IT::UNDEF, IT::U };


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

	struct INTERIM_DATA
	{
		char lexema;					//returnable lexema
		IT::IDDATATYPE iddatatype;
		IT::IDTYPE idtype;
	};

	struct FST
	{
		char** string;							//������� (������, ���������� 0x00 )
		INTERIM_DATA interim_data;
		short position = 0;						//������� ������� � ������� 
		short nstates;							//���������� ��������� ��������
		NODE* nodes;							//���� ���������: [0] -��������� ���������, [nstate-1]-��������
		short* rstates;							//��������� ��������� �������� �� ������ �������
		FST(
			INTERIM_DATA idata,
			char* &s,							//������� (������, ���������� 0x00 )
			short ns,							//���������� ��������� �������� 
			NODE n, ...							//������ ��������� (���� ���������)
		);
	};

	bool execute(								//��������� ������������� ������� 
		FST& fst									//������������������ �������� �������
	);

};
