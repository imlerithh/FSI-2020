#pragma once
#include "Error.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
typedef short GRBALPHABET; //символы алфавита граматики терминалы >0, нетерминалы<0
namespace GRB
{
	struct Rule //правило в граматике Грейбах
	{
		GRBALPHABET nn;     //нетерминал (левый символ правила) <0
		int iderror;        //идентификатор диагностического сообщения 
		short size;			//количество цепочек-правых частей правила
		struct Chain  //цепочка (правая часть правила)
		{
			short size;     //длина цепочки
			GRBALPHABET* nt;	//цепочка терминалов(>0) и нетерминалов (<0)
			Chain() { size = 0; nt = 0; };
			Chain(short psize, GRBALPHABET s, ...); //(кол. симв., симв.(терм и нетерм))
			char* getCChain(char* b);  // получить правую строку правила
			static GRBALPHABET T(char t) { return GRBALPHABET(t); }; //терминал
			static GRBALPHABET N(char n) { return -GRBALPHABET(n); }; //не терминал
			static bool isT(GRBALPHABET s) { return s > 0; }; //терминал?
			static bool isN(GRBALPHABET s) { return s < 0; }; //нетерминал?
			static char alphabet_to_char(GRBALPHABET s) { return isT(s) ? char(s) : char(-s); }; //GRBALPHABET->char
		}*chains;
		Rule() { nn = 0x00; size = 0; };
		Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...);
		//(нетерминал, идентификатор диагностического сообщения, кол.цепочек-правых частей правила, множество цепочек-правых частей правила)
		char* getCRule(char* b, short nchain);
		//получить правило в виде N->цепочка (для паспечатки)(буфер, номерцепочки(правой части) в правиле
		short getNChain(GRBALPHABET t, Rule::Chain& pchain, short j);
		//получить следующую за j подходящую цепочку, вернуть её номер или -1 (первый символ цепочки, возвращаемая цепочка, номер цепочки)
	};
	struct Graibach //грамматика Грейбах
	{
		short size; //количество правил
		GRBALPHABET startN;  //стартовый символ
		GRBALPHABET stbottomT; //дно стека
		Rule* rules; //множество правил
		Graibach() { short size = 0; startN = 0; stbottomT = 0; rules = 0; };
		Graibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...);
		//(стартовый символ, дно стека, количество правил, правило)
		short getRule(GRBALPHABET pnn, Rule& prule);
		//получить правило, возвращается номер правила или -1(левый символ правила, возвращ.правило грамматики)
		Rule getRule(short n); // получить правило по номеру
	};
	Graibach getGreibach(); //получить граматику 
};
