#pragma once

#define ID_MAXSIZE		5				// ������������ ���������� ������� � ��������������
#define TI_MAXSIZE		4096			// ������������ ���������� ��-�� � ������� ��������������� 
#define TI_INT_DEFAULT	0x00000000		// �������� �� ��������� ��� ���� integer 
#define TI_STR_DEFAULT	0x00			// �������� �� ��������� ��� ���� string 
#define TI_NULLIDX		0xffffffff		// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE	255

#define PARM_ID_DEFAULT_EXT L".id.txt" //��� ����� � ������ ������������ ������a(�������������� � ��������)

namespace IT	// ������� �������������
{
	enum IDDATATYPE { UNDEF = 0, INT = 1, STR = 2 };			// 0 - UNDEF, 1 - INTEGER,  2 - STRING
	enum IDTYPE { U = 0, P = 1, V = 2, F = 3, GF = 4, L = 5 };	// 0 - UNDEF, 1 - PARAMETR, 2 - VALUE, 3 - FUNCTION, 4 - GLOBAL FUNCTION, 5 - LITERAL

	struct Entry						// ������ ������� ���������������
	{
		int idxfirstLE;
		char* id;			// ������������� (������������� ��������� �� ID_MAXSIZE)
		char* prefix;
		IDDATATYPE	iddatatype;			// ��� ������
		IDTYPE	idtype;					// ��� ������������
		union
		{
			int vint;					// �������� integer
			struct
			{
				unsigned char len;			// ��������� �������� � string
				char str[TI_STR_MAXSIZE];	// ������� string
			} vstr;	// �������� string
		}value;	// �������� ��������������

	};

	struct IdTable // ��������� ������� ���������������
	{
		int maxsize;				// ������� ������� ��������������� < TI_MAXSIZE
		int current_size;			// ������� ������ ������� ��������������� < maxsize
		Entry* table;				// ������ ����� ������� ���������������
	};

	IdTable Create(int size);
	void Add(IdTable& idtable, Entry entry);
	Entry GetEntry(IdTable& idtable, int n);
	int IsId(IdTable& idtable, char id[ID_MAXSIZE+1]);
	void Delete(IdTable& idtable);
}