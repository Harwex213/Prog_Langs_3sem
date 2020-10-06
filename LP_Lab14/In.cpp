#include "stdafx.h"
// /c/Workplace/1University/second_cource/Prog_Languages/Labs/Prog_Langs_3sem
namespace In
{
	IN getin(wchar_t* infile)
	{
		//Задаём параметры IN sample (общий размер, строки, игнорируемые, массив для записи кода)
		IN sample;
		sample.text = new unsigned char[IN_MAX_LEN_TEXT];
		ifstream file(infile);

		//Блок временных переменных
		char unsigned txt_temp;			//Посимвольное чтение
		int  position = 0;				//Позиция (для вывода ошибок)
		int	 counter  = 0;				//Счётчик для записи количества входных символов
		
		char* start = NULL;				//Переменная для разбивки слов
		int word_size = 0;				//Подсчёт длины слова
		char* out_text = NULL;

		char compareINT[] = "integer";
		char compareSTR[] = "string";
		vector<IN_WORD> AlfaLexTable(sample.lxmCounter+1);	//Массив структур со словами (лексемами)
		sample.AlfaLexTable = AlfaLexTable;

		bool long_symbols = false;		//Много символов
		bool single_symbols = false;	//Одиночный символ
		bool space_symbol = false;		//Пробел
		bool ltrl_in = false;			//Находимся ли в литерале
		bool chek_file = false;			//Проверка пустоты файла

		if (file.is_open())
		{
			while ((txt_temp = file.get()) && !file.eof())
			{
				chek_file = true;
				switch (sample.code[txt_temp])
				{
				case IN::A:
				case IN::L:
				case IN::T:
					if (space_symbol && !ltrl_in)
					{
						space_symbol = false;
						sample.text[counter++] = IN_WHITE_SPACE;
						sample.ignor--;
					}
					if (!long_symbols && !ltrl_in)
						start = (char*)(sample.text + counter);
					if (txt_temp == '\'')
						if (!ltrl_in)	ltrl_in = true;
						else			ltrl_in = false;
					word_size++;
					long_symbols = true;
					single_symbols = false;
					space_symbol = false;
					sample.text[counter++] = txt_temp;
					position++;
					sample.size++; 
					break;
				case IN::W:
					long_symbols = false;
					single_symbols = false;
					space_symbol = true;
					if (ltrl_in)
					{
						sample.text[counter++] = IN_WHITE_SPACE;
						long_symbols = true;
						word_size++;
					}
					else
						sample.ignor++;
					position++;
					sample.size++;
					break;
				case IN::S:
					long_symbols = false;
					single_symbols = true;
					space_symbol = false;
					sample.text[counter++] = txt_temp;
					position++;
					sample.size++;
					break;
				//case IN::L:
				//	if (txt_temp == '\'')
				//		if (!ltrl_in)	ltrl_in = true;
				//		else			ltrl_in = false;
				//	if (!longLxm_symbol)
				//		start = (char*)(sample.text + counter);
				//	word_size++;
				//	longLxm_symbol = true;
				//	lxm_symbol = false;
				//	space_symbol = false;
				//	sample.text[counter++] = txt_temp;
				//	position++;
				//	sample.size++;
				//	break;
				//case IN::A:
				//	if (ltrl_in)
				//	{
				//		sample.text[counter++] = txt_temp;
				//		word_size++;
				//	}
				//	else
				//		throw ERROR_THROW_IN(111, sample.lines, position);
				//	position++;
				//	sample.size++;
				//	break;
				case IN::F:
					position++;
					throw ERROR_THROW_IN(111, sample.lines, position);
					break;
				case IN::I:
					sample.ignor++;
					position++;
					sample.size++;
					break;
				default:
					long_symbols = false;
					single_symbols = false;
					space_symbol = false;
					if (ltrl_in)
						throw ERROR_THROW_IN(111, sample.lines, position)
					else
						sample.text[counter++] = sample.code[txt_temp];
					position = 0;
					sample.lines++;
					break;
				}
				if (!long_symbols && word_size != 0)
				{
					out_text = new char[word_size + 1];
					out_text[word_size] = PARM_NULL_STR;
					strncpy(out_text, start, word_size);
					sample.lxmCounter = getword(sample.AlfaLexTable, out_text, position-word_size, sample.lines, sample.lxmCounter);
					word_size = 0;
					if (!strcmp(out_text,compareINT) || !strcmp(out_text, compareSTR)) // BAD
						sample.idntCouner++;
					delete[] out_text;
				}
				if (single_symbols)
				{
					out_text = new char[2];
					out_text[1] = PARM_NULL_STR;
					out_text[0] = txt_temp;
					sample.lxmCounter = getword(sample.AlfaLexTable, out_text, position, sample.lines, sample.lxmCounter);
					delete[] out_text;
				}
			}
			if (!chek_file)
				throw ERROR_THROW(113)
		}
		else
		{
			file.close();
			throw ERROR_THROW(110);
		}
		sample.text[counter] = PARM_NULL_STR;
		file.close();
		return sample;
	}

	int getword(vector<IN_WORD>& table, char* intext, int position, int line, int counter)
	{
		table[counter].text = new char[strlen(intext)];
		strcpy(table[counter].text, intext);
		cout << table[counter].text << "\t\t";
		table[counter].position = position;
		cout << "position: " << table[counter].position << "\t\t";
		table[counter].line = line;
		cout << "line: " << table[counter].line << endl;
		table.resize(++counter+1);
		return counter;
	}
}