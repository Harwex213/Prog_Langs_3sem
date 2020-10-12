#include "stdafx.h"

namespace LexAnalysis
{
	void FillLexTable(In::IN& in, LT::LexTable& lextable)
	{
		//ѕри каждой итерации выт€гиваем из массива слово дл€ разбора
		//ƒелаем разбор
		//Ќа основе возвращаемого значени€ делаем вывод (продолжаем или нет)
		//≈сли находим идентификатор - увеличиваем in.idCounter
		//«аписываем полученные данные в таблицу лексем

		char* string = NULL;

		for (int i = 0; i < in.lexCounter; i++)
		{
			//in.alfaLxmTable[i];
		}
	};

	void FillIdTable(const In::IN& in, const LT::LexTable& lextable, IT::IdTable& idtable)
	{

	};
}