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
		Automat::AUTOMAT automats;
		GRAPHES;
		automats.KeyWord = graphArray;
		LT::Entry entry;

		for (int i = 0; i < in.lexCounter; i++)
		{
			string = in.alfaLxmTable[i].text;
			entry.psn = in.alfaLxmTable[i].position;
			entry.sn = in.alfaLxmTable[i].line;
			entry.lexema[LEXEMA_FIXSIZE] = IN_NULL_STR;
			entry.lexema[LEXEMA_FIXSIZE - 1] = automats[string[0]].lexema;
			if (!FST::execute(automats[string[0]]))
			{
				entry.lexema[LEXEMA_FIXSIZE - 1] = LEX_ID;
				if (!FST::execute(automats.KeyWord[IDENTIFY_INDEX]))
					throw ERROR_THROW_IN(111, entry.sn, entry.psn);
			}
			Add(lextable, entry);
		}

		int counter = 0;
		for (int i = 0; i < in.lines; i++)
		{
			cout << lextable.table[counter].sn << ' ';
			while (lextable.table[counter].sn == i + 1)
			{
				cout << lextable.table[counter++].lexema;
			}
			cout << endl;
		}
	};

	void FillIdTable(const In::IN& in, const LT::LexTable& lextable, IT::IdTable& idtable)
	{

	};
}