#pragma once
#include "In.h"
#include "LT.h"
#include "IT.h"
#include "FST.h"

namespace Analysis
{
	void StartAnalysis(
		In::IN in,					//Contain IN_WORDS
		LT::LexTable& lxmTable,		//To fill lxmTable
		IT::IdTable& idTable		//To fill idTable
	);
	
	FST::INTERIM_DATA UpdateInterimData(
		const FST::FST& fst,		//Contain unique for this fst interim datas
		FST::INTERIM_DATA idata		//To fill interim data
	);
	
	void CreateEntry(
		FST::INTERIM_DATA idata,	//Contain interim data
		LT::LexTable& lxmTable		//To fill lxmTable
	);
}