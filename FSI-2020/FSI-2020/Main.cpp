#include "stdafx.h"
#include <iostream>
#include <locale>
#include <cwchar>

#include "Parm.h"
#include "Error.h"
#include "In.h"
#include "Log.h"
#include "Lex.h"
#include "Poland.h"
#include "Tables.h"
#include "GRB.h"
#include "MFST.h"
#include "Sem.h"
#include "Gen.h"

int _tmain(int argc, _TCHAR** argv)
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;

	LEX::DEL del;
	try
	{
		LT::LexTable lextable = LT::Create(LT_MAXSIZE);
		IT::IdTable idTable = IT::Create(TI_MAXSIZE);
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, L"Тест", L" Без ошибок", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		del = LEX::check(log, in, &lextable, &idTable); //LEX
		*log.stream << "\n[LEX] Лексический анализ выполнен без ошибок\n";
		
		MFST_TRACE_START;
		MFST::Mfst mfst(lextable, idTable, GRB::getGreibach());
		mfst.start(log);
		mfst.savededucation();
		mfst.printrules(log);

		SEM::SemanticAnalyse(lextable, idTable);
		*log.stream << "[SEM] Семантический анализ выполнен без ошибок\n\n[GEN] Переход к генерации кода\n";
		tablesOut(lextable, idTable);
		Gen::Gen(lextable, idTable);
		Log::Close(log);
		system("pause");
	}
	catch (Error::ERROR e)
	{
		if(e.id!=606)
		Log::WriteError(log, e);
		cout << "\nВыявлена ошибка. Подробная информация в файле протокола (-log).";
	}
	return 0;
}

