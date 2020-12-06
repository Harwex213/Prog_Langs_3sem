#pragma once
#include <list>

#define ID_MAXSIZE		30				// ������������ ���������� ������� � ��������������
#define TI_MAXSIZE		4096			// ������������ ���������� ��-�� � ������� ��������������� 
#define TI_INT_DEFAULT	0x00000000		// �������� �� ��������� ��� ���� integer 
#define TI_STR_DEFAULT	0x00			// �������� �� ��������� ��� ���� string
#define TI_STR_MAXSIZE	255

#define PARM_ID_DEFAULT_EXT L".id.txt" //��� ����� � ������ ������������ ������a(�������������� � ��������)

namespace IT
{
	enum IDDATATYPE { UNDEF = 0, UINT = 1, STRING = 2, BOOL = 3, FLOAT = 4 };
	enum IDTYPE { U = 0, PARAM = 1, VARIABLE = 2, FUNCTION = 3, LITERAL = 4 };

	struct Entry
	{
		int idxfirstLE;
		char* idName = NULL;
		std::list<std::string> visibility;
		IDDATATYPE	idDataType = UNDEF;
		IDTYPE	idType = U;
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

	struct IdTable
	{
		int maxsize;
		int current_size;
		Entry* table;
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