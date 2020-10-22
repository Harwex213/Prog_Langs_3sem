#include "stdafx.h"

// -in:c:#in\in.txt -out:c:#in\out.txt -log:c:#in\log.txt

int wmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, L"Тест:", L"без ошибок", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		LT::LexTable lexTable = LT::Create(LT_MAXSIZE);
		IT::IdTable idTable = IT::Create(TI_MAXSIZE);
		In::IN in = In::getin(parm.in);
		LexAnalysis::FillTables(in, lexTable, idTable);
		//WriteLexTable
		//WriteIdTable
		PolishNotation::TransformToPolishNotation(lexTable, idTable);
		Log::WriteIn(log, in);
		Out::OUT out = Out::getout(parm.out);
		Out::WriteAnalyze(out, in, log);
		Log::Close(log);
		Out::OutClose(out);
		LT::Delete(lexTable);
		IT::Delete(idTable);
		delete[] in.text;
		std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration < double >> (t2 - t1);

		std::cout << time_span.count() << " seconds.";
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}

	return 0;
}