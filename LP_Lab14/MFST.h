#pragma once
#include "Error.h"
#include "GRB.h"
#include "LT.h"
#include <stack>
#include <string>

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESAGE
#define MFST_DIAGN_NUMBER 3
typedef std::stack<short> MFSTSTSTACK;

namespace MFST
{
	struct MfstState			// состояние автомата (для сохранения)
	{
		std::string loveOfAnuta = "anuta molodec";
		short lenta_position;	// позиция на ленте
		short nrule;			// номер текущего правила
		short nrulechain;		// номер текущей цепочки в тукщем правиле
		MFSTSTSTACK st;			// стек автомата
		MfstState();
		MfstState(
			short pposition,	// позиция на ленте
			MFSTSTSTACK pst,	// стек автомата
			short nrulechain	// номер текущей цепочка в 
		);
		MfstState(
			short pposition,	// позиция на ленте
			MFSTSTSTACK pst,	// стек автомата
			short pnrule,		// номер текущего правила
			short pnrulechain	// номер текущей цепочки в текущем правиле
		);
	};

	struct Mfst					// магазинный автомат
	{
		enum RC_STEP			// код возврата функции step
		{
			NS_OK,				// найдена цепочка и правило, цепочка записана в стек
			NS_NORULE,			// не найдено правило грамматики (ошибка в грамматике)
			NS_NORULECHAIN,		// не найдена подходящая цепочка правила (ошибка в исходном коде)
			NS_ERROR,			// неизвестный нетерминальный символ грамматики
			TS_OK,				// текущий символ ленты == вершине стека, подвинулась лента, pop стека
			TS_NOK,				// текущий символ ленты != вершине стека, восстановлено состояние
			LENTA_END,			// текущая позиция ленты >= lenta_size
			SURPRISE			// неожиданный код возврата (ошибка в step)
		};
		
		struct MfstDiagnosis		// диагностика
		{
			short lenta_position;	// позиция на ленте
			RC_STEP rc_step;		// код завершения шага
			short nrule;			// номер правила
			short nrule_chain;		// номер цепочки правила
			MfstDiagnosis();		// 
			MfstDiagnosis(			//	
				short	plenta_position,	// позиция на ленте
				RC_STEP prc_step,			// код завершения шага
				short	pnrule,				// номер правила
				short	pnrule_chain		// номер цепочки правила
			);
		} diagnosis[MFST_DIAGN_NUMBER];		// последние самые глубокие сообщения

		GRBALPHABET* lenta;					// перекодированая (TS/NS) лента (из lex)
		short lenta_position;				// текущая позиция на ленте
		short nrule;						// номер текущего правила
		short nrulechain;					// номер текущей цепочки в текущем правиле
		short lenta_size;					// размерз ленты
		GRB::Greibach grebach;				// грамматика Грейбах
		LT::LexTable lex;					// результат работы лексического анализатора
		MFSTSTSTACK st;						// стек автомата
		std::stack<MfstState> storestate;	// стек для сохранения состояний
		
		Mfst();
		Mfst(								
			LT::LexTable plex,				// результат работы лексического анализатора
			GRB::Greibach pgrebach			// грамматика Грейбах
		);
		char* GetCSt(char* buf);			// получить содержимое стека
		char* getCLenta(char* buf, short pos, short n = 25);	// лента: n символов с pos
		char* getDiagnosis(char* buf, short n);		// получить n-ую строку диагностики или 0х00
		bool saveState();					// сохранить состояние автомата
		bool restState();					// восстановить состояние автомата
		bool push_chain(					// поместить цепочку правила в стек
			GRB::Rule::Chain chain			// цепочка правила
		);
		RC_STEP	step();						// выполнить шаг автомата
		bool start();						// запустить автомат
		bool saveDiagnosis(
			RC_STEP pprc_step				// код завершения шага
		);
		void printRules();					// вывести последовательность правил

		struct Deducation					// вывод
		{
			short size;						// количество шагов в выводе
			short* nrules;					// номер правила грамматики
			short* nrulechains;				// номера цепочек правила грамматики (nrules)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		} deducation;

		bool saveDeducation();				// сохранить дерево вывода
	};
}