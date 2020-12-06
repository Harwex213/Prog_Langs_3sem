#include "stdafx.h"

namespace LT							// таблица лексем
{
	LexTable Create(int size)			// создать таблицу лексем
	{
		if(size > LT_MAXSIZE)
			throw ERROR_THROW(120);
		LexTable sample;
		sample.maxsize = size;
		sample.current_size = 0;
		sample.table = new Entry[size]; 
		return sample;
	};

	void AddEntry(LexTable& lextable, Entry entry)
	{
		lextable.table[lextable.current_size].lexema = entry.lexema;
		lextable.table[lextable.current_size].position = entry.position;
		lextable.table[lextable.current_size].line = entry.line;
		lextable.table[lextable.current_size].idxTI = entry.idxTI;
		lextable.current_size++;
	};

	Entry GetEntry(LexTable& lextable, int n)
	{
		return lextable.table[n];
	};

	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
	};
}