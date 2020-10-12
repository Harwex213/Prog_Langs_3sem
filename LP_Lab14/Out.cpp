#include "stdafx.h"

namespace Out 
{
	OUT getout(wchar_t outfile[])
	{
		OUT temp;
		temp.stream = new ofstream;
		temp.stream->open(outfile);
		if (!temp.stream->is_open())
		{
			temp.stream->close();
			throw ERROR_THROW(114);
		}
		wcscpy_s(temp.logfile, outfile);

		return temp;
	}
	void WriteAnalyze(OUT out, In::IN in, Log::LOG log)
	{
		*out.stream << in.text << endl << endl;

		time_t rawtime;
		struct tm timeinfo;								//структура хранящая текущее время
		char buffer[PARM_MAX_SIZE];
		time(&rawtime);									//текущая дата в секундах
		localtime_s(&timeinfo, &rawtime);				//текущее локальное время, представленное в структуре
		*out.stream << endl << "----- Анализ ----- ";
		strftime(buffer, 300, " Дата: %d.%m.%Y %H:%M:%S", &timeinfo);
		*out.stream << buffer << " ----- " << endl;


		int count_lines = 1;
		int chain_size = 0;
		char* start = NULL;
		char* out_text = NULL;
		//FST::FST fst(
		//	out_text,									// цепочка для распознавания
		//	GRAPH1);
		int i = 0;
		while (i < in.size)
		{
			start = (char*)(in.text+i);
			while (!(in.text[i] == IN_VERT_LINE || in.text[i] == IN_NULL_STR))
			{
				chain_size++;
				i++;
			}
			out_text = new char[chain_size+1];
			out_text[chain_size] = IN_NULL_STR;
			strncpy(out_text, start, chain_size);
			FST::NODE(1, FST::RELATION('a', 1));
			/*fst = { 
				out_text,									
				GRAPH1};
			if (FST::execute(fst))
				*out.stream << "Цепочка: " << out_text << "\tраспознана" << endl;
			else
			{
				*out.stream << "Цепочка: " << out_text << "\tне распознана, содержит ошибку.";
				*out.stream << " Символ: " << out_text[fst.position] << ", строка: " << count_lines << ", позиция: " << fst.position + 1 << endl;

				*log.stream << "Цепочка: " << out_text << "\tне распознана, содержит ошибку.";
				*log.stream << " Символ: " << out_text[fst.position] << ", строка: " << count_lines << ", позиция: " << fst.position + 1 << endl;
			}*/

			delete[] out_text;
			chain_size = 0;
			i++;
			count_lines++;
		}
	}
	void OutClose(OUT out)
	{
		out.stream->close();
		delete out.stream;
		out.stream = NULL;
	}
}