#pragma once

#include "In.h"
#include "Log.h"
#include "Machine.h"
#include "LT.h"
#include "IT.h"

#define CF(x,n) del.clear_text[n]!=x? true:false
#define CF_M(x,n) del.clear_text[n-1]!=x? true:false
#define CF_P(x,n) del.clear_text[n+1]!=x? true:false

#define CT(x,n) del.clear_text[n]==x? true:false
#define CT_M(x,n) del.clear_text[n-1]==x? true:false
#define CT_P(x,n) del.clear_text[n+1]==x? true:false

#define STR(n) del.clear_text[n]

namespace LEX
{
	struct DEL
	{
		int deleted = 0; //���������� �������� ��������
		unsigned char clear_text[1024];//��� ����� ������
		int stroki = 0;//���-�� ����
		int cols = 0;//������������ ����� �����
		int* arr;//����� ���� ����
		char** main_array;//������ �� ����� �������
	};
	DEL check(Log::LOG log, In::IN in, LT::LexTable* lextable, IT::IdTable* idTable);
	void typeId(LT::LexTable* lexTable, IT::IdTable* idTable, char id[TI_STR_MAXSIZE], int number);
	int OCT_TO_DEC(char* st);
	int BIN_TO_DEC(char* st);
	char** divideText(unsigned char source[], int size, int max_word, int size_word);
	void clearSpace(unsigned char source[], int size);
}
