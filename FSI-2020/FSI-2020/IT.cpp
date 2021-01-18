#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <cstddef>
#include "IT.h"
#include "LT.h"
#include "Error.h"

namespace IT
{
	IdTable Create(int size)
	{
		IdTable* a = new IdTable;
		a->maxsize = size;
		a->size = 0;
		a->table = new Entry[size];
		return *a;
	}
	Entry Getentry(IdTable& idtable, int n)
	{
		return idtable.table[n];
	}
	void SetEntry(IT::IdTable& entry, int idxfirstLE, char* id, int line, IDDATATYPE iddatatype, IDTYPE idtype)
	{
		
		if (strlen(id) > 4)
			throw ERROR_THROW_IN(113, line, 0);
		char buff[5];
		if (IT::IsId(entry, id) == TI_NULLIDX || id == "_L")
		{
			strcpy_s((entry).table[entry.size].id, id);
			(entry).table[entry.size].idxfirstLE = idxfirstLE;
			(entry).table[entry.size].iddatatype = iddatatype;
			(entry).table[entry.size].idtype = idtype;
			if (id == "_L")
			{
				_itoa_s(entry.lit, buff, 10);
				strcat_s((entry).table[entry.size].id, buff);
			}
			entry.size++;
			entry.lit++;
		}
	}
	void Add(IdTable& idtable, Entry entry)
	{
		idtable.table[idtable.size++] = entry;
	}
	int IsId(IdTable& idtable, char id[ID_MAXSIZE])
	{
		int i;

		for (i = idtable.size; i >= 0; i--)
		{
			if (std::strcmp(idtable.table[i].id, id) == NULL)
			{

				return i;
			}

		}
		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable)
	{
		delete& idtable;
	}
}