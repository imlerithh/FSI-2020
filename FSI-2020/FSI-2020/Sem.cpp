#include "stdafx.h"
#include "Sem.h"
#include "Poland.h"
#include <iostream>
#include <vector>
#include <stack>
#define SIZE 100


void SEM::CheckMain(LT::LexTable lextable, IT::IdTable idtable)
{
	short m = 0;
	int i;
	for (i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == LEX_MAIN)
		{
			m++;
		}

		if (m > 1)
			throw ERROR_THROW_IN(402, lextable.table[i].sn, lextable.table[i].count);
	}
	if (m == 0)
		throw ERROR_THROW_IN(401, 0, 0);
}

void SEM::CheckId(LT::LexTable lextable, IT::IdTable idtable)
{
	
	char** str = new char*[idtable.size];
	int index = 0;
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == 'd')
		{	
			for (int j = 0; j < index; j++) {
				if (str[j] == idtable.table[lextable.table[i + 2].idxTI].id)
				{
					throw ERROR_THROW_IN(403, lextable.table[i].sn, lextable.table[i].count);
				}
			}
			str[index] = idtable.table[lextable.table[i + 2].idxTI].id;
		}
		if (lextable.table[i].lexema == 'f')
		{
			i++;
			while (lextable.table[i].lexema != ')') {
				if(lextable.table[i].lexema == 'i')
				for (int j = 0; j < index; j++) {
				if (str[j] == idtable.table[lextable.table[i].idxTI].id)
				{
					throw ERROR_THROW_IN(403, lextable.table[i].sn, lextable.table[i].count);
				}
			}
			str[index] = idtable.table[lextable.table[i ].idxTI].id;
				i++;
			}
		}
	}
}

void SEM::FirstLetterId(LT::LexTable lextable, IT::IdTable idtable)
{

	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == 'i')
		{
			char c = idtable.table[lextable.table[i].idxTI].id[0];
			if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
				throw ERROR_THROW_IN(413, lextable.table[i].sn, lextable.table[i].count);
		}
	}
}

void SEM::DivisionByZero(LT::LexTable lextable, IT::IdTable idtable)
{

	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == 'v' && lextable.table[i].operat == '%' || lextable.table[i].operat == '/')
		{
			if(lextable.table[i+1].lexema == 'l' && idtable.table[lextable.table[i+1].idxTI].value.vint == 0)
				throw ERROR_THROW_IN(410, lextable.table[i].sn, lextable.table[i].count);
		}
	}
}

void SEM::Operation(LT::LexTable lextable, IT::IdTable idtable)
{
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == 'v') {
			int k = 1;
			while (lextable.table[i - k].lexema != '=') {
				if (lextable.table[i - k].lexema == 'i' && idtable.table[lextable.table[i - k].idxTI].iddatatype != IT::IDDATATYPE::INT|| lextable.table[i - k].lexema == 'l' && idtable.table[lextable.table[i - k].idxTI].iddatatype != IT::IDDATATYPE::INT|| lextable.table[i - k].lexema == 'i' && idtable.table[lextable.table[i - k].idxTI].idtype == IT::IDTYPE::F|| lextable.table[i - k].lexema == 'q'|| lextable.table[i - k].lexema == 'y' || lextable.table[i - k].lexema == 'x')
					throw ERROR_THROW_IN(412, lextable.table[i].sn, lextable.table[i].count);
				k++;
			}
			while (lextable.table[i].lexema != ';') {
				if (lextable.table[i].lexema == 'i' && idtable.table[lextable.table[i].idxTI].iddatatype != IT::IDDATATYPE::INT || lextable.table[i].lexema == 'l' && idtable.table[lextable.table[i].idxTI].iddatatype != IT::IDDATATYPE::INT|| lextable.table[i].lexema == 'i' && idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F|| lextable.table[i].lexema == 'q' || lextable.table[i].lexema == 'y' || lextable.table[i].lexema == 'x')
					throw ERROR_THROW_IN(412, lextable.table[i].sn, lextable.table[i].count);
				i++;
			}
		}
	}
}

