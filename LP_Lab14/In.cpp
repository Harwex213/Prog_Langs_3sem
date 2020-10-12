#include "stdafx.h"
// /c/Workplace/1University/second_cource/Prog_Languages/Labs/Prog_Langs_3sem
namespace In
{
	IN getin(wchar_t* infile)
	{
		//Set IN struct
		IN sample;
		sample.text = new unsigned char[IN_MAX_LEN_TEXT];
		sample.alfaLxmTable = new PARSED_WORDS[LT_MAXSIZE];
		ifstream file(infile);

		//Block of temporary variables
		char unsigned txt_temp;			//Character-by-character reading
		int  position = 0;				//Position for ERRORs
		int	 counter  = 0;				//Counter for in.text
		
		char* start = NULL;				//Pointer for split word
		int word_size = 0;				//Counter of spliting word
		PARSED_WORDS entry;				//Structure to add in alfaLxmTable

		bool trueLongSmbl = false;		//There are many symbols
		bool trueSignleSmbl = false;	//It's single symbols
		bool space_symbol = false;		//Whitespace
		bool ltrl_in = false;			//Are we in literal?
		bool chek_file = false;			//Checking if the file is empty

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
					if (!trueLongSmbl && !ltrl_in)
						start = (char*)(sample.text + counter);
					if (txt_temp == '\'')
						if (!ltrl_in)	ltrl_in = true;
						else			ltrl_in = false;
					word_size++;
					trueLongSmbl = true;
					trueSignleSmbl = false;
					space_symbol = false;
					sample.text[counter++] = txt_temp;
					position++;
					sample.size++; 
					break;
				case IN::W:
					trueLongSmbl = false;
					trueSignleSmbl = false;
					space_symbol = true;
					if (ltrl_in)
					{
						sample.text[counter++] = IN_WHITE_SPACE;
						trueLongSmbl = true;
						word_size++;
					}
					else
						sample.ignor++;
					position++;
					sample.size++;
					break;
				case IN::S:
					trueLongSmbl = false;
					trueSignleSmbl = true;
					space_symbol = false;
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
					trueLongSmbl = false;
					trueSignleSmbl = false;
					space_symbol = false;
					if (ltrl_in)
						throw ERROR_THROW_IN(111, sample.lines, position)
					else
						sample.text[counter++] = sample.code[txt_temp];
					position = 0;
					break;
				}
				if (!trueLongSmbl && word_size != 0)
				{
					entry.line = sample.lines;
					entry.position = position;
					entry.text = new char[word_size+1];
					entry.text[word_size] = IN_NULL_STR;
					strncpy(entry.text, start, word_size);
					addword(sample, entry);
					delete[] entry.text;
					word_size = 0;
				}
				if (trueSignleSmbl)
				{
					entry.line = sample.lines;
					entry.position = position;
					entry.text = new char[2];
					entry.text[1] = IN_NULL_STR;
					entry.text[0] = txt_temp;
					addword(sample, entry);
					delete[] entry.text;
				}
				if (txt_temp == '\n')
					sample.lines++;
			}
			if (!chek_file)
				throw ERROR_THROW(113)
		}
		else
		{
			file.close();
			throw ERROR_THROW(110);
		}
		sample.text[counter] = IN_NULL_STR;
		file.close();
		return sample;
	}

	void addword(IN& in, PARSED_WORDS entry)
	{
		if (in.lexCounter > LT_MAXSIZE)
			expandAlfaLxmTable(in);
		in.alfaLxmTable[in.lexCounter].line = entry.line;
		in.alfaLxmTable[in.lexCounter].position = entry.position;
		if (entry.text != NULL)
		{
			in.alfaLxmTable[in.lexCounter].text = new char[strlen(entry.text)];
			strcpy(in.alfaLxmTable[in.lexCounter].text, entry.text);
		}
		else
			cout << "\nFound NULL in function 'addword' while chek 'entry.text'\n";
		in.lexCounter++;
	};

	void expandAlfaLxmTable(IN& in)
	{
		//dynamic expansion of array
	};
}