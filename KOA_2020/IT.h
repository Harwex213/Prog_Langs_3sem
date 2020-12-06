#pragma once
#include <list>

#define ID_MAXSIZE		30				// максимальное количество сиволов в идентификаторе
#define TI_MAXSIZE		4096			// максимальное количество эл-ов в таблице идентификаторов 
#define TI_INT_DEFAULT	0x00000000		// значение по умолчанию для типа integer 
#define TI_STR_DEFAULT	0x00			// значение по умолчанию для типа string
#define TI_STR_MAXSIZE	255

#define PARM_ID_DEFAULT_EXT L".id.txt" //для файла с итогом лексического анализa(идентификаторы и литералы)

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
			int vint;					// значение integer
			struct
			{
				unsigned char len;			// количесво символов в string
				char str[TI_STR_MAXSIZE - 1];	// символы string
			} vstr;	// значение string
		}value;	// значение идентификатора

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