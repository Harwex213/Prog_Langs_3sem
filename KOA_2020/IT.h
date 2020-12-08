#pragma once
#include <list>
#include <vector>

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

	struct Visibility
	{
		std::string visibilityInitilization;
		std::string visibilityFunction;
	};

	struct Entry
	{
		int idxfirstLE;
		char* idName = NULL;
		Visibility visibilityTest;
		std::list<std::string> visibility;
		IDDATATYPE	idDataType = UNDEF;
		IDTYPE	idType = U;
		union
		{
			int vUint;
			bool vBool;
			float vFloat;
			struct
			{
				unsigned char length;
				char string[TI_STR_MAXSIZE - 1];
			} vString;
		} value;

	};

	struct IdTable
	{
		int maxsize;
		int current_size;
		Entry* table;
	};

	IdTable Create(int size);
	void AddEntry(IdTable& idtable, Entry entry);
	Entry GetEntry(const IdTable& idtable, int n);
	int GetId(const IdTable& idTable, char* id, std::list<std::string> visibility);
	void Delete(IdTable& idtable);
}