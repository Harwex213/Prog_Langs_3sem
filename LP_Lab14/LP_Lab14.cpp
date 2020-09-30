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
		Automat::AUTOMAT automats;
		char text[] = "integer";
		char* string = text;
		GRAPHES;
		FST::FST graphArray[GRAPHS_SIZE] = { fst1, fst2, fst3, fst4, fst5, fst6, fst7, fst8, fst9, fst10 };
		Automat::createAutomat(automats, graphArray);
		FST::FST fstN = automats['i'];
		cout << string << endl;
		if (FST::execute(automats[string[0]]))
			cout << "WE DONE IT\n";
		else
			cout << "F*CK\n";
		char text1[] = "function";
		string = text1;
		cout << string << endl;
		if (FST::execute(automats[string[0]]))
			cout << "WE DONE IT\n";
		else
			cout << "F*CK\n";
		Log::WriteIn(log, in);
		Out::OUT out = Out::getout(parm.out);
		Out::WriteAnalyze(out, in, log);
		Log::Close(log);
		Out::OutClose(out);
		delete[] in.text;			//Удаляем использованную память
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}

	return 0;
}