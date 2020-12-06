#include "stdafx.h"

namespace LexAnalysis
{
	void Lexer(const In::IN& in, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		Graphs::GRAPHS automat;
		AnalysisData analysisData;
		FST::FST* temp;

		for (int i = 0; i < in.wordCounter; i++)
		{
			automat.string = in.alfaLxmTable[i].text;

			if (FindGraph(automat.tests[automat.string[0]], temp))
			{
				if (temp->lexema == LEX_IDENTIFICATOR)
				{

				}
				else
				{
					CheckLexema(*temp);
				}
			}
			else
				throw ERROR_THROW_IN(122, in.alfaLxmTable[i].line, in.alfaLxmTable[i].position)
		}
		cout << "DONE";
	}

	bool FindGraph(const std::vector<FST::FST*> graph, FST::FST*& temp)
	{
		bool ExecuteDone = false;
		for (int i = 0; !ExecuteDone && i < graph.size(); i++)
		{
			ExecuteDone = FST::execute(*graph[i]);
			temp = graph[i];
		}
		return ExecuteDone;
	}

	void CheckLexema(const FST::FST& temp)
	{
		switch (temp.lexema)
		{
		case LEX_DATATYPE:

			break;
		default:
			break;
		}
	}
}