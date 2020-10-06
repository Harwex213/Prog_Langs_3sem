#pragma once
#include <iostream>
#include <tchar.h>
#define GRAPH1 5, \
FST::NODE(1, FST::RELATION('a', 1)), \
FST::NODE(5, FST::RELATION('b', 1), FST::RELATION('c', 2), FST::RELATION('d', 2), FST::RELATION('e', 2), FST::RELATION('b', 3)), \
FST::NODE(4, FST::RELATION('c', 2), FST::RELATION('d', 2), FST::RELATION('e', 2), FST::RELATION('b', 3)), \
FST::NODE(2, FST::RELATION('b', 3), FST::RELATION('h', 4)), \
FST::NODE()

namespace FST
{
	struct RELATION							// ребро :символ->вершина графа переходов КА
	{
		char symbol;						// символ перехода
		short nnode;						// номер смежной вершины
		RELATION(char с = 0x00,				// символ перехода
			short ns = NULL);				// новое состояние												
	};

	struct NODE								// вершина графа переходов
	{
		short n_relation;					// количество инциндентных ребер
		RELATION* relations;				// инцидентные ребра; 1 --a--> 2, ребро a инцидентна вершинам 1 и 2
		NODE();
		NODE(
			short n,						// количество инциндентных ребер
			RELATION rel, ...				// список ребер
		);
	};

	struct FST
	{
		char** string;					//цепочка (строка, завершатся 0x00 )
		char lexema;					//возвращаемая лексема
		short position = 0;				//текущая позиция в цепочке 
		short nstates;						//количество состояний автомата
		NODE* nodes;						//граф переходов: [0] -начальное состояние, [nstate-1]-конечное
		short* rstates;						//возможные состояния автомата на данной позиции
		FST(
			char* &s,					//цепочка (строка, завершатся 0x00 )
			char lxm,
			short ns,						//количество состояний автомата 
			NODE n, ...						//список состояний (граф переходов)
		);

		void operator = (const FST& other)
		{
			this->string = other.string;
			this->lexema = other.lexema;
			this->position = other.position;
			this->nstates = other.nstates;
			this->nodes = new NODE[this->nstates];
			this->nodes = other.nodes;
			this->rstates = new short[this->nstates];
			memset(this->rstates, 0xff, sizeof(short) * this->nstates);
			this->rstates[0] = 0;
		}
	};

	char execute(							//выполнить распознавание цепочки 
		FST fst							//недетерминировнный конечный автомат
	);

};
