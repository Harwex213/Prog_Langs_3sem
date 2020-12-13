#include "stdafx.h"

// -in:c:#in\in.txt -out:c:#in\out.txt -log:c:#in\log.txt

int wmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		//std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

		Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN in = In::getin(parm.in);
		Out::OUT out = Out::getout(parm.out);
		log = Log::getlog(parm.log);

		// Lex Analysis Stage.
		LT::LexTable lexTable = LT::Create(LT_MAXSIZE);
		IT::IdTable idTable = IT::Create(TI_MAXSIZE);
		LexAnalysis::FillTables(in, lexTable, idTable);

		// Write results Stage.
		//WriteLexTable()
		//WriteIdTable()
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Log::WriteIn(log, in);
		Out::WriteAnalyze(out, in, log);

		// Close files Stage.
		Log::Close(log);
		Out::Close(out);

		// Parse Stage.
		// For Debug:
		//MFST_TRACE_START;
		//MFST::Mfst mfst(lexTable, GRB::getGreibach());
		//mfst.start();
		//mfst.printRules();

		// Polish Notation Stage.
		PolishNotation::TransformToPolishNotation(lexTable, idTable);

		// Clear RAM Stage.
		LT::Delete(lexTable);
		IT::Delete(idTable);
		delete[] in.text;

		// Time optimization chek.
		//std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		//std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration < double >> (t2 - t1);
		//std::cout << time_span.count() << " seconds.";
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}

	return 0;
}