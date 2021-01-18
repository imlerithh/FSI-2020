#pragma once
#include "IT.h"
#include "LT.h"
#include "Error.h"
#include <string.h>

namespace SEM
{
	void Poland(LT::LexTable& lextable, IT::IdTable idtable);
	void CheckType(LT::LexTable lextable, IT::IdTable idtable);
	void Ret(LT::LexTable lextable, IT::IdTable idtable);
	void Parametrs(LT::LexTable lextable, IT::IdTable idtable);
	void CheckMain(LT::LexTable lextable, IT::IdTable idtable);
	void CheckId(LT::LexTable lextable, IT::IdTable idtable);
	void SemanticAnalyse(LT::LexTable lextable, IT::IdTable idtable);
	void Vision(LT::LexTable lextable, IT::IdTable idtable);
	void Operation(LT::LexTable lextable, IT::IdTable idtable);
	void Appropriation(LT::LexTable lextable, IT::IdTable idtable);
	void LibraryParametrs(LT::LexTable lextable, IT::IdTable idtable);
	void FirstLetterId(LT::LexTable lextable, IT::IdTable idtable);
	void DivisionByZero(LT::LexTable lextable, IT::IdTable idtable);
}
