#pragma once

#define ID_MAXSIZE		5				// максимальное количество сиволов в идентификаторе
#define TI_MAXSIZE		4096			// максимальное количество эл-ов в таблице идентификаторов 
#define TI_INT_DEFAULT	0x00000000		// значение по умолчанию дл€ типа integer 
#define TI_STR_DEFAULT	0x00			// значение по умолчанию дл€ типа string 
#define TI_NULLIDX		0xffffffff		// нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE	255

#define PARM_ID_DEFAULT_EXT L".id.txt" //дл€ файла с итогом лексического анализa(идентификаторы и литералы)

namespace IT	// таблица идентификатов
{
	enum IDDATATYPE { UNDEF = 0, INT = 1, STR = 2 };			// 0 - UNDEF, 1 - INTEGER,  2 - STRING
	enum IDTYPE { U = 0, P = 1, V = 2, F = 3, GF = 4, L = 5 };	// 0 - UNDEF, 1 - PARAMETR, 2 - VALUE, 3 - FUNCTION, 4 - GLOBAL FUNCTION, 5 - LITERAL

	struct Entry						// строка таблицы идентификаторов
	{
		int idxfirstLE;
		char* id;			// идентификатор (автоматически усекаетс€ до ID_MAXSIZE)
		char* prefix;
		IDDATATYPE	iddatatype;			// тип данных
		IDTYPE	idtype;					// тип идентикатора
		union
		{
			int vint;					// значение integer
			struct
			{
				unsigned char len;			// количесво символов в string
				char str[TI_STR_MAXSIZE];	// символы string
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
	Entry GetEntry(IdTable& idtable, int n);
	int IsId(IdTable& idtable, char id[ID_MAXSIZE+1]);
	void Delete(IdTable& idtable);
}