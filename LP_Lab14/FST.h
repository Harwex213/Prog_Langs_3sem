#pragma once
#include <iostream>
#include <tchar.h>
#include "IT.h"

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
		char lexema;
		short position = 0;						//������� ������� � ������� 
		short nstates;							//���������� ��������� ��������
		NODE* nodes;							//���� ���������: [0] -��������� ���������, [nstate-1]-��������
		short* rstates;							//��������� ��������� �������� �� ������ �������
		FST(
			const char lxm,
			char* &s,							//������� (������, ���������� 0x00 )
			short ns,							//���������� ��������� �������� 
			NODE n, ...							//������ ��������� (���� ���������)
		);
	};

	bool execute(								//��������� ������������� ������� 
		FST& fst									//������������������ �������� �������
	);

};
