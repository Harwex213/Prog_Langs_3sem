#include "In.h"
#include "Error.h"
#include <fstream>
using namespace std;

namespace In
{
	IN getin(wchar_t* infile)
	{
		IN sample;
		sample.size = 0;				//Обнуляем размер, кол-во строк и пропущено
		sample.lines = 1;
		sample.ignor = 0;
		sample.text = new unsigned char[IN_MAX_LEN_TEXT];	//Выделяем массив для записи кода
		ifstream file(infile);			//Входим в поток для чтения
		char unsigned txt_temp;			//Временная переменная для посимвольного чтения
		int  position = 0;				//Временная переменная для хранения позиции
		int	 counter  = 0;
		bool whitespace_existe = false;	//Временная переменная для отображения наличия пробела в прошлой позиции
		bool whitespace_allow = false;
		bool ltrl_in = false;			//Временная переменная для проверки вошли ли в литерал
		bool chek_file = false;			//Булевая переменная для проверки пустоты файла

		if (file.is_open())
		{
			while ((txt_temp = file.get()) && !file.eof())
			{
				chek_file = true;
				switch (sample.code[txt_temp])
				{
				case IN::T:
					sample.text[counter++] = txt_temp;
					position++;
					whitespace_allow = true;
					whitespace_existe = false;
					sample.size++;
					break;
				case IN::W:
					if (ltrl_in || (whitespace_allow && !whitespace_existe)) //1) Мы в литерале? 2) Есть пробел?)
					{
						sample.text[counter++] = IN_WHITE_SPACE;	//Если хотя бы один да - пишем пробелы
						position++;
						whitespace_existe = true;
					}
					else
					{
						sample.ignor++;
						whitespace_existe = false;
					}
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
					whitespace_allow = false;
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
						whitespace_existe = false;
						whitespace_allow = true;
					}
					else
						ltrl_in = true;

					if (!whitespace_existe)
						sample.text[counter++] = txt_temp;
					else
					{
						sample.text[counter - 1] = txt_temp;
						sample.ignor++;
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
					position = 0;
					sample.lines++;
					whitespace_allow = false;
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