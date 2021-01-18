#include "stdafx.h"
#include "Tables.h"

void tablesOut(LT::LexTable  lextable, IT::IdTable  idTable)
{
	std::ofstream fout;
	fout.open("../Debug/Tables.txt");
	if (!fout.is_open())
	{

	}
	else
	{

		fout << "\tÒÀÁËÈÖÀ ËÅÊÑÅÌ\n";
		fout << "\n";
		fout << "  Ñòðîêà | Ëåêñåìà | id â idtable |     Îáëàñòü\n";
		fout << "\n";
		for (int i = 0; i < lextable.size; i++)
		{
			fout << "\t" << lextable.table[i].sn << " \t" << lextable.table[i].lexema << " \t";
			if (lextable.table[i].idxTI == -1)
				fout << "\t\t" << lextable.table[i].lt_vision;
			else
				fout << lextable.table[i].idxTI << "\t\t" << lextable.table[i].lt_vision;

			fout << "\n";
		}
		fout << "\n";
		fout << "\tÒÀÁËÈÖÀ ÈÄÅÍÒÈÔÈÊÀÒÎÐÎÂ\n";
		fout << " \n";
		fout << "  Èíäåêñ | Èäåíòèôèêàòîð |             Òèï             | Çíà÷åíèå\n";
		fout << "\n";
		for (int i = 0; i < idTable.size; i++)
		{
			fout << "\t" << idTable.table[i].idxfirstLE << " \t" << idTable.table[i].id << " \t\t";

			if (idTable.table[i].idtype == IT::IDTYPE::F)
			{
				fout << "F " << "\t";
			}
			else if (idTable.table[i].idtype == IT::IDTYPE::P)
			{
				fout << "P " << "\t";
			}
			else if (idTable.table[i].idtype == IT::IDTYPE::V)
			{
				fout << "V " << "\t";
			}
			else if (idTable.table[i].idtype == IT::IDTYPE::L)
			{
				fout << "L " << "\t";
			}
			if (idTable.table[i].iddatatype == IT::IDDATATYPE::INT)
			{
				fout << "totum " << "\t\t" << idTable.table[i].value.vint;
			}
			else if (idTable.table[i].iddatatype == IT::IDDATATYPE::STR)
			{
				fout << "chorda " << "\t\t"; 
				if (strlen(idTable.table[i].value.vstr->str) <= 0) {
					fout << '\"';
					fout << idTable.table[i].value.vstr->str;
					fout << '\"';
				}
				else fout << idTable.table[i].value.vstr->str;
			}
			else if (idTable.table[i].iddatatype == IT::IDDATATYPE::BOO)
			{
				fout << "logicus " << "\t";
				if (idTable.table[i].value.vbool == 0) fout << "falsus";
				else fout << "verum";
			}
			else if (idTable.table[i].iddatatype == IT::IDDATATYPE::CHR)
			{
				fout << "signum " << "\t\t" << idTable.table[i].value.vchar;
			}
			fout << "\n";
		}

	}
	fout.close();

}
