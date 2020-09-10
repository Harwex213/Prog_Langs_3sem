#include "In.h"
#include "Error.h"
#include <fstream>
using namespace std;
// /c/Workplace/1University/second_cource/Prog_Languages/Labs/Prog_Langs_3sem
namespace In
{
	IN getin(wchar_t* infile)
	{
		//����� ��������� IN sample (����� ������, ������, ������������, ������ ��� ������ ����)
		IN sample;
		sample.size = 0;
		sample.lines = 1;
		sample.ignor = 0;
		sample.text = new unsigned char[IN_MAX_LEN_TEXT];
		ifstream file(infile);

		//���� ��������� ����������
		char unsigned txt_temp;			//������������ ������
		int  position = 1;				//������� (��� ������ ������)
		int	 counter  = 0;				//������� ��� ������ ������������� ����
		bool true_symbol = false;		//������� "true" �������
		bool space_request = false;		//������ ������� �� ��������
		bool ltrl_in = false;			//��������� �� � ��������
		bool chek_file = false;			//�������� ������� �����

		if (file.is_open())
		{
			while ((txt_temp = file.get()) && !file.eof())
			{
				chek_file = true;
				switch (sample.code[txt_temp])
				{
				case IN::T:
					true_symbol = true;
					if (space_request)
					{
						sample.text[counter++] = IN_WHITE_SPACE;
						space_request = false;
						sample.ignor--;
					}
					sample.text[counter++] = txt_temp;
					position++;
					sample.size++;
					break;
				case IN::W:
					if (ltrl_in)
						sample.text[counter++] = IN_WHITE_SPACE;
					if (true_symbol)
						space_request = true;
					sample.ignor++;
					position++;
					sample.size++;
					break;
				case IN::S:
					true_symbol = false;
					space_request = false;
					sample.text[counter++] = txt_temp;
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
					true_symbol = false;
					space_request = false;
					if (ltrl_in)
						ltrl_in = false;
					else
						ltrl_in = true;
					sample.text[counter++] = txt_temp;
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
					true_symbol = false;
					space_request = false;
					if (ltrl_in)
						sample.text[counter++] = IN_CODE_ENDL;
					else
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