void SEM::Appropriation(LT::LexTable lextable, IT::IdTable idtable)
{
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == '=') {

			if (lextable.table[i + 1].lexema == 'i' && idtable.table[lextable.table[i - 1].idxTI].iddatatype != idtable.table[lextable.table[i + 1].idxTI].iddatatype|| (lextable.table[i + 1].lexema == 'l' && idtable.table[lextable.table[i - 1].idxTI].iddatatype != idtable.table[lextable.table[i + 1].idxTI].iddatatype)){
				throw ERROR_THROW_IN(411, lextable.table[i].sn, lextable.table[i].count);
			}
		else if (lextable.table[i + 1].lexema == 'q' && idtable.table[lextable.table[i - 1].idxTI].iddatatype != IT::IDDATATYPE::INT) {
			throw ERROR_THROW_IN(411, lextable.table[i].sn, lextable.table[i].count);
		}
		else if (lextable.table[i + 1].lexema == 'x' && idtable.table[lextable.table[i - 1].idxTI].iddatatype != IT::IDDATATYPE::INT)
			throw ERROR_THROW_IN(411, lextable.table[i].sn, lextable.table[i].count);
		if (lextable.table[i + 1].lexema == 'y' && idtable.table[lextable.table[i - 1].idxTI].iddatatype != IT::IDDATATYPE::INT)
			throw ERROR_THROW_IN(411, lextable.table[i].sn, lextable.table[i].count);
	}
	}
}

void SEM::LibraryParametrs(LT::LexTable lextable, IT::IdTable idtable)
{
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == 'y') {
			if (idtable.table[lextable.table[i + 2].idxTI].iddatatype != IT::IDDATATYPE::CHR)
				throw ERROR_THROW_IN(408, lextable.table[i].sn, lextable.table[i].count);
		}
		if (lextable.table[i].lexema == 'q') {
			if (idtable.table[lextable.table[i + 2].idxTI].iddatatype != IT::IDDATATYPE::INT)
				throw ERROR_THROW_IN(407, lextable.table[i].sn, lextable.table[i].count);
		}
		if (lextable.table[i].lexema == 'u') {
			if (idtable.table[lextable.table[i + 2].idxTI].iddatatype != IT::IDDATATYPE::BOO)
				throw ERROR_THROW_IN(406, lextable.table[i].sn, lextable.table[i].count);
		}
		if (lextable.table[i].lexema == 'z') {
			if (idtable.table[lextable.table[i + 2].idxTI].iddatatype != IT::IDDATATYPE::INT) {
				throw ERROR_THROW_IN(406, lextable.table[i].sn, lextable.table[i].count);
			}
			else if (idtable.table[lextable.table[i + 2].idxTI].value.vint < 0 || idtable.table[lextable.table[i + 2].idxTI].value.vint > 65535) {
				throw ERROR_THROW_IN(406, lextable.table[i].sn, lextable.table[i].count);
			}
		}
	}
}

void SEM::Vision(LT::LexTable lextable, IT::IdTable idtable)
{

	char** vision = new char*[idtable.size];
	for (int i = 0; i < idtable.size; i++) {
		vision[i] = new char[10];
		vision[i][0] = 'a';
	}
	int index = 0;
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == 'i' && idtable.table[lextable.table[i].idxTI].idtype != IT::IDTYPE::F)
		{
			if (vision[lextable.table[i].idxTI][0] == 'a') {
				vision[lextable.table[i].idxTI] = lextable.table[i].lt_vision;
			}
			else if (vision[lextable.table[i].idxTI] != lextable.table[i].lt_vision) {
				throw ERROR_THROW_IN(400, lextable.table[i].sn, lextable.table[i].count);
			}
		}
	}
}

