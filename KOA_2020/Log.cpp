#include "stdafx.h"

namespace Log
{
	LOG getlog(wchar_t logfile[], wchar_t logLexTableFile[], wchar_t logIdTableFile[])
	{
		LOG temp;
		temp.stream = new ofstream;
		temp.streamLexTable = new ofstream;
		temp.streamIdTable = new ofstream;
		temp.stream->open(logfile);
		temp.streamLexTable->open(logLexTableFile);
		temp.streamIdTable->open(logIdTableFile);
		if (!temp.stream->is_open() && !temp.streamLexTable->is_open() && !temp.streamIdTable->is_open())
		{
			temp.stream->close();
			temp.streamLexTable->close();
			temp.streamIdTable->close();
			throw ERROR_THROW(112);
		}
		wcscpy_s(temp.logfile, logfile);
		wcscpy_s(temp.logLexTableFile, logLexTableFile);
		wcscpy_s(temp.logIdTableFile, logIdTableFile);

		return temp;
	}
	void WriteLine(LOG log, const char* c, ...)
	{
		const char** ptr = &c;

		while (*ptr != "")
		{
			*log.stream << *ptr;
			ptr++;
		}
	}
	void WriteLine(LOG log, const wchar_t* c, ...)
	{
		const wchar_t** ptr = &c;
		char c_char[PARM_MAX_SIZE];

		while (*ptr != L"")
		{
			wcstombs(c_char, *ptr, sizeof(c_char));
			*log.stream << c_char;
			ptr++;
		}
	}
	void WriteLog(LOG log)
	{
		time_t rawtime;
		struct tm timeinfo;			//��������� �������� ������� �����
		char buffer[PARM_MAX_SIZE];

		time(&rawtime);					//������� ���� � ��������
		localtime_s(&timeinfo, &rawtime);	//������� ��������� �����, �������������� � ���������

		*log.stream << "----- �������� ----- ";
		strftime(buffer, 300, " ����: %d.%m.%Y %H:%M:%S", &timeinfo);
		*log.stream << buffer << " ----- " << endl;
	}
	void WriteLogLexTable(LOG log, LT::LexTable lexTable)
	{
		time_t rawtime;
		struct tm timeinfo;			//��������� �������� ������� �����
		char buffer[PARM_MAX_SIZE];

		time(&rawtime);					//������� ���� � ��������
		localtime_s(&timeinfo, &rawtime);	//������� ��������� �����, �������������� � ���������

		*log.streamLexTable << "----- �������� ----- ";
		strftime(buffer, 300, " ����: %d.%m.%Y %H:%M:%S", &timeinfo);
		*log.streamLexTable << buffer << " ----- " << endl;

		int counter = 0;
		for (int i = 0; i < lexTable.table[lexTable.current_size - 1].line; i++)
		{
			*log.streamLexTable << lexTable.table[counter].line << ' ';
			while (lexTable.table[counter].line == i + 1)
			{
				*log.streamLexTable << lexTable.table[counter].lexema;
				if (lexTable.table[counter].lexema == LEX_IDENTIFICATOR || lexTable.table[counter].lexema== LEX_LITERAL)
				{
					*log.streamLexTable << "(" << lexTable.table[counter].idxTI << ")";
				}
				counter++;
			}
			*log.streamLexTable << endl;
		}
	}
	void WriteLogIdTable(LOG log, IT::IdTable idTable)
	{
		time_t rawtime;
		struct tm timeinfo;			//��������� �������� ������� �����
		char buffer[PARM_MAX_SIZE];

		time(&rawtime);					//������� ���� � ��������
		localtime_s(&timeinfo, &rawtime);	//������� ��������� �����, �������������� � ���������

		*log.streamIdTable << "----- �������� ----- ";
		strftime(buffer, 300, " ����: %d.%m.%Y %H:%M:%S", &timeinfo);
		*log.streamIdTable << buffer << " ----- " << endl;


	}
	void WriteParm(LOG log, Parm::PARM parm)
	{
		char c_char[PARM_MAX_SIZE];
		*log.stream << "----- ��������� ----- " << endl;
		wcstombs(c_char, parm.log, sizeof(c_char));
		*log.stream << "-log: " << c_char << endl;
		wcstombs(c_char, parm.out, sizeof(c_char));
		*log.stream << "-out: " << c_char << endl;
		wcstombs(c_char, parm.in, sizeof(c_char));
		*log.stream << "-in: " << c_char << endl;
	}
	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "----- �������� ������ ----- " << endl;
		*log.stream << "���������� ��������: " << in.size << endl;
		*log.stream << "���������������: " << in.ignor << endl;
		*log.stream << "���������� �����: " << in.lines << endl;
	}
	void WriteError(LOG log, Error::ERROR error)
	{
		bool chek_smb = false;
		if (error.inext.line != -1)
			chek_smb = true;
		if (log.stream != NULL && log.stream->is_open())
		{
			*log.stream << "������ " << error.id << ": " << error.message << endl;
			if (chek_smb)
				*log.stream << "������: " << error.inext.line << " �������: " << error.inext.col << endl << endl;
		}
		else
		{
			cout << "������ " << error.id << ": " << error.message << endl;
			if (chek_smb)
				cout << "������: " << error.inext.line << " �������: " << error.inext.col << endl << endl;
		}
	}
	void Close(LOG log)
	{
		log.stream->close();
		delete log.stream;
		log.stream = NULL;
	}
}