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
		idtable.table[idtable.current_size].idName = new char[strlen(entry.idName)+1];
		strcpy(idtable.table[idtable.current_size].idName, entry.idName);
		// idDataType
		idtable.table[idtable.current_size].idType = entry.idType;
		idtable.table[idtable.current_size].visibility = entry.visibility;
		idtable.current_size++;
	}
	Entry GetEntry(const IdTable& idtable, int n)
	{
		return idtable.table[n];
	}
	int GetId(IdTable& idtable, char* id, std::list<std::string> prefix, int sn, int psn)
	{
		//for (int i = 0; i < idtable.current_size; i++)
		//{
		//	switch (idtable.table[i].idtype)
		//	{
		//	case L:
		//		if (strcmp(idtable.table[i].id, id) == 0 ||
		//			strncmp(idtable.table[i].id, id, LITERAL_MAXSIZE) == 0)
		//			return i;
		//		break;
		//	default:
		//		if (strcmp(idtable.table[i].id, id) == 0 ||
		//			strncmp(idtable.table[i].id, id, ID_MAXSIZE) == 0)
		//		{
		//			if (idtable.table[i].idtype == F)
		//				if (!idtable.table[i].isGlobalFunction)
		//					return i;
		//			if (*idtable.table[i].prefix.rbegin() == *prefix.rbegin())
		//				return i;
		//		}
		//		break;
		//	}
		//}
		return LT_TI_NULLXDX;
	}
	bool IsId(IdTable& idtable, Entry entry)
	{
		return true;
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