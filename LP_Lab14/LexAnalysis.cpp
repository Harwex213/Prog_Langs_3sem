#include "stdafx.h"

namespace LexAnalysis
{
	void FillLexTable(In::IN& in, LT::LexTable& lextable)
	{
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
			if (entry.lexema[LEXEMA_FIXSIZE - 1] == LEX_INTORSTR)
				in.idCounter++;
		}
		//int counter = 0;
		//for (int i = 0; i < in.lines; i++)
		//{
		//	cout << lextable.table[counter].sn << ' ';
		//	while (lextable.table[counter].sn == i + 1)
		//	{
		//		cout << lextable.table[counter++].lexema;
		//	}
		//	cout << endl;
		//}
	};

	void FillIdTable(const In::IN& in, const LT::LexTable& lextable, IT::IdTable& idtable)
	{
		//Пробегаемся по таблице лексем и ищем идентификаторы
		//Пока не нашли идентификатор -	Заполняем у лексем idxTI "нулём"
		//Когда нашли идентификатор:
		//1) Делаем трёхшаговую итерацию назад
		//2) На каждой итерации с помощью switch определяем тип данных и тип идентика
		//3) Если дошли до другого идентификатора - закончить итерации
		//Если ничего не собрали - этот идентификатор уже объявлен
		//Если что-то нашли - засунуть в IsId(IsLiteral) с целью:
		//1) Проверить на переобъявление
		//2) Выяснить idxTI
		//Если нашли GF - создать область видимости
		//В соотвествии с собранными данными заполнить их в entry
		//Указать prefix
		//С помощью in (индексы совпадают) - заполнить название идентика (Помнить про L и GF!)
		//С помощью in - заполнить значения у L
		//У !L заполнить стандартными значениями


	};
}