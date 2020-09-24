#pragma once
#include <iostream>
#include <tchar.h>
#define GRAPH1 5, \
FST::NODE(1, FST::RELATION('a', 1)), \
FST::NODE(5, FST::RELATION('b', 1), FST::RELATION('c', 2), FST::RELATION('d', 2), FST::RELATION('e', 2), FST::RELATION('b', 3)), \
FST::NODE(4, FST::RELATION('c', 2), FST::RELATION('d', 2), FST::RELATION('e', 2), FST::RELATION('b', 3)), \
FST::NODE(2, FST::RELATION('b', 3), FST::RELATION('h', 4)), \
FST::NODE()

namespace FST
{
	struct RELATION							// ����� :������->������� ����� ��������� ��
	{
		char symbol;						// ������ ��������
		short nnode;						// ����� ������� �������
		RELATION(char � = 0x00,				// ������ ��������
			short ns = NULL);				// ����� ���������												
	};

	struct NODE								// ������� ����� ���������
	{
		short n_relation;					// ���������� ������������ �����
		RELATION* relations;				// ����������� �����; 1 --a--> 2, ����� a ���������� �������� 1 � 2
		NODE();
		NODE(
			short n,						// ���������� ������������ �����
			RELATION rel, ...				// ������ �����
		);
	};

	struct FST
	{
		const char* string;					//������� (������, ���������� 0x00 ) 
		short position = 0;					//������� ������� � ������� 
		short nstates;						//���������� ��������� ��������
		NODE* nodes;						//���� ���������: [0] -��������� ���������, [nstate-1]-��������
		short* rstates;						//��������� ��������� �������� �� ������ �������.
		FST(
			const char* s,					//������� (������, ���������� 0x00 ) 
			short ns,						//���������� ��������� �������� 
			NODE n, ...						//������ ��������� (���� ���������)
		);
	};

	bool execute(							//��������� ������������� ������� 
		FST& fst							//������������������ �������� �������
	);

};
