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
		idtable.table[idtable.current_size].id = new char[strlen(entry.id)+1];
		strcpy(idtable.table[idtable.current_size].id, entry.id);
		if ((idtable.table[idtable.current_size].iddatatype = entry.iddatatype) == IT::STR)
			idtable.table[idtable.current_size].value.vstr = entry.value.vstr;
		else
			idtable.table[idtable.current_size].value.vint = entry.value.vint;
		idtable.table[idtable.current_size].idtype = entry.idtype;
		idtable.table[idtable.current_size].prefix = entry.prefix;
		idtable.current_size++;
	}
	Entry GetEntry(const IdTable& idtable, int n)
	{
		return idtable.table[n];
	}
	int GetId(IdTable& idtable, char* id, std::list<std::string> prefix, int sn, int psn)
	{
		for (int i = 0; i < idtable.current_size; i++)
		{
			switch (idtable.table[i].idtype)
			{
			case L:
				if (strcmp(idtable.table[i].id, id) == 0 ||
					strncmp(idtable.table[i].id, id, LITERAL_MAXSIZE) == 0)
					return i;
				break;
			default:
				if (strcmp(idtable.table[i].id, id) == 0 ||
					strncmp(idtable.table[i].id, id, ID_MAXSIZE) == 0)
				{
					if (idtable.table[i].idtype == F)
						if (!idtable.table[i].isGlobalFunction)
							return i;
					if (*idtable.table[i].prefix.rbegin() == *prefix.rbegin())
						return i;
				}
				break;
			}
		}
		return LT_TI_NULLXDX;
	}
	bool IsId(IdTable& idtable, Entry entry)
	{
		switch (entry.idtype)
		{
		case L:
			for (int i = 0; i < idtable.current_size; i++)
			{
				if (strncmp(idtable.table[i].id, entry.id, LITERAL_MAXSIZE) == 0)
					return false;
			}
			break;
		default:
			for (int i = 0; i < idtable.current_size; i++)
			{
				if (*idtable.table[i].prefix.rbegin() == *entry.prefix.rbegin())
					if (strcmp(idtable.table[i].id, entry.id) == 0 ||
						strncmp(idtable.table[i].id, entry.id, ID_MAXSIZE) == 0)
						return false;
			}
			break;
		}
		return true;
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