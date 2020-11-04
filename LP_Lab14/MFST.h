#pragma once
#include "Error.h"
#include "GRB.h"
#include "LT.h"
#include <stack>
#include <string>

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESAGE
#define MFST_DIAGN_NUMBER 3
typedef std::stack<short> MFSTSTSTACK;

namespace MFST
{
	struct MfstState			// ��������� �������� (��� ����������)
	{
		std::string loveOfAnuta = "anuta molodec";
		short lenta_position;	// ������� �� �����
		short nrule;			// ����� �������� �������
		short nrulechain;		// ����� ������� ������� � ������ �������
		MFSTSTSTACK st;			// ���� ��������
		MfstState();
		MfstState(
			short pposition,	// ������� �� �����
			MFSTSTSTACK pst,	// ���� ��������
			short nrulechain	// ����� ������� ������� � 
		);
		MfstState(
			short pposition,	// ������� �� �����
			MFSTSTSTACK pst,	// ���� ��������
			short pnrule,		// ����� �������� �������
			short pnrulechain	// ����� ������� ������� � ������� �������
		);
	};

	struct Mfst					// ���������� �������
	{
		enum RC_STEP			// ��� �������� ������� step
		{
			NS_OK,				// ������� ������� � �������, ������� �������� � ����
			NS_NORULE,			// �� ������� ������� ���������� (������ � ����������)
			NS_NORULECHAIN,		// �� ������� ���������� ������� ������� (������ � �������� ����)
			NS_ERROR,			// ����������� �������������� ������ ����������
			TS_OK,				// ������� ������ ����� == ������� �����, ����������� �����, pop �����
			TS_NOK,				// ������� ������ ����� != ������� �����, ������������� ���������
			LENTA_END,			// ������� ������� ����� >= lenta_size
			SURPRISE			// ����������� ��� �������� (������ � step)
		};
		
		struct MfstDiagnosis		// �����������
		{
			short lenta_position;	// ������� �� �����
			RC_STEP rc_step;		// ��� ���������� ����
			short nrule;			// ����� �������
			short nrule_chain;		// ����� ������� �������
			MfstDiagnosis();		// 
			MfstDiagnosis(			//	
				short	plenta_position,	// ������� �� �����
				RC_STEP prc_step,			// ��� ���������� ����
				short	pnrule,				// ����� �������
				short	pnrule_chain		// ����� ������� �������
			);
		} diagnosis[MFST_DIAGN_NUMBER];		// ��������� ����� �������� ���������

		GRBALPHABET* lenta;					// ��������������� (TS/NS) ����� (�� lex)
		short lenta_position;				// ������� ������� �� �����
		short nrule;						// ����� �������� �������
		short nrulechain;					// ����� ������� ������� � ������� �������
		short lenta_size;					// ������� �����
		GRB::Greibach grebach;				// ���������� �������
		LT::LexTable lex;					// ��������� ������ ������������ �����������
		MFSTSTSTACK st;						// ���� ��������
		std::stack<MfstState> storestate;	// ���� ��� ���������� ���������
		
		Mfst();
		Mfst(								
			LT::LexTable plex,				// ��������� ������ ������������ �����������
			GRB::Greibach pgrebach			// ���������� �������
		);
		char* GetCSt(char* buf);			// �������� ���������� �����
		char* getCLenta(char* buf, short pos, short n = 25);	// �����: n �������� � pos
		char* getDiagnosis(char* buf, short n);		// �������� n-�� ������ ����������� ��� 0�00
		bool saveState();					// ��������� ��������� ��������
		bool restState();					// ������������ ��������� ��������
		bool push_chain(					// ��������� ������� ������� � ����
			GRB::Rule::Chain chain			// ������� �������
		);
		RC_STEP	step();						// ��������� ��� ��������
		bool start();						// ��������� �������
		bool saveDiagnosis(
			RC_STEP pprc_step				// ��� ���������� ����
		);
		void printRules();					// ������� ������������������ ������

		struct Deducation					// �����
		{
			short size;						// ���������� ����� � ������
			short* nrules;					// ����� ������� ����������
			short* nrulechains;				// ������ ������� ������� ���������� (nrules)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		} deducation;

		bool saveDeducation();				// ��������� ������ ������
	};
}