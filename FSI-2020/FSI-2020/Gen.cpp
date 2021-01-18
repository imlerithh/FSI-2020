#include "stdafx.h"
#include "Gen.h"
#include "Lex.h"
#include <stack>
#include <string>

namespace Gen
{

	Gen::Gen(LT::LexTable plexT, IT::IdTable pidT)
	{
		idT = pidT;
		lexT = plexT;
		out = std::ofstream("../ASMLauncher/asm.asm");
		Head();
		Constants();

		Data();
		Code();
	}
	void Gen::Head()
	{
		out << ".586\n";
		out << ".model flat, stdcall\n";
		out << "includelib ../Debug/StaticLib.lib\n";
		out << "randomness PROTO\n";
		out << "transformatio PROTO: DWORD\n";
		out << "quadrum PROTO: SDWORD\n";
		out << "outInt PROTO:  SDWORD\n";
		out << "outChar PROTO: DWORD\n";
		out << "outString PROTO: DWORD, :DWORD\n";
		out << "outBool PROTO: SDWORD\n";
		out << "ExitProcess PROTO : DWORD\n\n";
		out << "\n.stack 4096\n";

	}
	void Gen::Constants()
	{
		out << ".const\n";
		for (int i = 0; i < idT.size; i++)
		{
			if (idT.table[i].idtype == IT::IDTYPE::L)
			{
				out << "\t" << idT.table[i].id;
				if (idT.table[i].iddatatype == IT::IDDATATYPE::STR)
					out << " byte " << idT.table[i].value.vstr->str << ", 10, 0";
				if (idT.table[i].iddatatype == IT::IDDATATYPE::CHR)
					out << " dword " << idT.table[i].value.vchar << ", 0";
				if (idT.table[i].iddatatype == IT::IDDATATYPE::INT)
					out << " sdword " << idT.table[i].value.vint;
				if (idT.table[i].iddatatype == IT::IDDATATYPE::BOO)
					out << " dword " << idT.table[i].value.vbool;

				out << '\n';
			}
		}
		out << "\tconsoletitle db \'FSI-2020\', 0\n";
	}
	void Gen::Data()
	{
		out << ".data\n";
		for (int i = 0; i < lexT.size; i++)
		{
			if (lexT.table[i].lexema == 'd')
			{
				if (idT.table[lexT.table[i + 2].idxTI].idtype == IT::IDTYPE::V)
				{
					out << "\t" << idT.table[lexT.table[i + 2].idxTI].id;
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype == IT::IDDATATYPE::BOO || idT.table[lexT.table[i + 2].idxTI].iddatatype == IT::IDDATATYPE::STR || idT.table[lexT.table[i + 2].idxTI].iddatatype == IT::IDDATATYPE::CHR)
						out << " dword 0";
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype == IT::IDDATATYPE::INT)
						out << " sdword 0";
					out << '\n';
				}
			}
		}
		out << "\tcounter sdword 0\n";
	}
	void Gen::Code()
	{
		out << "\n.code\n";
		int indOfFun = 0;
		int indOflex = -1;
		int rhesis = -1;
		//function - 1
		//if - 2
		//while - 3
		//for - 4
		//main - 5
		std::stack<int> stack;//
		std::stack<int> _if;

		std::stack<int> _for;

		short count_if = 0;
		short count_for = 0;

		bool proc = false;
		bool enter = false;
		for (int i = 0; i < lexT.size; i++)
		{
			switch (lexT.table[i].lexema)
			{
			case LEX_FUNCTION:
			{
				stack.push(1);
				indOfFun = i + 1;
				out << idT.table[lexT.table[indOfFun].idxTI].id << " PROC ";
				proc = true;
				while (lexT.table[i].lexema != ')')
				{
					rhesis = i;
					i++;
				}
				while (lexT.table[i].lexema != '(')
				{
					if (lexT.table[i].lexema == 'i')
					{
						if (idT.table[lexT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
						{
							out << idT.table[lexT.table[i].idxTI].id << ":sdword";
							if (lexT.table[i - 2].lexema != '(')
								out << ", ";
						}
						if (idT.table[lexT.table[i].idxTI].iddatatype == IT::IDDATATYPE::BOO || idT.table[lexT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR || idT.table[lexT.table[i].idxTI].iddatatype == IT::IDDATATYPE::CHR)
						{
							out << idT.table[lexT.table[i].idxTI].id << ":dword";
							if (lexT.table[i - 2].lexema != '(')
								out << ", ";
						}
					}
					i--;
				}
				i = rhesis;
				out << std::endl;
				break;
			}
			case LEX_MAIN:
			{
				stack.push(5);
				enter = true;
				out << "main PROC\n";
				break;
			}
			case LEX_BRACELET: 
			{
				if (stack.top() == 1)
				{

					out << idT.table[lexT.table[indOfFun].idxTI].id << " ENDP\n\n";
					stack.pop();
					indOfFun = 0;
					break;
				}
				if (stack.top() == 2)//if
				{
					stack.pop();
					out << "continue_if" << _if.top() << ":\n";
					_if.pop();
					break;
				}
				if (stack.top() == 4)//for
				{
					stack.pop();
					out << "dec counter\n";
					out << "mov ecx, counter\n";
					out << "loop _for" << _for.top() << '\n';
					break;
				}

				break;
			}
			case LEX_RETURN:
			{
				if (!enter)
				{
					if (idT.table[lexT.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::INT || idT.table[lexT.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::BOO || idT.table[lexT.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::CHR)
						out << "\tmov eax, " << idT.table[lexT.table[i + 1].idxTI].id << "\n\tret\n";
					if (idT.table[lexT.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::STR && idT.table[lexT.table[i + 1].idxTI].idtype == IT::IDTYPE::L)
						out << "\tmov eax, offset " << idT.table[lexT.table[i + 1].idxTI].id << "\n\tret\n";
					else out << "\tmov eax," << idT.table[lexT.table[i + 1].idxTI].id << "\n\tret\n";
					

				}
				else 
				{
					out << "\tpush " << idT.table[lexT.table[i + 1].idxTI].id << "\n";
				}
				break;
			}
			case LEX_PRINT:
			{
				if (lexT.table[i + 1].lexema == 'i' || lexT.table[i + 1].lexema == 'l')
				{
					if (idT.table[lexT.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::INT)
					{
						out << "\tpush " << idT.table[lexT.table[i + 1].idxTI].id << "\n";
						out << "call outInt\n";
					}
					else if (idT.table[lexT.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::STR)
					{
						out << "\tpush offset consoletitle\n";
						if (idT.table[lexT.table[i + 1].idxTI].idtype == IT::IDTYPE::L)
							out << "\tpush offset " << idT.table[lexT.table[i + 1].idxTI].id << "\n";
						else out << "\tpush " << idT.table[lexT.table[i + 1].idxTI].id << "\n";
						out << "call outString\n";
						
					}
					else if (idT.table[lexT.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::CHR) {
						out << "\tpush " << idT.table[lexT.table[i + 1].idxTI].id << "\n";
						out << "call outChar\n";
					}
					else
					{
						out << "\tpush " << idT.table[lexT.table[i + 1].idxTI].id << "\n";
						out << "call outBool\n";
					}

				}

				break;
			}
			case LEX_FOR:
			{
				stack.push(4);
				_for.push(count_for);
				out << "mov ecx, " << idT.table[lexT.table[i + 2].idxTI].id << '\n';
				out << "push " << idT.table[lexT.table[i + 2].idxTI].id << '\n';
				out << "pop counter\n";
				out << "inc counter\n";
				out << "_for" << _for.top() << ":\n";
				count_for++;
				break;
			}
			case LEX_IF:
			{
				stack.push(2);
				_if.push(count_if);
				out << "\tmov eax, " << idT.table[lexT.table[i + 2].idxTI].id << "\n";
				out << "\tmov ebx, " << 0 << "\n";
				out << "cmp eax, ebx\n";

				out << "ja true_if" << _if.top() << std::endl;
				out << "jmp continue_if" << _if.top() << std::endl;
				out << "true_if" << _if.top() << ":" << std::endl;
				count_if++;
				break;
			}
			case LEX_RAV:
			{
				indOflex = i - 1;
				while (lexT.table[i].operat != ';')
				{
					if (lexT.table[i].lexema != '#') {
						if (lexT.table[i].idxTI != TI_NULLIDX)
						{
							if (idT.table[lexT.table[i].idxTI].iddatatype == IT::IDDATATYPE::BOO && lexT.table[i].lexema != '@')
								out << "\tpush " << idT.table[lexT.table[i].idxTI].id << "\n";
							if (idT.table[lexT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT && lexT.table[i].lexema != '@')
								out << "\tpush " << idT.table[lexT.table[i].idxTI].id << "\n";
							if (idT.table[lexT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR && lexT.table[i].lexema != '@')
								if (idT.table[lexT.table[i].idxTI].idtype == IT::IDTYPE::L)
								out << "\tpush offset " << idT.table[lexT.table[i].idxTI].id << "\n";
								else out << "\tpush " << idT.table[lexT.table[i].idxTI].id << "\n";
							if (idT.table[lexT.table[i].idxTI].iddatatype == IT::IDDATATYPE::CHR && lexT.table[i].lexema != '@')
								out << "\tpush " << idT.table[lexT.table[i].idxTI].id << "\n";
						}
						if (lexT.table[i].lexema == '@')
						{
							if (lexT.table[i].operat == 'x')
							{
								out << "call randomness\n";
								out << "\tpush eax\n";
							}
							else if (lexT.table[i].operat == 'y')
							{
								out << "call transformatio\n";
								out << "\tpush eax\n";
							}
							else if (lexT.table[i].operat == 'q')
							{
								out << "call quadrum\n";
								out << "\tpush eax\n";
							}
							else
							{
								out << "call " << idT.table[lexT.table[i].idxTI].id << "\n";
								out << "\tpush eax\n";
							}
						}
						if (lexT.table[i].operat == '+')
						{
							out << "\tpop eax\n";
							out << "\tpop ebx\n";
							out << "add eax, ebx\n";
							out << "\tpush eax\n";
						}
						if (lexT.table[i].operat == '-')
						{
							out << "\tpop ebx\n";
							out << "\tpop eax\n";
							out << "sub eax, ebx\n";
							out << "\tpush eax\n";
						}
						if (lexT.table[i].operat == '*')
						{
							out << "\tpop eax\n";
							out << "\tpop ebx\n";
							out << "imul ebx\n";
							out << "\tpush eax\n";
						}
						if (lexT.table[i].operat == '/')
						{
							out << "\tpop ebx\n";
							out << "\tpop eax\n";
							out << "\tmov edx, 0\n";
							out << "idiv ebx\n";
							out << "\tpush eax\n";
						}
						if (lexT.table[i].operat == '%')
						{
							out << "\tpop ebx\n";
							out << "\tpop eax\n";
							out << "\tmov edx, 0\n";
							out << "idiv ebx\n";
							out << "\tpush edx\n";
						}
					}
					i++;
				}

				out << "\tpop " << idT.table[lexT.table[indOflex].idxTI].id << "\n";
			}
			default:
				break;
			}
		}
		out << "call ExitProcess\n";
		out << "main ENDP\n";
		out << "end main\n";
	}
}