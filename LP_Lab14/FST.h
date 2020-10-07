#pragma once
#include <iostream>
#include <tchar.h>
#include "IT.h"

#define NULL_STRING	char* nothing = NULL;
#define NULL_DATA	FST::INTERIM_DATA nullData = { '\0', IT::UNDEF, IT::U };


namespace FST
{
	struct RELATION								// ребро :символ->вершина графа переходов КА
	{
		char symbol;							// символ перехода
		short nnode;							// номер смежной вершины
		RELATION(char с = 0x00,					// символ перехода
			short ns = NULL);					// новое состояние												
	};

	struct NODE									// вершина графа переходов
	{
		short n_relation;						// количество инциндентных ребер
		RELATION* relations;					// инцидентные ребра; 1 --a--> 2, ребро a инцидентна вершинам 1 и 2
		NODE();
		NODE(
			short n,							// количество инциндентных ребер
			RELATION rel, ...					// список ребер
		);
	};

	struct INTERIM_DATA
	{
		char lexema;					//returnable lexema
		IT::IDDATATYPE iddatatype;
		IT::IDTYPE idtype;
	};

	struct FST
	{
		char** string;							//цепочка (строка, завершатся 0x00 )
		INTERIM_DATA interim_data;
		short position = 0;						//текущая позиция в цепочке 
		short nstates;							//количество состояний автомата
		NODE* nodes;							//граф переходов: [0] -начальное состояние, [nstate-1]-конечное
		short* rstates;							//возможные состояния автомата на данной позиции
		FST(
			INTERIM_DATA idata,
			char* &s,							//цепочка (строка, завершатся 0x00 )
			short ns,							//количество состояний автомата 
			NODE n, ...							//список состояний (граф переходов)
		);
	};

	bool execute(								//выполнить распознавание цепочки 
		FST& fst									//недетерминировнный конечный автомат
	);

};
