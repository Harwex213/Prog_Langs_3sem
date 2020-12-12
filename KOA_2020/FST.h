#pragma once
#include <iostream>
#include <tchar.h>
#include <vector>
#include "IT.h"
#include "LT.h"

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
		IT::IDDATATYPE idDataType = IT::UNDEF;
		LT::OperationType operationType = LT::NONE;
		char lexema;
		char** string;
		short position = 0;
		short nstates;
		NODE* nodes;
		short* rstates;
		FST* nextFST;

		FST();
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