void SEM::Parametrs(LT::LexTable lextable, IT::IdTable idtable)
{
	struct Param
	{
		int idindex;
		char name[ID_MAXSIZE];
		std::vector<int> vector;//типы параметров
		int count_p;
	};
	Param param[SIZE] = {};

	int size = 0;
	std::vector<int> buffer;
	int index;
	int help = 0;
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == LEX_FUNCTION)//нахожу функцию для записи
		{
			strcpy_s(param[size].name, idtable.table[lextable.table[i + 1].idxTI].id);
			param[size].idindex = lextable.table[i + 1].idxTI;
			i = i + 2;
			while (lextable.table[i].lexema != LEX_RIGHTHESIS)
			{
				if (lextable.table[i].idxTI != TI_NULLIDX && idtable.table[lextable.table[i].idxTI].idtype > 0 && idtable.table[lextable.table[i].idxTI].idtype < 1000)
				{
					param[size].vector.push_back(idtable.table[lextable.table[i].idxTI].iddatatype);
				}
				if (lextable.table[i].lexema == LEX_RIGHTHESIS)
					break;
				i++;
			}
			param[size].count_p = param[size].vector.size();
			size++;
		}
		if (lextable.table[i].idxTI != TI_NULLIDX && size != 0)
		{
			if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F)//запишу в буфер
			{

				index = lextable.table[i].idxTI;
				//записал в буфер вызов функции
				for (int j = 0; j < size; j++)
				{
					if (index == param[j].idindex)//запомнили индекс с вектором параметров
					{
						while (lextable.table[i].lexema != LEX_RIGHTHESIS)
						{
							i++;
							if (lextable.table[i].idxTI != TI_NULLIDX && idtable.table[lextable.table[i].idxTI].idtype > 0 && idtable.table[lextable.table[i].idxTI].idtype < 1000)
							{
								buffer.push_back(idtable.table[lextable.table[i].idxTI].iddatatype);
								help++;
							}
							//i++;
						}
						if (param[j].vector.size() != help)
							throw ERROR_THROW_IN(405, lextable.table[i].sn, lextable.table[i].count);
						help = 0;
						//проверка типов
						for (int last = 0; last < param[j].vector.size(); last++)
						{
							if (param[j].vector[last] != buffer[last])
							{
								throw ERROR_THROW_IN(409, lextable.table[i].sn, lextable.table[i].count);
							}
						}
						buffer.clear();
					}
				}
			}
		}
		/*if (lextable.table[i].lexema == LEX_IF)
		{
			while (lextable.table[i].lexema != LEX_RIGHTHESIS)
			{
				if (lextable.table[i].idxTI != TI_NULLIDX && idtable.table[lextable.table[i].idxTI].idtype > 0 && idtable.table[lextable.table[i].idxTI].idtype < 1000)
				{
					if (idtable.table[lextable.table[i].idxTI].iddatatype != IT::IDDATATYPE::BOO)
							throw ERROR_THROW_IN(406, lextable.table[i].sn, lextable.table[i].count);
				}
				i++;
			}
		}
		if (lextable.table[i].lexema == LEX_TRANSFORMATIO)
		{
			while (lextable.table[i].lexema != LEX_RIGHTHESIS)
			{
				if (lextable.table[i].idxTI != TI_NULLIDX && idtable.table[lextable.table[i].idxTI].idtype > 0 && idtable.table[lextable.table[i].idxTI].idtype < 1000)
				{
					if (idtable.table[lextable.table[i].idxTI].iddatatype != IT::IDDATATYPE::CHR)
						throw ERROR_THROW_IN(408, lextable.table[i].sn, lextable.table[i].count);
				}
				i++;
			}
		}
		if (lextable.table[i].lexema == LEX_POW)
		{
			while (lextable.table[i].lexema != LEX_RIGHTHESIS)
			{
				if (lextable.table[i].idxTI != TI_NULLIDX && idtable.table[lextable.table[i].idxTI].idtype > 0 && idtable.table[lextable.table[i].idxTI].idtype < 1000)
				{
					if (idtable.table[lextable.table[i].idxTI].iddatatype != IT::IDDATATYPE::INT )
						throw ERROR_THROW_IN(407, lextable.table[i].sn, lextable.table[i].count);
				}
				i++;
			}
		}*/
	}
}



void SEM::Poland(LT::LexTable& lextable, IT::IdTable idtable)
{
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == LEX_RAV)
		{
			Poland::PolishNotation(i, &lextable, idtable);
		}
	}
}

void SEM::Ret(LT::LexTable lextable, IT::IdTable idtable)
{
	std::stack<int> stack;
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i - 1].lexema == 'f')
		{
			stack.push(idtable.table[lextable.table[i].idxTI].iddatatype);
		}
		if (lextable.table[i].lexema == 'm')
		{
			stack.push(1);
			while (lextable.table[i - 1].lexema != 'r')
			{
				i++;
			}
			if (stack.top() == idtable.table[lextable.table[i].idxTI].iddatatype)
			{
				stack.pop();
			}
			else
			{
				throw ERROR_THROW_IN(404, lextable.table[i].sn, lextable.table[i].count);
			}
			i++;
		}
		if (lextable.table[i - 1].lexema == 'r')
		{
			if (stack.top() == idtable.table[lextable.table[i].idxTI].iddatatype)
			{
				stack.pop();
			}
			else
			{
				throw ERROR_THROW_IN(404, lextable.table[i].sn, lextable.table[i].count);
			}
		}

	}
}

void SEM::SemanticAnalyse(LT::LexTable lextable, IT::IdTable idtable)
{

	CheckMain(lextable, idtable);//входная точка 
	CheckId(lextable, idtable);//переопределение идентификаторов
	FirstLetterId(lextable, idtable);// первый символ id не цифра
	Parametrs(lextable, idtable);//кол-во параметров в функции
	Ret(lextable, idtable);//тип возвращаемого значения
	Vision(lextable, idtable); // область видимость
	Operation(lextable, idtable);//соответсвие операндов в операции
	Appropriation(lextable, idtable);//присваивание нужного типа идентификатору
	LibraryParametrs(lextable, idtable);//проверка параметров библиотечных функций и if 
	DivisionByZero(lextable, idtable); // деление на 0
	Poland(lextable, idtable);//подключение польской записи
}
