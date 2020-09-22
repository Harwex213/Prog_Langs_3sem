#include "In.h"
#include "Error.h"
#include "FST.h"
#include <fstream>
#include <vector>
using namespace std;
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
		int  position = 1;				//Позиция (для вывода ошибок)
		int	 counter  = 0;				//Счётчик для записи количества входных символов
		
		char* start = NULL;				//Переменная для разбивки слов
		int word_size = 0;				//Подсчёт длины слова
		char* out_text = NULL;

		int counterLxm = 0;				//Счётчик для количества лексем (структур)
		vector<IN_WORD> AlfaLexTable(counterLxm+1);	//Массив структур со словами (лексемами)

		bool longLxm_symbol = false;		//
		bool lxm_symbol = false;		//
		bool space_symbol = false;		//
		bool ltrl_in = false;			//Находимся ли в литерале
		bool chek_file = false;			//Проверка пустоты файла

		if (file.is_open())
		{
			while ((txt_temp = file.get()) && !file.eof())
			{
				chek_file = true;
				switch (sample.code[txt_temp])
				{
				case IN::T:
					if (space_symbol)
					{
						space_symbol = false;
						sample.text[counter++] = IN_WHITE_SPACE;
						sample.ignor--;
					}
					if (!longLxm_symbol && !ltrl_in)
						start = (char*)(sample.text + counter);
					word_size++;
					longLxm_symbol = true;
					lxm_symbol = false;
					space_symbol = false;
					sample.text[counter++] = txt_temp;
					position++;
					sample.size++; 
					break;
				case IN::W:
					longLxm_symbol = false;
					lxm_symbol = false;
					space_symbol = true;
					if (ltrl_in)
					{
						sample.text[counter++] = IN_WHITE_SPACE;
						longLxm_symbol = true;
						word_size++;
					}
					else
						sample.ignor++;
					position++;
					sample.size++;
					break;
				case IN::S:
					longLxm_symbol = false;
					lxm_symbol = true;
					space_symbol = false;
					sample.text[counter++] = txt_temp;
					position++;
					sample.size++;
					break;
				case IN::L:
					if (txt_temp == '\'')
						if (!ltrl_in)	ltrl_in = true;
						else			ltrl_in = false;
					if (!longLxm_symbol)
						start = (char*)(sample.text + counter);
					word_size++;
					longLxm_symbol = true;
					lxm_symbol = false;
					space_symbol = false;
					sample.text[counter++] = txt_temp;
					position++;
					sample.size++;
					break;
				case IN::A:
					if (ltrl_in)
					{
						sample.text[counter++] = txt_temp;
						word_size++;
					}
					else
						throw ERROR_THROW_IN(111, sample.lines, position);
					position++;
					sample.size++;
					break;
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
					longLxm_symbol = false;
					lxm_symbol = false;
					space_symbol = false;
					if (ltrl_in)
						throw ERROR_THROW_IN(111, sample.lines, position)
					else
						sample.text[counter++] = sample.code[txt_temp];
					position = 1;
					sample.lines++;
					break;
				}
				if (!longLxm_symbol && word_size != 0)
				{
					out_text = new char[word_size + 1];
					out_text[word_size] = PARM_NULL_STR;
					strncpy(out_text, start, word_size);
					counterLxm = getword(AlfaLexTable, out_text, position, sample.lines, counterLxm);
					word_size = 0;
					delete[] out_text;
				}
				if (lxm_symbol)
				{
					out_text = new char[2];
					out_text[1] = PARM_NULL_STR;
					out_text[0] = txt_temp;
					counterLxm = getword(AlfaLexTable, out_text, position, sample.lines, counterLxm);
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
		table[counter].text = intext;
		cout << table[counter].text << endl;
		table[counter].position = position;
		table[counter].line = line;
		table.resize(++counter+1);
		return counter;
	}
}