#pragma once
#include <list>

#define ID_MAXSIZE		5				// максимальное количество сиволов в идентификаторе
#define LITERAL_MAXSIZE	20
#define TI_MAXSIZE		4096			// максимальное количество эл-ов в таблице идентификаторов 
#define TI_INT_DEFAULT	0x00000000		// значение по умолчанию дл€ типа integer 
#define TI_STR_DEFAULT	0x00			// значение по умолчанию дл€ типа string
#define TI_STR_MAXSIZE	255

#define PARM_ID_DEFAULT_EXT L".id.txt" //дл€ файла с итогом лексического анализa(идентификаторы и литералы)

namespace IT	// таблица идентификатов
{
	enum IDDATATYPE { UNDEF = 0, INT = 1, STR = 2 };			// 0 - UNDEF, 1 - INTEGER,  2 - STRING
	enum IDTYPE { U = 0, P = 1, V = 2, F = 3, L = 4 };	// 0 - UNDEF, 1 - PARAMETR, 2 - VALUE, 3 - FUNCTION, 4 - GLOBAL FUNCTION, 5 - LITERAL

	struct Entry						// строка таблицы идентификаторов
	{
		int idxfirstLE;
		char* id = NULL;			// идентификатор (автоматически усекаетс€ до ID_MAXSIZE)
		std::list<std::string> prefix;
		bool isGlobalFunction = false;
		IDDATATYPE	iddatatype = UNDEF;		// тип данных
		IDTYPE	idtype  = U;				// тип идентикатора
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

	struct IdTable // экземпл€р таблицы идентификаторов
	{
		int maxsize;				// емкость таблицы идентификаторов < TI_MAXSIZE
		int current_size;			// текущий размер таблицы идентификаторов < maxsize
		Entry* table;				// массив строк таблицы идентификаторов
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