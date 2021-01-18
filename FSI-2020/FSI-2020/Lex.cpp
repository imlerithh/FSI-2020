#include "stdafx.h"
#include "Lex.h"
#include <fstream>
#include <string>
#include <stack>

std::stack<char*> stack;
namespace LEX
{
	//LEX::DEL id(LEX::DEL del, LT::Entry lt, IT::Entry id, LT::LexTable lextable, IT::IdTable idTable, int i, int number)
	LEX::DEL check(Log::LOG log, In::IN in, LT::LexTable* lextable, IT::IdTable* idTable)
	{

		//провер€ю на двойные пробелы, табул€ции, переходы строк, если есть удал€ю их
		LEX::DEL del;
		int i = 0;
		int m = 0;//i дл€ старого, m дл€ исправленного текста

		
		if (in.text[0] == ' ' || in.text[0] == '\t' || in.text[0] == '\n')
		{
			do
			{
				i++;
				del.deleted++;
			} while (in.text[i] <= 48 && in.text[i] >= 122);
		}

		for (m; m < in.size; m)
		{
			//двойные
			if ((in.text[i] == ' ' && in.text[i + 1] == ' ') || (in.text[i] == ' ' && in.text[i + 1] == '\t')
				|| (in.text[i] == '\t' && in.text[i + 1] == ' ') || (in.text[i] == '\t' && in.text[i + 1] == '\t')
				|| (in.text[i] == ' ' && in.text[i + 1] == '\n') || (in.text[i] == '\t' && in.text[i + 1] == '\n')
				|| (in.text[i] == '\n' && in.text[i + 1] == '\n'))
			{
				do
				{
					i++;
					del.deleted++;
				} while (in.text[i] <= 48 && in.text[i] >= 122);
			}

			else
			{
				del.clear_text[m] = in.text[i];
				m++;
				i++;
			}
		}
		*log.stream << "”даленные символы:   " << del.deleted << std::endl;
		std::cout << del.clear_text;
		// подсчет слов входной строки.
		for (int i = 0; i <= strlen((char*)del.clear_text); i++)
		{
			if (STR(i) == '>' || STR(i) == '<' || STR(i) == '+' || STR(i) == '-' || STR(i) == '*' || STR(i) == '/' || STR(i) == '(' || STR(i) == ')' || STR(i) == '{' || STR(i) == '}' || STR(i) == ',' || STR(i) == ';' || STR(i) == '+' || STR(i) == '=' || STR(i) == '\n')
			{
				if (STR(i - 1) != '>' || STR(i - 1) != '<' || STR(i - 1) != '+' && STR(i - 1) != '-' && STR(i - 1) != '*' && STR(i - 1) != '/' && STR(i - 1) != '(' && STR(i - 1) != ')' && STR(i - 1) != '{' && STR(i - 1) != '}' && STR(i - 1) != ',' && STR(i - 1) != ' ' && STR(i - 1) != '\n' && STR(i - 1) != ';' && STR(i - 1) != '=')
					del.stroki += 2;
				else del.stroki++;
			}

			else if ((STR(i) == ' ' || STR(i) == '\n') && STR(i + 1) != '\0')
			{
				if (STR(i - 1) != '>' || STR(i - 1) != '<' || STR(i - 1) != '+' && STR(i - 1) != '-' && STR(i - 1) != '*' && STR(i - 1) != '/' && STR(i - 1) != '(' && STR(i - 1) != ')' && STR(i - 1) != '{' && STR(i - 1) != '}' && STR(i - 1) != ',' && STR(i - 1) != ' ' && STR(i - 1) != '\n' && STR(i - 1) != ';' && STR(i - 1) != '=')
					del.stroki += 1;
			}
			else if (STR(i) == '\"') {
				del.stroki++;
				while (STR(i) != '\"') i++;
			}
			else if (STR(i) == '\'') {
				del.stroki++;
				while (STR(i) != '\'') i++;
			}
			//else if (del.clear_text[x] == '#')
			//{
			//	del.stroki++;
			//	do
			//	{
			//		x++;
			//	}
			//	while (del.clear_text[x] != ';' && del.clear_text[x]!=' ');
			//}
			else if (STR(i) == '\0') {
				if (STR(i - 1) != '>' || STR(i - 1) != '<' || STR(i - 1) != '+' && STR(i - 1) != '-' && STR(i - 1) != '*' && STR(i - 1) != '/' && STR(i - 1) != '(' && STR(i - 1) != ')' && STR(i - 1) != '{' && STR(i - 1) != '}' && STR(i - 1) != ',' && STR(i - 1) != ' ' && STR(i - 1) != ';' && STR(i - 1) != '=')
				{
					del.stroki += 1;
				}
				break;
			}
		}

		*log.stream << "\n¬ходной файл после преобразовани€:\n" << del.clear_text << std::endl;

		del.main_array = divideText(del.clear_text, in.size-del.deleted, del.stroki, 300);

		std::cout <<  "----------—Ћќ¬ј----------" << std::endl;
		for (int i = 0; i < del.stroki; i++) {
			if (del.main_array[i][0] == '\n')
				std::cout << "\\n" << std::endl;
			else
			std::cout << del.main_array[i] << std::endl;
			if (del.main_array[i][0] == '\0') break;
		}
		int number = 1;//номер строки
		int count_lt = 0;//подсчет литералов

	
		char* vision = new char[7];//обл видимости по умолчанию
		vision[0] = 'g';  vision[1] = 'l'; vision[2] = 'o'; vision[3] = 'b'; vision[4] = 'a'; vision[5] = 'l'; vision[6] = '\0';
		
		stack.push(vision);
		int position = 1;
		LT::Entry lt;
		IT::Entry id;
		*log.stream << "----------Ћ≈ —≈ћџ----------" << std::endl;
		std::cout << "----------Ћ≈ —≈ћџ----------" << std::endl;
		for (int i = 0; i < del.stroki; i++)//пробегают все слова
		{
			switch (del.main_array[i][0])
			{

			case '\"':
			{
				if (strlen(del.main_array[i]) >= 50) {
					throw ERROR_THROW_IN(117, (*lextable).table[(*lextable).size - 1].sn, position);
				}
				else if ((strlen(del.main_array[i]) <= 2)) {
					throw ERROR_THROW_IN(118, (*lextable).table[(*lextable).size - 1].sn, position);
				}
				FST::FST fst2(del.main_array[i], LITERAL_STR);
				if (FST::execute(fst2))
				{
					std::cout << "l ";
					*log.stream << "l ";
					LT::SetEntry(&*lextable, LEX_LITERAL, (*idTable).size, number, position, stack.top(), 'l');
					IT::SetEntry(*idTable, (*idTable).size, (char*)"_L", number, IT::IDDATATYPE::STR, IT::IDTYPE::L);
					strcpy_s((*idTable).table[(*idTable).size - 1].value.vstr->str, del.main_array[i]);
					break;
				}
			}
			case '\'':
			{
				FST::FST fst2(del.main_array[i], LITERAL_CHAR);
				if (strlen(del.main_array[i]) >= 4) {
					throw ERROR_THROW_IN(117, (*lextable).table[(*lextable).size - 1].sn, position);
				}
				else if ((strlen(del.main_array[i]) <= 2)) {
					throw ERROR_THROW_IN(118, (*lextable).table[(*lextable).size - 1].sn, position);
				}
				if (FST::execute(fst2))
				{
					std::cout << "l ";
					*log.stream << "l ";
					LT::SetEntry(&*lextable, LEX_LITERAL, (*idTable).size, number, position, stack.top(), 'l');
					IT::SetEntry(*idTable, (*idTable).size, (char*)"_L", number, IT::IDDATATYPE::CHR, IT::IDTYPE::L);
					strcpy_s((*idTable).table[(*idTable).size - 1].value.vchar, del.main_array[i]);
					break;
				}


			}
			case 'a': 
			{
				FST::FST fst(del.main_array[i], DECLARE);
				if (FST::execute(fst))
				{
					std::cout << "d ";
					*log.stream << "d ";
					LT::SetEntry(&*lextable, LEX_DECLARE, LT_TI_NULLIDX, number, position, stack.top(), 'd');
				}
				else
				{
					std::cout << "i ";
					*log.stream << "i ";
					LT::SetEntry(&*lextable, LEX_ID, IT::IsId(*idTable, del.main_array[i]), number, position, stack.top(), 'i');
					IT::SetEntry(*idTable, (*idTable).size, del.main_array[i], number, IT::IDDATATYPE::NON, IT::IDTYPE::N);
					typeId(&*lextable, &*idTable, del.main_array[i], number);
				}
				break;
			}
			case 'c':
			{
				FST::FST fst(del.main_array[i], IF);
				FST::FST fst2(del.main_array[i], STRING);
				if (FST::execute(fst))
				{
					std::cout << "u ";
					*log.stream << "u ";
					LT::SetEntry(&*lextable, LEX_IF, LT_TI_NULLIDX, number, position, stack.top(), 'u');
					stack.push(stack.top());
				}
				else
				{
					if (FST::execute(fst2))
					{
						std::cout << "t ";
						*log.stream << "t ";
						LT::SetEntry(&*lextable, LEX_STRING, LT_TI_NULLIDX, number, position, stack.top(), 's');
					}
					else
					{
						std::cout << "i ";
						*log.stream << "i ";
						LT::SetEntry(&*lextable, LEX_ID, IT::IsId(*idTable, del.main_array[i]), number, position, stack.top(), 'i');
						IT::SetEntry(*idTable, (*idTable).size, del.main_array[i], number, IT::IDDATATYPE::NON, IT::IDTYPE::N);
						typeId(&*lextable, &*idTable, del.main_array[i], number);
					}

				}
				break;
			}
			case 'f':
			{
				FST::FST fst(del.main_array[i], FALSE);
				if (FST::execute(fst))
				{
					std::cout << "l ";
					*log.stream << "l ";
					LT::SetEntry(&*lextable, LEX_LITERAL, (*idTable).size, number, position, stack.top(), 'l');
					IT::SetEntry(*idTable, (*idTable).size, (char*)"_L", number, IT::IDDATATYPE::BOO, IT::IDTYPE::L);
					(*idTable).table[(*idTable).size - 1].value.vbool = 0;
				}
				else
				{
					std::cout << "i ";
					*log.stream << "i ";
					LT::SetEntry(&*lextable, LEX_ID, IT::IsId(*idTable, del.main_array[i]), number, position, stack.top(), 'i');
					IT::SetEntry(*idTable, (*idTable).size, del.main_array[i], number, IT::IDDATATYPE::NON, IT::IDTYPE::N);
					typeId(&*lextable, &*idTable, del.main_array[i], number);
				}
				break;
			}
			case 'l':
			{
				FST::FST fst(del.main_array[i], PRINT);
				FST::FST fst2(del.main_array[i], BOOL);
				if (FST::execute(fst))
				{
					std::cout << "p ";
					*log.stream << "p ";
					LT::SetEntry(&*lextable, LEX_PRINT, IT::IsId(*idTable, del.main_array[i]), number, position, stack.top(), 'p');
				}
				else if (FST::execute(fst2))
				{
					std::cout << "t ";
					*log.stream << "t ";
					LT::SetEntry(&*lextable, LEX_BOOL, LT_TI_NULLIDX, number, position, stack.top(), 't');
				}
				else
				{
					std::cout << "i ";
					*log.stream << "i ";
					LT::SetEntry(&*lextable, LEX_ID, IT::IsId(*idTable, del.main_array[i]), number, position, stack.top(), 'i');
					IT::SetEntry(*idTable, (*idTable).size, del.main_array[i], number, IT::IDDATATYPE::NON, IT::IDTYPE::N);
					typeId(&*lextable, &*idTable, del.main_array[i], number);
				}
				break;
			}
			case 'm':
			{
				FST::FST fst(del.main_array[i], FUNCTION);
				if (FST::execute(fst))
				{
					std::cout << "f ";
					*log.stream << "f ";
					LT::SetEntry(&*lextable, LEX_FUNCTION, LT_TI_NULLIDX, number, position, stack.top(), 'f');
				}
				else
				{
					std::cout << "i ";
					*log.stream << "i ";
					LT::SetEntry(&*lextable, LEX_ID, IT::IsId(*idTable, del.main_array[i]), number, position, stack.top(), 'i');
					IT::SetEntry(*idTable, (*idTable).size, del.main_array[i], number, IT::IDDATATYPE::NON, IT::IDTYPE::N);
					typeId(&*lextable, &*idTable, del.main_array[i], number);
				}
				break;
			}
			case 'p':
			{
				FST::FST fst(del.main_array[i], MAIN);

				if (FST::execute(fst))
				{
					std::cout << "m ";
					*log.stream << "m ";
					LT::SetEntry(&*lextable, LEX_MAIN, IT::IsId(*idTable, del.main_array[i]), number, position, stack.top(), 'm');
					stack.push(del.main_array[i]);
				}
				else
				{
					std::cout << "i ";
					*log.stream << "i ";
					LT::SetEntry(&*lextable, LEX_ID, IT::IsId(*idTable, del.main_array[i]), number, position, stack.top(), 'i');
					IT::SetEntry(*idTable, (*idTable).size, del.main_array[i], number, IT::IDDATATYPE::NON, IT::IDTYPE::N);
					typeId(&*lextable, &*idTable, del.main_array[i], number);
				}

				break;
			}
			case 'q':
			{
				FST::FST fst(del.main_array[i], POW);

				if (FST::execute(fst))
				{
					std::cout << "q ";
					*log.stream << "q ";
					LT::SetEntry(&*lextable, LEX_POW, IT::IsId(*idTable, del.main_array[i]), number, position, stack.top(), 'q');
				}
				else
				{
					std::cout << "i ";
					*log.stream << "i ";
					LT::SetEntry(&*lextable, LEX_ID, IT::IsId(*idTable, del.main_array[i]), number, position, stack.top(), 'i');
					IT::SetEntry(*idTable, (*idTable).size, del.main_array[i], number, IT::IDDATATYPE::NON, IT::IDTYPE::N);
					typeId(&*lextable, &*idTable, del.main_array[i], number);
				}
				break;
			}
			case 'r':
			{
				FST::FST fst(del.main_array[i], RETURN);
				FST::FST fst2(del.main_array[i], FOR);
				FST::FST fst3(del.main_array[i], RANDOMNESS);
				if (FST::execute(fst))
				{
					std::cout << "r ";
					*log.stream << "r ";
					LT::SetEntry(&*lextable, LEX_RETURN, LT_TI_NULLIDX, number, position, stack.top(), 'r');
				}
				else if (FST::execute(fst2))
				{
					std::cout << "z ";
					*log.stream << "z ";
					LT::SetEntry(&*lextable, LEX_FOR, LT_TI_NULLIDX, number, position, stack.top(), 'z');
					stack.push(stack.top());
				}
				else if (FST::execute(fst3)) {
					std::cout << "x ";
					*log.stream << "x ";
					LT::SetEntry(&*lextable, LEX_RANDOMNESS, LT_TI_NULLIDX, number, position, stack.top(), 'x');
				}
				else
				{
					std::cout << "i ";
					*log.stream << "i ";
					LT::SetEntry(&*lextable, LEX_ID, IT::IsId(*idTable, del.main_array[i]), number, position, stack.top(), 'i');
					IT::SetEntry(*idTable, (*idTable).size, del.main_array[i], number, IT::IDDATATYPE::NON, IT::IDTYPE::N);
					typeId(&*lextable, &*idTable, del.main_array[i], number);
				}
				break;
			}
			case 's':
			{
				FST::FST fst(del.main_array[i], CHAR);
				if (FST::execute(fst))
				{
					std::cout << "j ";
					*log.stream << "j ";
					LT::SetEntry(&*lextable, LEX_CHAR, LT_TI_NULLIDX, number, position, stack.top(), 'j');
				}
				else
				{
					std::cout << "i ";
					*log.stream << "i ";
					LT::SetEntry(&*lextable, LEX_ID, IT::IsId(*idTable, del.main_array[i]), number, position, stack.top(), 'i');
					IT::SetEntry(*idTable, (*idTable).size, del.main_array[i], number, IT::IDDATATYPE::NON, IT::IDTYPE::N);
					typeId(&*lextable, &*idTable, del.main_array[i], number);
				}
				break;
			}
			case 't':
			{
				
				FST::FST fst(del.main_array[i], INTEGER);
				FST::FST fst2(del.main_array[i], TRANSFORMATIO);
				if (FST::execute(fst))
				{
						std::cout << "t ";
						*log.stream << "t ";
						LT::SetEntry(&*lextable, LEX_INTEGER, LT_TI_NULLIDX, number, position, stack.top(), 'n');
				}
				else if (FST::execute(fst2)) {
						std::cout << "y ";
						*log.stream << "y ";
						LT::SetEntry(&*lextable, LEX_TRANSFORMATIO, LT_TI_NULLIDX, number, position, stack.top(), 'y');
				}
				else
				{
						std::cout << "i ";
						*log.stream << "i ";
						LT::SetEntry(&*lextable, LEX_ID, IT::IsId(*idTable, del.main_array[i]), number, position, stack.top(), 'd');
						IT::SetEntry(*idTable, (*idTable).size, del.main_array[i], number, IT::IDDATATYPE::NON, IT::IDTYPE::N);
						typeId(&*lextable, &*idTable, del.main_array[i], number);
				}
				break;
			}
			case 'v':
			{
				FST::FST fst(del.main_array[i], TRUE);
				if (FST::execute(fst))
				{
					std::cout << "l ";
					*log.stream << "l ";
					LT::SetEntry(&*lextable, LEX_LITERAL, (*idTable).size, number, position, stack.top(), 'l');
					IT::SetEntry(*idTable, (*idTable).size, (char*)"_L", number, IT::IDDATATYPE::BOO, IT::IDTYPE::L);
					(*idTable).table[(*idTable).size - 1].value.vbool = 1;
					
				}
				else
				{
					std::cout << "i ";
					*log.stream << "i ";
					LT::SetEntry(&*lextable, LEX_ID, IT::IsId(*idTable, del.main_array[i]), number, position, stack.top(), 'd');
					IT::SetEntry(*idTable, (*idTable).size, del.main_array[i], number, IT::IDDATATYPE::NON, IT::IDTYPE::N);
					typeId(&*lextable, &*idTable, del.main_array[i], number);
				}
				break;
			}
		

			case ';':
			{
				FST::FST fst(del.main_array[i], SEMICOLON);
				if (FST::execute(fst))
				{
					std::cout << "; ";
					*log.stream << "; ";
					LT::SetEntry(&*lextable, LEX_SEMICOLON, LT_TI_NULLIDX, number, position, stack.top(), ';');
				}
				break;
			}
			case ',':
			{
				FST::FST fst(del.main_array[i], COMMA);
				if (FST::execute(fst))
				{
					std::cout << ", ";
					*log.stream << ", ";
					LT::SetEntry(&*lextable, LEX_COMMA, LT_TI_NULLIDX, number, position, stack.top(), ',');
				}
				break;
			}
			case '(':
			{
				FST::FST fst(del.main_array[i], LEFTTHESIS);
				if (FST::execute(fst))
				{
					std::cout << "( ";
					*log.stream << "( ";
					LT::SetEntry(&*lextable, LEX_LEFTHESIS, LT_TI_NULLIDX, number, position, stack.top(), '(');
				}
				break;
			}
			case ')':
			{
				std::cout << ") ";
				*log.stream << ") ";
				FST::FST fst(del.main_array[i], RIGHTTHESIS);
				if (FST::execute(fst))
				{
					LT::SetEntry(&*lextable, LEX_RIGHTHESIS, LT_TI_NULLIDX, number, position, stack.top(), ')');
				}
				break;
			}
			case '{':
			{
				FST::FST fst(del.main_array[i], LEFTBRACE);
				if (FST::execute(fst))
				{
					std::cout << "{ ";
					*log.stream << "{ ";
					LT::SetEntry(&*lextable, LEX_LEFTBRACE, LT_TI_NULLIDX, number, position, stack.top(), '{');
				}
				break;
			}
			case '}':
			{
				FST::FST fst(del.main_array[i], BRACELET);
				if (FST::execute(fst))
				{
					std::cout << "} ";
					*log.stream << "} ";
					LT::SetEntry(&*lextable, LEX_BRACELET, LT_TI_NULLIDX, number, position, stack.top(), '}');
					stack.pop();
					if (stack.empty())
						throw ERROR_THROW_IN(116, 0, 0);
				}

				break;
			}
			case '+':
			{
				FST::FST fst(del.main_array[i], PLUS);
				if (FST::execute(fst))
				{
					std::cout << "+ ";
					*log.stream << "+ ";
					LT::SetEntry(&*lextable, LEX_PLUS, LT_TI_NULLIDX, number, position, stack.top(), '+');	
				}
				
				break;
			}
			case '-':
			{
				FST::FST fst(del.main_array[i], MINUS);
				if (FST::execute(fst))
				{
					std::cout << "- ";
					*log.stream << "- ";
					LT::SetEntry(&*lextable, LEX_MINUS, LT_TI_NULLIDX, number, position, stack.top(), '-');
				}
				break;
			}
			case '*':
			{
				FST::FST fst(del.main_array[i], STAR);
				if (FST::execute(fst))
				{
					std::cout << "* ";
					*log.stream << "* ";
					LT::SetEntry(&*lextable, LEX_STAR, LT_TI_NULLIDX, number, position, stack.top(), '*');
				}
				break;
			}
			case '/':
			{
				FST::FST fst(del.main_array[i], DIRSLASH);
				if (FST::execute(fst))
				{
					std::cout << "/ ";
					*log.stream << "/ ";
					LT::SetEntry(&*lextable, LEX_DIRSLASH, LT_TI_NULLIDX, number, position, stack.top(), '/');
				}
				break;
			}
			case '%':
			{
				FST::FST fst(del.main_array[i], MODULE);
				if (FST::execute(fst))
				{
					std::cout << "% ";
					*log.stream << "% ";
					LT::SetEntry(&*lextable, LEX_MODULE, LT_TI_NULLIDX, number, position, stack.top(), '%');
				}
				break;
			}
			case '=':
			{
				FST::FST fst(del.main_array[i], RAVNO);
				if (FST::execute(fst))
				{
					std::cout << "= ";
					*log.stream << "= ";
					LT::SetEntry(&*lextable, LEX_RAV, LT_TI_NULLIDX, number, position, stack.top(), '=');
				}
				break;
			}
			case '\n':
			{
				std::cout << "\n";
				*log.stream << "\n ";
				number++;
				position = 0;
				break;
			}
			case '\0':
			{
				break;
			}
			default://в область - idx предыдущего  
			{
				FST::FST fst(del.main_array[i], X2);
				FST::FST fst2(del.main_array[i], X8);
				if (FST::execute(fst))
				{
					std::cout << "l ";
					*log.stream << "l ";
					LT::SetEntry(&*lextable, LEX_LITERAL, (*idTable).size, number, position, stack.top(), 'l');
					IT::SetEntry(*idTable, (*idTable).size, (char*)"_L", number, IT::IDDATATYPE::INT, IT::IDTYPE::L);
					int a = BIN_TO_DEC(del.main_array[i]);
					if (a >= INT32_MIN && a <= INT32_MAX)
						(*idTable).table[(*idTable).size - 1].value.vint = a;
					else
						throw ERROR_THROW_IN(117, (*lextable).table[(*lextable).size - 1].sn, position);
				}
				else
				{
					if (FST::execute(fst2))
					{
						std::cout << "l ";
						*log.stream << "l ";
						LT::SetEntry(&*lextable, LEX_LITERAL, (*idTable).size, number, position, stack.top(), 'l');
						IT::SetEntry(*idTable, (*idTable).size, (char*)"_L", number, IT::IDDATATYPE::INT, IT::IDTYPE::L);
						int a = OCT_TO_DEC(del.main_array[i]);
						if (a >= INT32_MIN && a <= INT32_MAX)
							(*idTable).table[(*idTable).size - 1].value.vint = a;
						else
							throw ERROR_THROW_IN(117, (*lextable).table[(*lextable).size - 1].sn, position);
					}
					else
					{
						std::cout << "i ";
						*log.stream << "i ";
						LT::SetEntry(&*lextable, LEX_ID, IT::IsId(*idTable, del.main_array[i]), number, position, stack.top(), 'i');
						IT::SetEntry(*idTable, (*idTable).size, del.main_array[i], number, IT::IDDATATYPE::NON, IT::IDTYPE::N);
						typeId(&*lextable, &*idTable, del.main_array[i], number);
					}
				}
				break;
			}
			}
			position++;
		}
		stack.pop();
		if (!stack.empty())
			throw ERROR_THROW_IN(115, 0, 0);
		return del;
	}

