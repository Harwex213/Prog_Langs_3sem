#include "stdafx.h"

namespace LT							// таблица лексем
{
	void AddEntry(LexTable& lextable, Entry& entry)
	{
		lextable.table.push_back(entry);
		lextable.current_size++;
	};

	Entry GetEntry(LexTable& lextable, int n)
	{
		return lextable.table[n];
	};

	void Delete(LexTable& lextable)
	{
		lextable.table.clear();
		lextable.table.shrink_to_fit();
	};

	char GetOperationSymbol(const Entry& entry)
	{
		switch (entry.operationType)
		{
		case PLUS:
			return SYMBOL_PLUS;
			break;
		default:
			return NULL;
			break;
		}
	}
}