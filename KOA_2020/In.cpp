#include "stdafx.h"

namespace In
{
	IN getin(wchar_t* infile)
	{
		// Set IN struct
		IN sample;
		sample.alfaLxmTable = new PARSED_WORDS[LT_MAXSIZE];
		ifstream file(infile);

		//Block of temporary variables
		char unsigned txt_temp;
		bool chek_file = false;
		PARSED_WORDS entry;
		ANALYSIS_DATA interimData;

		if (file.is_open())
		{
			while ((txt_temp = file.get()) && !file.eof())
			{
				chek_file = true;

				sample.size++;
				interimData.positionNumber++;

				AnalyzeLetter(sample.code[txt_temp], txt_temp, interimData, sample);

				entry.line = interimData.lineNumber;

				while (!sample.symbolCounter.empty())
				{
					int tempCounter = sample.symbolCounter.front();
					entry.position = interimData.positionNumber - tempCounter;
					sample.symbolCounter.pop_front();
					entry.text = new char[tempCounter + 1];
					entry.text[tempCounter] = NULL;
					for (int i = 0; i < tempCounter; i++)
					{
						entry.text[i] = sample.symbols.front();
						sample.symbols.pop_front();
					}
					AddWord(sample, entry);
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
		file.close();
		return sample;
	}

	void AddWord(IN& in, PARSED_WORDS entry)
	{
		if (in.wordCounter > LT_MAXSIZE)
			ExpandAlfaLxmTable(in);
		in.alfaLxmTable[in.wordCounter].line = entry.line;
		in.alfaLxmTable[in.wordCounter].position = entry.position;
		if (entry.text != NULL)
		{
			in.alfaLxmTable[in.wordCounter].text = new char[strlen(entry.text)];	
			strcpy(in.alfaLxmTable[in.wordCounter].text, entry.text);
		}
		else
			cout << "\nFound NULL in function 'addword' while chek 'entry.text'\n";
		cout << entry.text << "\t\tposition: " << entry.position << "\t" << entry.line << endl;
		in.wordCounter++;
	};

	void AnalyzeLetter(int symbol_type, char symbol, ANALYSIS_DATA& interimData, IN& in)
	{
		switch (symbol_type)
		{
		case IN::T:
			interimData.wasTrueSymbol = true;
			interimData.symbolCounter++;
			in.symbols.push_back(symbol);
			if (symbol == '\'')
			{
				if (interimData.literalIn)
				{
					if (interimData.wasTrueSymbol)
						interimData.WasTrueSymbol(in);
					interimData.literalIn = false;
				}
				else
					interimData.literalIn = true;
			}
			break;
		case IN::S:
			if (interimData.wasTrueSymbol)
				interimData.WasTrueSymbol(in);
			in.symbols.push_back(symbol);
			interimData.symbolCounter = 1;
			in.symbolCounter.push_back(interimData.symbolCounter);
			interimData.symbolCounter = 0;
			break;
		case IN::F:
			throw ERROR_THROW_IN(111, interimData.lineNumber, interimData.positionNumber);
			break;
		default:
			interimData.lineNumber++;
			interimData.positionNumber = 1;
			if (interimData.literalIn)
				throw ERROR_THROW_IN(111, interimData.lineNumber, interimData.positionNumber);
		case IN::W:
			if (interimData.wasTrueSymbol && !interimData.literalIn)
				interimData.WasTrueSymbol(in);
			break;
		}
	}

	void ExpandAlfaLxmTable(IN& in)
	{
		// dynamic expansion of array
	};
}