#include "stdafx.h"

namespace IT
{
	IdTable Create(int size)
	{

		if (size > TI_MAXSIZE)
			throw ERROR_THROW(140);
		IdTable sample;
		sample.maxsize = size;
		sample.current_size = 0;
		sample.table = new Entry[size];
		return sample;
	}
	//void Add(IdTable& idtable, Entry entry)
	//{

	//}
	//Entry GetEntry(IdTable& idtable, int n)
	//{

	//}
	//int IsId(IdTable& idtable, char id[ID_MAXSIZE])
	//{

	//}
	//void PrintIdTable(const wchar_t* in)
	//{

	//}
	//void Delete(IdTable& idtable)
	//{

	//}
}