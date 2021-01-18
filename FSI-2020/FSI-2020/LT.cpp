#include "stdafx.h"
#include "LT.h"

namespace LT
{
	LexTable Create(int size)
	{
		LexTable* a = new LexTable;
		a->maxsize = size;
		a->size = 0;
		a->table = new Entry[size];
		return *a;
	}

	void Add(LexTable& lextable, Entry entry)
	{
		lextable.table[lextable.size++] = entry;
	}

	Entry Getentry(LexTable& lextable, int n)
	{
		return lextable.table[n];
	}
	void SetEntry(LT::LexTable* entry, unsigned char lexema, int indx, int line, int count, char* vision, char operat)
	{
		(*entry).table[(*entry).size].lexema = lexema;
		(*entry).table[(*entry).size].idxTI = indx;
		(*entry).table[(*entry).size].sn = line;
		(*entry).table[(*entry).size].count = count;
		(*entry).table[(*entry).size].lt_vision = vision;
		(*entry).table[(*entry).size].operat = operat;
		(*entry).size++;
	}
	void Delete(LexTable& lextable)
	{
		delete& lextable;
	}
}