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
	void Add(IdTable& idtable, Entry entry)
	{
		idtable.table[idtable.current_size].idxfirstLE = entry.idxfirstLE;
		idtable.table[idtable.current_size].id = new char[strlen(entry.id)];
		strcpy(idtable.table[idtable.current_size].id, entry.id);
		idtable.table[idtable.current_size].iddatatype = entry.iddatatype;
		idtable.table[idtable.current_size].idtype = entry.idtype;
		idtable.table[idtable.current_size].value = entry.value;
		idtable.current_size++;
	}
	Entry GetEntry(IdTable& idtable, int n)
	{
		return idtable.table[n];
	}
	int IsId(IdTable& idtable, char* id)
	{
		if (id)
			for (int i = 0; i < idtable.current_size; i++)
			{
				if (strcmp(idtable.table[i].id, id) == 0)
					return i;
				if (strncmp(idtable.table[i].id, id, strlen(idtable.table[i].id)) == 0)
					return i;
			}
		return LT_TI_NULLXDX;
	}
	void Delete(IdTable& idtable)
	{
		for (int i = 0; i < idtable.current_size; i++)
		{
			delete[] idtable.table[i].id;
		}
		delete[] idtable.table;
	}
}