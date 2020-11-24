#pragma once
#include <list>

#define ID_MAXSIZE		5				// ������������ ���������� ������� � ��������������
#define LITERAL_MAXSIZE	20
#define TI_MAXSIZE		4096			// ������������ ���������� ��-�� � ������� ��������������� 
#define TI_INT_DEFAULT	0x00000000		// �������� �� ��������� ��� ���� integer 
#define TI_STR_DEFAULT	0x00			// �������� �� ��������� ��� ���� string
#define TI_STR_MAXSIZE	255

#define PARM_ID_DEFAULT_EXT L".id.txt" //��� ����� � ������ ������������ ������a(�������������� � ��������)

namespace IT	// ������� �������������
{
	enum IDDATATYPE { UNDEF = 0, INT = 1, STR = 2 };			// 0 - UNDEF, 1 - INTEGER,  2 - STRING
	enum IDTYPE { U = 0, P = 1, V = 2, F = 3, L = 4 };	// 0 - UNDEF, 1 - PARAMETR, 2 - VALUE, 3 - FUNCTION, 4 - GLOBAL FUNCTION, 5 - LITERAL

	struct Entry						// ������ ������� ���������������
	{
		int idxfirstLE;
		char* id = NULL;			// ������������� (������������� ��������� �� ID_MAXSIZE)
		std::list<std::string> prefix;
		bool isGlobalFunction = false;
		IDDATATYPE	iddatatype = UNDEF;		// ��� ������
		IDTYPE	idtype  = U;				// ��� ������������
		union
		{
			int vint;					// �������� integer
			struct
			{
				unsigned char len;			// ��������� �������� � string
				char str[TI_STR_MAXSIZE - 1];	// ������� string
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
	Entry GetEntry(const IdTable& idtable, int n);
	int GetId(
		IdTable& idtable,
		char* id,
		std::list<std::string> prefix,
		int sn, int psn);
	bool IsId(
		IdTable& idtable,
		Entry entry
	);
	void Delete(IdTable& idtable);
}