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
#define MFST_TRACE_START  cout<<setfill (' ') << "\nШаг" << ":" \
								  << setw(26) << left << " Правило" \
								  << setw(30) <<left << " Входная лента" \
								  << setw(26) << left << " Cтeк" \
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
//typedef std::stack <short>  MFSTSTSTACK; //стек автомата 
namespace MFST
{
	struct MfstState //Состояние автомата (для сохранения)
	{
		short lenta_position;   // позиция на ленте
		short nrule;			// номер текущего правила
		short nrulechain;		// номер текущей цепочки, текущего правила 
		MFSTSTSTACK st;			// стек автомата
		MfstState();
		MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain);
		//(позиция на ленте, стек автомата, номер текущей цепочки)
		MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain);
		//(позиция на ленте, стек автомата, номер текущего правила, номер текущей цепочки)
	};
	struct Mfst //магазинный автомат
	{
		enum RC_STEP   // код возврата функции step
		{
			NS_OK,				//найдено правило и цепочка, цепочка записана в стек
			NS_NORULE,			//не найдено правило грамматики(ошибка в грамматике)
			NS_NORULECHAIN,		//не найдена подходящая цепочка правила (ошибка в исходном коде)
			NS_ERROR,			//неизвестный нетерминальный символ грамматики
			TS_OK,				//тек. символ ленты == вершине стека, продвинулась лента, рор стека
			TS_NOK,				//тек. символ ленты != вершине стека, восстановлено состояние
			LENTA_END,			//текущая позиция ленты >= lenta_size
			SURPRISE			//неожиданный код возврата (ошибка в step)
		};
		struct MfstDiagnosis //диагностика 
		{
			short lenta_position;   // позиция на ленте
			RC_STEP rc_step;	    // код завершения шага
			short nrule;			// номер правила
			short nrule_chain;		// номер цепочки правила
			MfstDiagnosis();
			MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain);
			//(позиция в ленте, код завершения шага, номер правила, номер цепочки правила)
		}diagnosis[MFST_DIAGN_NUMBER];   // последние самые глубокие сообщения
		GRBALPHABET* lenta;			//перекодированная (TS/NS) лента (из LEX)
		short lenta_position;		// текущая позиция на ленте 
		short nrule;				//номер текущего правила
		short nrulechain;			//номер текущей цепочки, текущего правила
		short lenta_size;			//размер ленты
		GRB::Graibach grebach;		//граматика Грейбах
		LT::LexTable lex;			// результат работы лексического анализатора
		IT::IdTable idtable;
		MFSTSTSTACK st;				//стек автомата
		use_container<std::stack <MfstState>> storestate; // стек для сохранения состояний
		Mfst();
		Mfst(LT::LexTable plex, IT::IdTable pid, GRB::Graibach pgrebach);
		//(лекс табл, грамматика Грейбах
		char* getCSt(char* buf);	//получить содержимое стека
		char* getCLenta(char* buf, short pos, short n = 25); //лента: n символов с pos
		char* getDiagnosis(short n, char* buf); //получить n-ую строки или 0х00
		bool savestate();			//сохранить состояние автомата
		bool reststate();			//восстановить состояние автомата
		bool push_chain(GRB::Rule::Chain chain); //поместить цепочку правила в стек
		RC_STEP step();				//выполнить шаг автомата
		bool start(Log::LOG log);	//запустить автомат
		bool savediagnosis(RC_STEP pprc_step); //код завершения шага
		void printrules(Log::LOG log);			//вывести последовательность правил
		struct Deducation //вывод
		{
			short size;		//количество шагов в выводе
			short* nrules;	//номера правил грамматики
			short* nrulechains; //номера цепочек правил граматики (nrules)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		} deducation;
		bool savededucation(); //сохранить дерево вывода
	};
}
