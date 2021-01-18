#include "stdafx.h"
#include "GRB.h"
#include <string.h>
#define GRB_ERROR_SERIES 600
namespace GRB
{
#define NS(n) Rule::Chain::N(n)
#define TS(n) Rule::Chain::T(n)
	Graibach greibach(NS('S'), TS('$'), //стартовый символ, дно стека
		7,                              //количество правил
		Rule(NS('S'), GRB_ERROR_SERIES,  //Неверная структура программы
			6, 
			Rule::Chain(14, TS('n'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('L'), TS(';'), TS('}'), TS(';'), NS('S')),
			
			Rule::Chain(14, TS('s'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('L'), TS(';'), TS('}'), TS(';'), NS('S')),
			
			Rule::Chain(14, TS('b'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('L'), TS(';'), TS('}'), TS(';'), NS('S')),
			
			Rule::Chain(14, TS('j'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('L'), TS(';'), TS('}'), TS(';'), NS('S')),
			
			Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('L'), TS(';'), TS('}'), TS(';')),
			
			Rule::Chain(9, TS('m'), TS('{'), NS('N'), TS('r'), NS('L'), TS(';'), TS('}'), TS(';'), NS('S'))
			
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 1, //Ошибочный оператор
			20, 
			Rule::Chain(5, TS('d'), TS('n'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('d'), TS('n'), TS('i'), TS(';')),
			
			Rule::Chain(5, TS('d'), TS('s'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('d'), TS('s'), TS('i'), TS(';')),

			Rule::Chain(5, TS('d'), TS('j'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('d'), TS('j'), TS('i'), TS(';')),

			Rule::Chain(5, TS('d'), TS('b'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('d'), TS('b'), TS('i'), TS(';')),

			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			
			Rule::Chain(8, TS('u'), TS('('), NS('L'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(9, TS('u'), TS('('), NS('L'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('N')),

			Rule::Chain(7, TS('u'), TS('('), NS('L'), TS(')'), TS('{'), TS('}'), TS(';')),
			Rule::Chain(8, TS('u'), TS('('), NS('L'), TS(')'), TS('{'), TS('}'), TS(';'), NS('N')),

			Rule::Chain(8, TS('z'), TS('('), TS('l'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(9, TS('z'), TS('('), TS('l'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('N')),

			Rule::Chain(7, TS('z'), TS('('), TS('l'), TS(')'), TS('{'),  TS('}'), TS(';')),
			Rule::Chain(8, TS('z'), TS('('), TS('l'), TS(')'), TS('{'),  TS('}'), TS(';'), NS('N')),

			Rule::Chain(4, TS('p'), NS('L'), TS(';'), NS('N')),										
			
			Rule::Chain(3, TS('p'), NS('L'), TS(';'))
			
		),
		Rule(NS('L'), GRB_ERROR_SERIES + 6,
			2,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 2, //ошибка в выражении
			12, 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			//библиотечные функции
			Rule::Chain(3, TS('x'), TS('('), TS(')')),

			Rule::Chain(4, TS('y'), TS('('), TS('i'), TS(')')),			
			Rule::Chain(4, TS('y'), TS('('), TS('l'), TS(')')),

			Rule::Chain(4, TS('q'), TS('('), TS('i'), TS(')')),
			Rule::Chain(4, TS('q'), TS('('), TS('l'), TS(')'))
			
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 3,
			4, 
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M')),
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M'))
		),
		Rule(NS('F'), GRB_ERROR_SERIES + 4,
			8,
			Rule::Chain(2, TS('n'), TS('i')),
			Rule::Chain(4, TS('n'), TS('i'), TS(','), NS('F')),

			Rule::Chain(2, TS('s'), TS('i')),
			Rule::Chain(4, TS('s'), TS('i'), TS(','), NS('F')),

			Rule::Chain(2, TS('j'), TS('i')),
			Rule::Chain(4, TS('j'), TS('i'), TS(','), NS('F')),

			Rule::Chain(2, TS('b'), TS('i')),
			Rule::Chain(4, TS('b'), TS('i'), TS(','), NS('F'))
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 5,
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		)
	);
	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
	{
		nt = new GRBALPHABET[size = psize];
		int* p = (int*)&s;
		for (short i = 0; i < psize; ++i) nt[i] = (GRBALPHABET)p[i];
	}
	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < size; i++) b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	};
	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...)
	{
		nn = pnn;
		iderror = piderror;
		chains = new Chain[size = psize];
		Chain* p = &c;
		for (int i = 0; i < size; i++) chains[i] = p[i];
	}
	char* Rule::getCRule(char* b, short nchain)
	{
		char bchain[200];
		b[0] = Chain::alphabet_to_char(nn);
		b[1] = '-'; b[2] = '>'; b[3] = 0x00;
		chains[nchain].getCChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain);
		return b;
	}
	short Rule::getNChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;
		while (j < size && chains[j].nt[0] != t)
			++j;
		rc = (j < size ? j : -1);
		if (rc >= 0) pchain = chains[rc];
		return rc;
	};
	Graibach::Graibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...)
	{
		startN = pstartN;
		stbottomT = pstbottomT;
		rules = new Rule[size = psize];
		Rule* p = &r;
		for (int i = 0; i < size; i++) rules[i] = p[i];
	}
	short Graibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1;
		short k = 0;
		while (k < size && rules[k].nn != pnn) k++;
		if (k < size) prule = rules[rc = k];
		return rc;
	}
	Rule Graibach::getRule(short n)
	{
		Rule rc;
		if (n < size) rc = rules[n];
		return rc;
	};
	Graibach getGreibach()
	{
		return greibach;
	};
}