#pragma once
#include "Error.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
typedef short GRBALPHABET; //������� �������� ��������� ��������� >0, �����������<0
namespace GRB
{
	struct Rule //������� � ��������� �������
	{
		GRBALPHABET nn;     //���������� (����� ������ �������) <0
		int iderror;        //������������� ���������������� ��������� 
		short size;			//���������� �������-������ ������ �������
		struct Chain  //������� (������ ����� �������)
		{
			short size;     //����� �������
			GRBALPHABET* nt;	//������� ����������(>0) � ������������ (<0)
			Chain() { size = 0; nt = 0; };
			Chain(short psize, GRBALPHABET s, ...); //(���. ����., ����.(���� � ������))
			char* getCChain(char* b);  // �������� ������ ������ �������
			static GRBALPHABET T(char t) { return GRBALPHABET(t); }; //��������
			static GRBALPHABET N(char n) { return -GRBALPHABET(n); }; //�� ��������
			static bool isT(GRBALPHABET s) { return s > 0; }; //��������?
			static bool isN(GRBALPHABET s) { return s < 0; }; //����������?
			static char alphabet_to_char(GRBALPHABET s) { return isT(s) ? char(s) : char(-s); }; //GRBALPHABET->char
		}*chains;
		Rule() { nn = 0x00; size = 0; };
		Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...);
		//(����������, ������������� ���������������� ���������, ���.�������-������ ������ �������, ��������� �������-������ ������ �������)
		char* getCRule(char* b, short nchain);
		//�������� ������� � ���� N->������� (��� ����������)(�����, ������������(������ �����) � �������
		short getNChain(GRBALPHABET t, Rule::Chain& pchain, short j);
		//�������� ��������� �� j ���������� �������, ������� � ����� ��� -1 (������ ������ �������, ������������ �������, ����� �������)
	};
	struct Graibach //���������� �������
	{
		short size; //���������� ������
		GRBALPHABET startN;  //��������� ������
		GRBALPHABET stbottomT; //��� �����
		Rule* rules; //��������� ������
		Graibach() { short size = 0; startN = 0; stbottomT = 0; rules = 0; };
		Graibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...);
		//(��������� ������, ��� �����, ���������� ������, �������)
		short getRule(GRBALPHABET pnn, Rule& prule);
		//�������� �������, ������������ ����� ������� ��� -1(����� ������ �������, �������.������� ����������)
		Rule getRule(short n); // �������� ������� �� ������
	};
	Graibach getGreibach(); //�������� ��������� 
};
