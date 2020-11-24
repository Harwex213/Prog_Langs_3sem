#include "stdafx.h"

namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG temp;
		temp.stream = new ofstream;
		temp.stream->open(logfile);
		if (!temp.stream->is_open())
		{
			temp.stream->close();
			throw ERROR_THROW(112);
		}
		wcscpy_s(temp.logfile, logfile);

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

		*log.stream << endl << "----- �������� ----- ";
		strftime(buffer, 300, " ����: %d.%m.%Y %H:%M:%S", &timeinfo);
		*log.stream << buffer << " ----- " << endl;
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