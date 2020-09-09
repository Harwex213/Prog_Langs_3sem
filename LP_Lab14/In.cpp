#include "In.h"
#include "Error.h"
#include <fstream>
using namespace std;

namespace In
{
	IN getin(wchar_t* infile)
	{
		//Задаём параметры IN sample (общий размер, строки, игнорируемые, массив для записи кода)
		IN sample;
		sample.size = 0;
		sample.lines = 1;
		sample.ignor = 0;
		sample.text = new unsigned char[IN_MAX_LEN_TEXT];
		ifstream file(infile);

		//Блок временных переменных
		char unsigned txt_temp;			//Посимвольное чтение
		int  position = 1;				//Позиция (для вывода ошибок)
		int	 counter  = 0;				//Счётчик для записи обработонного кода
		bool whitespace_existe = false;	//Присутствие (или отсутствие) пробела в прошлой строке
		bool separator_existe = false;	//Присутствие (или отсутствие) сепаратора в прошлой строке
		bool ltrl_in = false;			//Вошли ли в литерал
		bool chek_file = false;			//Проверка пустоты файла

		if (file.is_open())
		{
			while ((txt_temp = file.get()) && !file.eof())
			{
				chek_file = true;
				switch (sample.code[txt_temp])
				{
				case IN::T:
					sample.text[counter++] = txt_temp;
					whitespace_existe = false;
					separator_existe = false;
					position++;
					sample.size++;
					break;
				case IN::W: 
					if (ltrl_in || position != 1 && !(whitespace_existe || separator_existe))
					{
						sample.text[counter++] = IN_WHITE_SPACE;
						whitespace_existe = true;
					}
					else
					{
						sample.ignor++;
						if (separator_existe)
						{
							whitespace_existe = false;
							separator_existe = false;
						}
					}
					position++;
					sample.size++;
					break;
				case IN::S:
					if (ltrl_in || !whitespace_existe)
						sample.text[counter++] = txt_temp;
					else
					{
						sample.text[counter - 1] = txt_temp;
						sample.ignor++;
						whitespace_existe = false;
					}
					separator_existe = true;
					position++;
					sample.size++;
					break;
				case IN::A:
					if (ltrl_in)
						sample.text[counter++] = txt_temp;
					else
						throw ERROR_THROW_IN(111, sample.lines, position);
					position++;
					sample.size++;
					break;
				case IN::L:
					if (ltrl_in)
					{
						ltrl_in = false;
						sample.text[counter++] = txt_temp;
						separator_existe = true;
					}
					else
					{
						ltrl_in = true;
						if (whitespace_existe)
						{
							sample.text[counter - 1] = txt_temp;
							sample.ignor++;
							whitespace_existe = false;
						}
						else
							sample.text[counter++] = txt_temp;
					}
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
					sample.text[counter++] = sample.code[txt_temp];
					position = 1;
					sample.lines++;
					break;
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
}