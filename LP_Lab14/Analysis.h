#pragma once
#include "In.h"
#include "LT.h"
#include "IT.h"
#include "FST.h"

namespace Analysis
{
	struct INTERIM_DATA
	{
		//lexema sector
		char lexema;					//returnable lexema
		int position;
		int line;

		//identificator sector
		bool IsIdentificator = false;
		bool IsGlobalFunction = false;
		int idxfirstLE;
		char idName[ID_MAXSIZE + 1];			// идентификатор (автоматически усекается до ID_MAXSIZE
		char* idGFName;
		char* prefix;
		IT::IDDATATYPE	iddatatype = IT::UNDEF;			// тип данных
		IT::IDTYPE	idtype = IT::U;					// тип идентикатора
		union
		{
			int vint;					// значение integer
			struct
			{
				unsigned char len;			// количесво символов в string
				char str[TI_STR_MAXSIZE];	// символы string
			} vstr;	// значение string
		}value;	// значение идентификатора
	};

	void StartAnalysis(
		const In::IN& in,					//Contain IN_WORDS
		LT::LexTable& lxmTable,		//To fill lxmTable
		IT::IdTable& idTable		//To fill idTable
	);
	
	void UpdateInterimData(
		const FST::FST& fst,		//Contain unique for this fst interim datas
		INTERIM_DATA* idata			//To fill interim data
	);

	void UpdateInterimData(
		const FST::FST& fst,		//Contain unique for this fst interim datas
		INTERIM_DATA* idata			//To fill interim data
	);

	INTERIM_DATA* ZeroizeInterimData(
		INTERIM_DATA* idata			//Contain interim data
	);
	
	void CreateEntry(
		INTERIM_DATA* idata,		//Contain interim data
		LT::LexTable& lxmTable		//To fill lxmTable
	);

	void CreateEntry(
		const INTERIM_DATA* idata,		//Contain interim data
		IT::IdTable& idTable		//To fill idTable
	);
}