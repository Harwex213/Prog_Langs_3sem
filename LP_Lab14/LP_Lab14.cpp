#include "stdafx.h"

// -in:c:#in\in.txt -out:c:#in\out.txt -log:c:#in\log.txt

int wmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, L"Тест:", L"без ошибок", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		LT::LexTable lexTable = LT::Create(in.lxmCounter);
		IT::IdTable idTable = IT::Create(in.idntCouner);
		Analysis::MakeAnalysis(lexTable, idTable);
		Log::WriteIn(log, in);
		Out::OUT out = Out::getout(parm.out);
		Out::WriteAnalyze(out, in, log);
		Log::Close(log);
		Out::OutClose(out);
		Delete(lexTable);
		delete[] in.text;			//Удаляем использованную память
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}

	return 0;
}