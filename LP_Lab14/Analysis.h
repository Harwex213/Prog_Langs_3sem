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
		char idName[ID_MAXSIZE + 1];			// ������������� (������������� ��������� �� ID_MAXSIZE
		char* idGFName;
		char* prefix;
		IT::IDDATATYPE	iddatatype = IT::UNDEF;			// ��� ������
		IT::IDTYPE	idtype = IT::U;					// ��� ������������
		union
		{
			int vint;					// �������� integer
			struct
			{
				unsigned char len;			// ��������� �������� � string
				char str[TI_STR_MAXSIZE];	// ������� string
			} vstr;	// �������� string
		}value;	// �������� ��������������
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