	void typeId(LT::LexTable* lexTable, IT::IdTable* idTable, char id[TI_STR_MAXSIZE], int number)
	{
		if ((*idTable).table[IT::IsId(*idTable, id)].iddatatype == IT::IDDATATYPE::NON && (*idTable).table[IT::IsId(*idTable, id)].idtype == IT::IDTYPE::N)
		{
			if ((*lexTable).table[(*lexTable).size - 3].lexema == LEX_INTEGER && (*lexTable).table[(*lexTable).size - 2].lexema == LEX_FUNCTION)
			{
				(*idTable).table[(*idTable).size - 1].iddatatype = IT::IDDATATYPE::INT;
				(*idTable).table[(*idTable).size - 1].idtype = IT::IDTYPE::F;
				(*idTable).table[(*idTable).size - 1].value.vint = TI_INT_DEFAULT;
				(stack).push(id);
			}
			else if (((*lexTable).table[(*lexTable).size - 3].lexema == LEX_COMMA || (*lexTable).table[(*lexTable).size - 3].lexema == LEX_LEFTHESIS) &&
				(*lexTable).table[(*lexTable).size - 2].lexema == LEX_INTEGER)
			{
				(*idTable).table[(*idTable).size - 1].iddatatype = IT::IDDATATYPE::INT;
				(*idTable).table[(*idTable).size - 1].idtype = IT::IDTYPE::P;
				(*idTable).table[(*idTable).size - 1].value.vint = TI_INT_DEFAULT;
			}
			else if ((*lexTable).table[(*lexTable).size - 3].lexema == LEX_DECLARE && (*lexTable).table[(*lexTable).size - 2].lexema == LEX_INTEGER)
			{
				(*idTable).table[(*idTable).size - 1].iddatatype = IT::IDDATATYPE::INT;
				(*idTable).table[(*idTable).size - 1].idtype = IT::IDTYPE::V;
				(*idTable).table[(*idTable).size - 1].value.vint = TI_INT_DEFAULT;
			}
			else if ((*lexTable).table[(*lexTable).size - 3].lexema == LEX_STRING && (*lexTable).table[(*lexTable).size - 2].lexema == LEX_FUNCTION)
			{
				(*idTable).table[(*idTable).size - 1].iddatatype = IT::IDDATATYPE::STR;
				(*idTable).table[(*idTable).size - 1].idtype = IT::IDTYPE::F;
				*(*idTable).table[(*idTable).size - 1].value.vstr->str = TI_STR_DEFAULT;
				stack.push(id);
			}
			else if (((*lexTable).table[(*lexTable).size - 3].lexema == LEX_COMMA || (*lexTable).table[(*lexTable).size - 3].lexema == LEX_LEFTHESIS)
				&& (*lexTable).table[(*lexTable).size - 2].lexema == LEX_STRING)
			{
				(*idTable).table[(*idTable).size - 1].iddatatype = IT::IDDATATYPE::STR;
				(*idTable).table[(*idTable).size - 1].idtype = IT::IDTYPE::P;
				*(*idTable).table[(*idTable).size - 1].value.vstr->str = TI_STR_DEFAULT;
			}
			else if ((*lexTable).table[(*lexTable).size - 3].lexema == LEX_DECLARE && (*lexTable).table[(*lexTable).size - 2].lexema == LEX_STRING)
			{
				(*idTable).table[(*idTable).size - 1].iddatatype = IT::IDDATATYPE::STR;
				(*idTable).table[(*idTable).size - 1].idtype = IT::IDTYPE::V;
				*(*idTable).table[(*idTable).size - 1].value.vstr->str = TI_STR_DEFAULT;
			}
			else if ((*lexTable).table[(*lexTable).size - 3].lexema == LEX_BOOL && (*lexTable).table[(*lexTable).size - 2].lexema == LEX_FUNCTION)
			{
				(*idTable).table[(*idTable).size - 1].iddatatype = IT::IDDATATYPE::BOO;
				(*idTable).table[(*idTable).size - 1].idtype = IT::IDTYPE::F;
				(*idTable).table[(*idTable).size - 1].value.vbool = TI_BOOL_DEFAULT;
				stack.push(id);
			}
			else if (((*lexTable).table[(*lexTable).size - 3].lexema == LEX_COMMA || (*lexTable).table[(*lexTable).size - 3].lexema == LEX_LEFTHESIS) &&
				(*lexTable).table[(*lexTable).size - 2].lexema == LEX_BOOL)
			{
				(*idTable).table[(*idTable).size - 1].iddatatype = IT::IDDATATYPE::BOO;
				(*idTable).table[(*idTable).size - 1].idtype = IT::IDTYPE::P;
				(*idTable).table[(*idTable).size - 1].value.vbool = TI_BOOL_DEFAULT;
			}
			else if ((*lexTable).table[(*lexTable).size - 3].lexema == LEX_DECLARE && (*lexTable).table[(*lexTable).size - 2].lexema == LEX_BOOL)
			{
				(*idTable).table[(*idTable).size - 1].iddatatype = IT::IDDATATYPE::BOO;
				(*idTable).table[(*idTable).size - 1].idtype = IT::IDTYPE::V;
				(*idTable).table[(*idTable).size - 1].value.vbool = TI_BOOL_DEFAULT;
			}////
			else if ((*lexTable).table[(*lexTable).size - 3].lexema == LEX_CHAR && (*lexTable).table[(*lexTable).size - 2].lexema == LEX_FUNCTION)
			{
				(*idTable).table[(*idTable).size - 1].iddatatype = IT::IDDATATYPE::CHR;
				(*idTable).table[(*idTable).size - 1].idtype = IT::IDTYPE::F;
				(*idTable).table[(*idTable).size - 1].value.vbool = TI_STR_DEFAULT;
				stack.push(id);
			}
			else if (((*lexTable).table[(*lexTable).size - 3].lexema == LEX_COMMA || (*lexTable).table[(*lexTable).size - 3].lexema == LEX_LEFTHESIS) &&
				(*lexTable).table[(*lexTable).size - 2].lexema == LEX_CHAR)
			{
				(*idTable).table[(*idTable).size - 1].iddatatype = IT::IDDATATYPE::CHR;
				(*idTable).table[(*idTable).size - 1].idtype = IT::IDTYPE::P;
				strcpy_s((*idTable).table[(*idTable).size - 1].value.vchar, TI_CHAR_DEAFAULT);
			}
			else if ((*lexTable).table[(*lexTable).size - 3].lexema == LEX_DECLARE && (*lexTable).table[(*lexTable).size - 2].lexema == LEX_CHAR)
			{
				(*idTable).table[(*idTable).size - 1].iddatatype = IT::IDDATATYPE::CHR;
				(*idTable).table[(*idTable).size - 1].idtype = IT::IDTYPE::V;
				strcpy_s((*idTable).table[(*idTable).size - 1].value.vchar, TI_CHAR_DEAFAULT);
			}
			else
			{
				throw ERROR_THROW_IN(114, (*lexTable).table[(*lexTable).size - 1].sn, (*lexTable).table[(*lexTable).size - 1].count);
			}
			(*lexTable).table[((*lexTable).size) - 1].idxTI = IT::IsId(*idTable, id);
		}
		
	}
	int OCT_TO_DEC(char* st)
	{
		int i, s, k, p;
		s = 0;
		p = strlen(st);
		bool minus = false;
		if (st[0] == '7') {
			minus = true;
			i = 1;
		}
		else i = 0;
		for (; st[i] != 'o'; i++)
		{
			switch (toupper(st[i]))
			{	
			case '0': k = 0; break;
			case '1': k = 1; break;
			case '2': k = 2; break;
			case '3': k = 3; break;
			case '4': k = 4; break;
			case '5': k = 5; break;
			case '6': k = 6; break;
			case '7': k = 7; break;
			}
			s = s + k * pow(8, p-i-2);
		}
		if (minus)
			return -s;
		else return s;
	}
	int BIN_TO_DEC(char* st)
	{
		int i, s = 0, p;
		s = 0;
		p = strlen(st);
		bool minus = false;
		if (st[0] == '1') {
			minus = true; i = 1;
		}
		else i = 0;
		for (; st[i] != '\0'; i++)
		{
			if(st[i]=='1')
			s += pow(2, p - 1-i);
		}
		if (minus)
			return -s;
		else return s;
	}
	char** divideText(unsigned char source[], int size, int max_word, int size_word)		// формирование массива строк
	{
		char** word = new char* [max_word];	//  массив слов
		for (int i = 0; i < max_word; i++)
			word[i] = new char[size_word] {NULL};

		bool findSP, findLit = false;	// найден сепаратор, найден литерал
		int j = 0;
		char SP[] = { " ,;(){}=+-*%/\n" };
		for (int i = 0, k = 0; i < size - 1; i++, k++)
		{
			findSP = false;
			if (source[i] == '\"')	// если встречаетс€ ковычка
				findLit = !findLit;	// установить флаг в противоположное (false)
			if (source[i] == '\'')	// если встречаетс€ ковычка
				findLit = !findLit;	// установить флаг в противоположное (false)

			for (int t = 0; t < sizeof(SP) - 1; t++)
			{
				if (source[i] == SP[t] && findLit == false)		// если i-тый - сепаратор и это не литерал
				{
					if (source[i] == '-' && source[i - 1] == '=')
						break;
					findSP = true;
					if (word[j][0] != NULL) {  // если в начале слова не null
						word[j++][k] = '\0';	// то записать в конец слова \0
						k = 0;	// начать столбец с первого символа
					}
					if (SP[t] == ' ') {  // если символ - пробел => переход к следующему слову
						k = -1;
						break;
					}
					word[j][k++] = SP[t];	// записать сепаратор
					word[j++][k] = '\0';	// записать в конец слова \0
					k = -1;		// установить в предначальную позицию столбца
					break;
				}
			}
			if (!findSP)	// если не сепаратор
				word[j][k] = source[i];		//записать символ в массив
		}
		word[j][0] = '\0';		//последующие строки в null
		for (int i = 0; i < j; i++)
			if (!strcmp((char*)word[i], ""))	// если есть пуста€ строка => вернуть null
				return NULL;
		return word;	// иначе - массив слов
	}
	void clearSpace(unsigned char source[], int size)			// очистка пробельных символов
	{
		char SP[] = { " ,;(){}=+-*%/\n" };
		bool findLit = false;
		for (int i = 0; i < size; i++)
		{
			if (source[i] == '\"')	// если встречаетс€ ковычка
				findLit = !findLit;	// установить флаг в противоположное (false)
			if (source[i] == ' ' && findLit == false)
			{		// если i-тый символ - пробел и это не литерал
				for (int j = 0; j < sizeof(SP) - 1; j++)
				{
					if (source[i + 1] == SP[j] || source[i - 1] == SP[j] || i == 0)
					{	// если следующий или предыдущий символ - сепараторы
						for (int k = i; k < size; k++)
						{	// сдвиг массива
							source[k] = source[k + 1];
						}
						i--;		// возврат на ту же позицию
						break;
					}
				}
			}
		}
	}
}