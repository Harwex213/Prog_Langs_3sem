#pragma once
#include <iostream>
#include <tchar.h>
#include "LT.h"
#include "Error.h"
namespace LT							// таблица лексем
{
	LexTable Create(int size)			// создать таблицу лексем
	{
		if(size > LT_MAXSIZE)
			throw ERROR_THROW(121);
		LexTable sample;
		sample.maxsize = size;
		sample.current_size = 0;
		sample.table = new Entry[size]; 
		return sample;
	};

	void Add(LexTable& lextable, Entry entry)
	{
		lextable.current_size++;
		lextable.table[lextable.current_size] = entry;
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