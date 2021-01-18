#pragma once
#include "Error.h"
#include "GRB.h"
#include "LT.h"
#include "IT.h"
#include "Log.h"
#include <iomanip>
#include <stack>

using namespace std;
#define MFST_DIAGN_MAXSIZE 2*200
#define MFST_DIAGN_NUMBER 3
#define MFST_TRACE_START  cout<<setfill (' ') << "\n���" << ":" \
								  << setw(26) << left << " �������" \
								  << setw(30) <<left << " ������� �����" \
								  << setw(26) << left << " C�e�" \
								  << endl;
#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)
#define ISNS(n) GRB::Rule::Chain::isN(n)
#define MFST_TRACE1 std::cout<<setw(4)<<left<<(++FST_TRACE_n) <<": " \
							<<setw(20)<<left<<rule.getCRule(rbuf,nrulechain) \
							<<setw(30)<<left<<getCLenta(lbuf, lenta_position) \
							<<setw(20)<<left<<getCSt(sbuf) \
							<<endl;
#define MFST_TRACE2 std::cout<<setw(4)<<left<< FST_TRACE_n<<": " \
							<<setw(20)<<left<<" " \
							<<setw(30)<<left<<getCLenta(lbuf, lenta_position) \
							<<setw(20)<<left<<getCSt(sbuf) \
							<<endl;
#define MFST_TRACE3 std::cout<<setw(4)<<left<< ++FST_TRACE_n<<": " \
							<<setw(20)<<left<<" " \
							<<setw(30)<<left<<getCLenta(lbuf, lenta_position) \
							<<setw(20)<<left<<getCSt(sbuf) \
							<<endl;
#define MFST_TRACE4(c) std::cout<<setw(4)<<left<< ++FST_TRACE_n<<": "<<setw(20)<<left<<c<<endl;
#define MFST_TRACE5(c) std::cout<<setw(4)<<left<< FST_TRACE_n<<": "<<setw(20)<<left<<c<<endl;
#define MFST_TRACE6(c,k) std::cout<<setw(4)<<left<< FST_TRACE_n<<": "<<setw(20)<<left<<c<<k<<endl;
#define MFST_TRACE7 *log.stream<<setw(4)<<left<<state.lenta_position<<": " \
							<<setw(20)<<left<<rule.getCRule(rbuf,state.nrulechain) \
							<<endl;
template <typename T>
struct use_container : T
{
	using T::T;
	using T::c;
};

typedef use_container <std::stack <short>> MFSTSTSTACK;
//typedef std::stack <short>  MFSTSTSTACK; //���� �������� 
namespace MFST
{
	struct MfstState //��������� �������� (��� ����������)
	{
		short lenta_position;   // ������� �� �����
		short nrule;			// ����� �������� �������
		short nrulechain;		// ����� ������� �������, �������� ������� 
		MFSTSTSTACK st;			// ���� ��������
		MfstState();
		MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain);
		//(������� �� �����, ���� ��������, ����� ������� �������)
		MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain);
		//(������� �� �����, ���� ��������, ����� �������� �������, ����� ������� �������)
	};
	struct Mfst //���������� �������
	{
		enum RC_STEP   // ��� �������� ������� step
		{
			NS_OK,				//������� ������� � �������, ������� �������� � ����
			NS_NORULE,			//�� ������� ������� ����������(������ � ����������)
			NS_NORULECHAIN,		//�� ������� ���������� ������� ������� (������ � �������� ����)
			NS_ERROR,			//����������� �������������� ������ ����������
			TS_OK,				//���. ������ ����� == ������� �����, ������������ �����, ��� �����
			TS_NOK,				//���. ������ ����� != ������� �����, ������������� ���������
			LENTA_END,			//������� ������� ����� >= lenta_size
			SURPRISE			//����������� ��� �������� (������ � step)
		};
		struct MfstDiagnosis //����������� 
		{
			short lenta_position;   // ������� �� �����
			RC_STEP rc_step;	    // ��� ���������� ����
			short nrule;			// ����� �������
			short nrule_chain;		// ����� ������� �������
			MfstDiagnosis();
			MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain);
			//(������� � �����, ��� ���������� ����, ����� �������, ����� ������� �������)
		}diagnosis[MFST_DIAGN_NUMBER];   // ��������� ����� �������� ���������
		GRBALPHABET* lenta;			//���������������� (TS/NS) ����� (�� LEX)
		short lenta_position;		// ������� ������� �� ����� 
		short nrule;				//����� �������� �������
		short nrulechain;			//����� ������� �������, �������� �������
		short lenta_size;			//������ �����
		GRB::Graibach grebach;		//��������� �������
		LT::LexTable lex;			// ��������� ������ ������������ �����������
		IT::IdTable idtable;
		MFSTSTSTACK st;				//���� ��������
		use_container<std::stack <MfstState>> storestate; // ���� ��� ���������� ���������
		Mfst();
		Mfst(LT::LexTable plex, IT::IdTable pid, GRB::Graibach pgrebach);
		//(���� ����, ���������� �������
		char* getCSt(char* buf);	//�������� ���������� �����
		char* getCLenta(char* buf, short pos, short n = 25); //�����: n �������� � pos
		char* getDiagnosis(short n, char* buf); //�������� n-�� ������ ��� 0�00
		bool savestate();			//��������� ��������� ��������
		bool reststate();			//������������ ��������� ��������
		bool push_chain(GRB::Rule::Chain chain); //��������� ������� ������� � ����
		RC_STEP step();				//��������� ��� ��������
		bool start(Log::LOG log);	//��������� �������
		bool savediagnosis(RC_STEP pprc_step); //��� ���������� ����
		void printrules(Log::LOG log);			//������� ������������������ ������
		struct Deducation //�����
		{
			short size;		//���������� ����� � ������
			short* nrules;	//������ ������ ����������
			short* nrulechains; //������ ������� ������ ��������� (nrules)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		} deducation;
		bool savededucation(); //��������� ������ ������
	};
}
