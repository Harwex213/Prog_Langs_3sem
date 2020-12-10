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
	void AddEntry(IdTable& idtable, Entry entry)
	{
		idtable.table[idtable.current_size].idName = new char[strlen(entry.idName)+1];
		strcpy(idtable.table[idtable.current_size].idName, entry.idName);
		idtable.table[idtable.current_size].idType = entry.idType;
		idtable.table[idtable.current_size].idDataType = entry.idDataType;
		idtable.table[idtable.current_size].idxfirstLE = entry.idxfirstLE;
		idtable.table[idtable.current_size].visibility = entry.visibility;
		idtable.table[idtable.current_size].value = entry.value;
		idtable.current_size++;
	}
	Entry GetEntry(const IdTable& idtable, int n)
	{
		return idtable.table[n];
	}
	int GetId(const IdTable& idTable, char* id, std::forward_list<std::string> visibility)
	{
		for (int i = 0; i < idTable.current_size; i++)
		{
			if (LexAnalysis::ViewVisibility(visibility, idTable.table[i].visibility) && (strcmp(id, idTable.table[i].idName) == 0))
				return i;
		}
		return LT_TI_NULLXDX;
	}
	void Delete(IdTable& idtable)
	{
		for (int i = 0; i < idtable.current_size; i++)
		{
			delete[] idtable.table[i].idName;
		}
		delete[] idtable.table;
	}
}