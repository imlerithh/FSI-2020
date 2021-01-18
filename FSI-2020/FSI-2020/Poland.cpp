#include "stdafx.h"
#include <stack>
#include <queue>
#include "Poland.h"

using namespace std;
using namespace Poland;
int prior(char l)
{
	if (l == '+' || l == '-')
		return 1;
	if (l == '*' || l == '/' || l == '%')
		return 2;
	return 3;
}

bool Poland::PolishNotation(int i, LT::LexTable* lextable, IT::IdTable& idTable)
{
	std::stack<LT::Entry> stack;//операциии
	std::queue<LT::Entry> queue;//ids & literals
	short marker = i;
	for (i; (*lextable).table[i].operat != ';'; i++)
	{
		if ((*lextable).table[i].operat >= 48 && (*lextable).table[i].operat <= 122)
		{
			if ((*lextable).table[i].idxTI != TI_NULLIDX /*|| (*lextable).table[i].operat == 'o'*/)//если это идентификатор
			{
				if (idTable.table[(*lextable).table[i].idxTI].idtype == IT::IDTYPE::F)
				{
					do
					{
						if ((*lextable).table[i].operat != '(' && (*lextable).table[i].operat != ',')
						{
							queue.push((*lextable).table[i]);
							i++;
						}
						else
						{
							i++;
						}
					} while ((*lextable).table[i].operat != ')');
					// вместо ) ставлю id функции и замен€ю лексему на @
					(*lextable).table[marker] = queue.front();
					queue.pop();
					marker++;
					queue.front().lexema = '@';
					queue.push(queue.front());
					queue.pop();
					i++;
					//поставлю все до @ в таблицу лексем
					for (marker; marker < marker + queue.size() - 1; marker++)
					{
						(*lextable).table[marker] = queue.front();
						queue.pop();
					}
				}
			}
			else if ((*lextable).table[i].operat == 'x' || (*lextable).table[i].operat == 'y' || (*lextable).table[i].operat == 'q')
			{
				do
				{
					if ((*lextable).table[i].operat != '(' && (*lextable).table[i].operat != ',')
					{
						queue.push((*lextable).table[i]);
						i++;
					}
					else
					{
						i++;
					}
				} while ((*lextable).table[i].operat != ')');
				// вместо ) ставлю id функции и замен€ю лексему на @
				(*lextable).table[marker] = queue.front();
				queue.pop();
				marker++;
				queue.front().lexema = '@';
				queue.push(queue.front());
				queue.pop();
				i++;
				//поставлю все до @ в таблицу лексем
				for (marker; marker < marker + queue.size() - 1; marker++)
				{
					(*lextable).table[marker] = queue.front();
					queue.pop();
				}
			}
		}
		if ((*lextable).table[i].operat < 48)//( ) * + - /
		{
			if (stack.size() > 0)
			{
				if (prior((*lextable).table[i].operat) <= prior(stack.top().operat) && (*lextable).table[i].operat != ')' && stack.top().operat != '(')
				{
					queue.push(stack.top());
					stack.pop();
					stack.push((*lextable).table[i]);
				}
				else if (prior((*lextable).table[i].operat) > prior(stack.top().operat) && (*lextable).table[i].operat != ')' && (*lextable).table[i].operat != '(')
				{
					stack.push((*lextable).table[i]);
				}
				else if ((*lextable).table[i].operat == ')')
				{
					while (stack.top().operat != '(')
					{
						queue.push(stack.top());
						stack.pop();
					}
					stack.pop();//удалю (
				}
				else
				{
					stack.push((*lextable).table[i]);
				}
			}
			else
			{
				stack.push((*lextable).table[i]);
			}
		}
		if ((*lextable).table[i].operat >= 48 && (*lextable).table[i].operat <= 122)
		{
			queue.push((*lextable).table[i]);
		}
		if ((*lextable).table[i].operat == ';')
			break;
	}
	while (stack.size() != 0)
	{
		queue.push(stack.top());
		stack.pop();
	}
	//измен€ю таблицу лексем
	for (marker; marker < i; marker++)
	{
		if (!queue.empty())
		{
			(*lextable).table[marker] = queue.front();
			queue.pop();
		}
		else
		{
			(*lextable).table[marker].idxTI = -1;
			(*lextable).table[marker].lexema = '#';
			//(*lextable).table[marker].sn = -1;
			//(*lextable).table[marker].lt_vision = -3;
		}
	}
	return true;
}
