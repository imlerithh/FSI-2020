#pragma once

#include "FST.h"


#define RANDOMNESS 11, \
	FST::NODE(1, FST::RELATION('r', 1)),\
	FST::NODE(1, FST::RELATION('a', 2)),\
	FST::NODE(1, FST::RELATION('n', 3)),\
	FST::NODE(1, FST::RELATION('d', 4)),\
	FST::NODE(1, FST::RELATION('o', 5)),\
	FST::NODE(1, FST::RELATION('m', 6)),\
	FST::NODE(1, FST::RELATION('n', 7)),\
	FST::NODE(1, FST::RELATION('e', 8)),\
	FST::NODE(1, FST::RELATION('s', 9)),\
	FST::NODE(1, FST::RELATION('s', 10)),\
	FST::NODE()

#define TRANSFORMATIO 14, \
	FST::NODE(1, FST::RELATION('t', 1)),\
	FST::NODE(1, FST::RELATION('r', 2)),\
	FST::NODE(1, FST::RELATION('a', 3)),\
	FST::NODE(1, FST::RELATION('n', 4)),\
	FST::NODE(1, FST::RELATION('s', 5)),\
	FST::NODE(1, FST::RELATION('f', 6)),\
	FST::NODE(1, FST::RELATION('o', 7)),\
	FST::NODE(1, FST::RELATION('r', 8)),\
	FST::NODE(1, FST::RELATION('m', 9)),\
	FST::NODE(1, FST::RELATION('a', 10)),\
	FST::NODE(1, FST::RELATION('t', 11)),\
	FST::NODE(1, FST::RELATION('i', 12)),\
	FST::NODE(1, FST::RELATION('o', 13)),\
	FST::NODE()


#define CHAR 7, \
	FST::NODE(1, FST::RELATION('s', 1)),\
	FST::NODE(1, FST::RELATION('i', 2)),\
	FST::NODE(1, FST::RELATION('g', 3)),\
	FST::NODE(1, FST::RELATION('n', 4)),\
	FST::NODE(1, FST::RELATION('u', 5)),\
	FST::NODE(1, FST::RELATION('m', 6)),\
	FST::NODE()

#define LITERAL_CHAR 4,	\
	FST::NODE(2, FST::RELATION('\'', 1), FST::RELATION('\'', 2)),\
	FST::NODE(62,	\
	FST::RELATION('a', 2), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 2), FST::RELATION('e', 2), FST::RELATION('f', 2),\
	FST::RELATION('g', 2), FST::RELATION('h', 2), FST::RELATION('i', 2), FST::RELATION('j', 2), FST::RELATION('k', 2), FST::RELATION('l', 2),\
	FST::RELATION('m', 2), FST::RELATION('n', 2), FST::RELATION('o', 2), FST::RELATION('p', 2), FST::RELATION('q', 2), FST::RELATION('r', 2),\
	FST::RELATION('s', 2), FST::RELATION('t', 2), FST::RELATION('u', 2), FST::RELATION('v', 2), FST::RELATION('w', 2), FST::RELATION('x', 2),\
	FST::RELATION('y', 2), FST::RELATION('z', 2), FST::RELATION('1', 2), FST::RELATION('2', 2), FST::RELATION('3', 2), FST::RELATION('4', 2),\
	FST::RELATION('5', 2), FST::RELATION('6', 2), FST::RELATION('7', 2), FST::RELATION('8', 2), FST::RELATION('9', 2), FST::RELATION('0', 2),\
	\
	FST::RELATION('A', 2), FST::RELATION('B', 2), FST::RELATION('C', 2), FST::RELATION('D', 2), FST::RELATION('E', 2), FST::RELATION('F', 2),\
	FST::RELATION('G', 2), FST::RELATION('H', 2), FST::RELATION('I', 2), FST::RELATION('J', 2), FST::RELATION('K', 2), FST::RELATION('L', 2),\
	FST::RELATION('M', 2), FST::RELATION('N', 2), FST::RELATION('O', 2), FST::RELATION('P', 2), FST::RELATION('Q', 2), FST::RELATION('R', 2),\
	FST::RELATION('S', 2), FST::RELATION('T', 2), FST::RELATION('U', 2), FST::RELATION('V', 2), FST::RELATION('W', 2), FST::RELATION('X', 2),\
	FST::RELATION('Y', 2), FST::RELATION('Z', 2)), \
	\
	FST::NODE(1, FST::RELATION('\'', 3)),\
	FST::NODE()

#define FOR 7, \
	FST::NODE(1, FST::RELATION('r', 1)),\
	FST::NODE(1, FST::RELATION('e', 2)),\
	FST::NODE(1, FST::RELATION('p', 3)),\
	FST::NODE(1, FST::RELATION('e', 4)),\
	FST::NODE(1, FST::RELATION('a', 5)),\
	FST::NODE(1, FST::RELATION('t', 6)),\
	FST::NODE()

#define POW 8, \
	FST::NODE(1, FST::RELATION('q', 1)),\
	FST::NODE(1, FST::RELATION('u', 2)),\
	FST::NODE(1, FST::RELATION('a', 3)),\
	FST::NODE(1, FST::RELATION('d', 4)),\
	FST::NODE(1, FST::RELATION('r', 5)),\
	FST::NODE(1, FST::RELATION('u', 6)),\
	FST::NODE(1, FST::RELATION('m', 7)),\
	FST::NODE()

#define IF 9, \
	FST::NODE(1, FST::RELATION('c', 1)),\
	FST::NODE(1, FST::RELATION('o', 2)),\
	FST::NODE(1, FST::RELATION('n', 3)),\
	FST::NODE(1, FST::RELATION('d', 4)),\
	FST::NODE(1, FST::RELATION('i', 5)),\
	FST::NODE(1, FST::RELATION('t', 6)),\
	FST::NODE(1, FST::RELATION('i', 7)),\
	FST::NODE(1, FST::RELATION('o', 8)),\
	FST::NODE()

#define WHILE 6, \
	FST::NODE(1, FST::RELATION('r', 1)),\
	FST::NODE(1, FST::RELATION('u', 2)),\
	FST::NODE(1, FST::RELATION('r', 3)),\
	FST::NODE(1, FST::RELATION('s', 4)),\
	FST::NODE(1, FST::RELATION('u', 5)),\
	FST::NODE(1, FST::RELATION('s', 5)),\
	FST::NODE()

#define TRUE 6, \
	FST::NODE(1, FST::RELATION('v', 1)),\
	FST::NODE(1, FST::RELATION('e', 2)),\
	FST::NODE(1, FST::RELATION('r', 3)),\
	FST::NODE(1, FST::RELATION('u', 4)),\
	FST::NODE(1, FST::RELATION('m', 5)),\
	FST::NODE()

#define FALSE 7, \
	FST::NODE(1, FST::RELATION('f', 1)),\
	FST::NODE(1, FST::RELATION('a', 2)),\
	FST::NODE(1, FST::RELATION('l', 3)),\
	FST::NODE(1, FST::RELATION('s', 4)),\
	FST::NODE(1, FST::RELATION('u', 5)),\
	FST::NODE(1, FST::RELATION('s', 6)),\
	FST::NODE()

#define BOOL 8, \
	FST::NODE(1, FST::RELATION('l', 1)),\
	FST::NODE(1, FST::RELATION('o', 2)),\
	FST::NODE(1, FST::RELATION('g', 3)),\
	FST::NODE(1, FST::RELATION('i', 4)),\
	FST::NODE(1, FST::RELATION('c', 5)),\
	FST::NODE(1, FST::RELATION('u', 6)),\
	FST::NODE(1, FST::RELATION('s', 7)),\
	FST::NODE()

#define DECLARE 11,	\
	FST::NODE(1, FST::RELATION('a', 1)),\
	FST::NODE(1, FST::RELATION('n', 2)),\
	FST::NODE(1, FST::RELATION('n', 3)),\
	FST::NODE(1, FST::RELATION('u', 4)),\
	FST::NODE(1, FST::RELATION('n', 5)),\
	FST::NODE(1, FST::RELATION('t', 6)),\
	FST::NODE(1, FST::RELATION('i', 7)),\
	FST::NODE(1, FST::RELATION('a', 8)),\
	FST::NODE(1, FST::RELATION('t', 9)),\
	FST::NODE(1, FST::RELATION('e', 10)),\
	FST::NODE()

#define INTEGER 6,	\
	FST::NODE(1, FST::RELATION('t', 1)),\
	FST::NODE(1, FST::RELATION('o', 2)),\
	FST::NODE(1, FST::RELATION('t', 3)),\
	FST::NODE(1, FST::RELATION('u', 4)),\
	FST::NODE(1, FST::RELATION('m', 5)),\
	FST::NODE()

#define STRING 7,	\
	FST::NODE(1, FST::RELATION('c', 1)),\
	FST::NODE(1, FST::RELATION('h', 2)),\
	FST::NODE(1, FST::RELATION('o', 3)),\
	FST::NODE(1, FST::RELATION('r', 4)),\
	FST::NODE(1, FST::RELATION('d', 5)),\
	FST::NODE(1, FST::RELATION('a', 6)),\
	FST::NODE()

#define FUNCTION 6,	\
	FST::NODE(1, FST::RELATION('m', 1)),\
	FST::NODE(1, FST::RELATION('u', 2)),\
	FST::NODE(1, FST::RELATION('n', 3)),\
	FST::NODE(1, FST::RELATION('u', 4)),\
	FST::NODE(1, FST::RELATION('s', 5)),\
	FST::NODE()

#define RETURN 8,	\
	FST::NODE(1, FST::RELATION('r', 1)),\
	FST::NODE(1, FST::RELATION('e', 2)),\
	FST::NODE(1, FST::RELATION('d', 3)),\
	FST::NODE(1, FST::RELATION('i', 4)),\
	FST::NODE(1, FST::RELATION('t', 5)),\
	FST::NODE(1, FST::RELATION('u', 6)),\
	FST::NODE(1, FST::RELATION('s', 7)),\
	FST::NODE()

#define PRINT 7,	\
	FST::NODE(1, FST::RELATION('l', 1)),\
	FST::NODE(1, FST::RELATION('o', 2)),\
	FST::NODE(1, FST::RELATION('q', 3)),\
	FST::NODE(1, FST::RELATION('u', 4)),\
	FST::NODE(1, FST::RELATION('o', 5)),\
	FST::NODE(1, FST::RELATION('r', 6)),\
	FST::NODE()

#define MAIN 8,	\
	FST::NODE(1, FST::RELATION('p', 1)),\
	FST::NODE(1, FST::RELATION('e', 2)),\
	FST::NODE(1, FST::RELATION('l', 3)),\
	FST::NODE(1, FST::RELATION('a', 4)),\
	FST::NODE(1, FST::RELATION('g', 5)),\
	FST::NODE(1, FST::RELATION('u', 6)),\
	FST::NODE(1, FST::RELATION('s', 7)),\
	FST::NODE()

#define ID 2,	\
	FST::NODE(62,	\
	FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('c', 0), FST::RELATION('d', 0), FST::RELATION('e', 0), FST::RELATION('f', 0),\
	FST::RELATION('g', 0), FST::RELATION('h', 0), FST::RELATION('i', 0), FST::RELATION('j', 0), FST::RELATION('k', 0), FST::RELATION('l', 0),\
	FST::RELATION('m', 0), FST::RELATION('n', 0), FST::RELATION('o', 0), FST::RELATION('p', 0), FST::RELATION('q', 0), FST::RELATION('r', 0),\
	FST::RELATION('s', 0), FST::RELATION('t', 0), FST::RELATION('u', 0), FST::RELATION('v', 0), FST::RELATION('w', 0), FST::RELATION('x', 0),\
	FST::RELATION('y', 0), FST::RELATION('z', 0),\
	\
	FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1),\
	FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 1), FST::RELATION('1', 1), FST::RELATION('2', 1),\
	FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1), FST::RELATION('e', 1), FST::RELATION('f', 1),\
	FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1), FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1),\
	FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1), FST::RELATION('p', 1), FST::RELATION('q', 1), FST::RELATION('r', 1),\
	FST::RELATION('s', 1), FST::RELATION('t', 1), FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1),\
	FST::RELATION('y', 1), FST::RELATION('z', 1)),\
	FST::NODE()

#define X2 2,	\
	FST::NODE(4,	\
	FST::RELATION('0', 0), FST::RELATION('1', 0),\
	\
	FST::RELATION('0', 1), FST::RELATION('1', 1)),\
	FST::NODE()

#define X8 3,	\
	FST::NODE(14,	\
	FST::RELATION('1', 0), FST::RELATION('2', 0), FST::RELATION('3', 0), FST::RELATION('4', 0), FST::RELATION('5', 0),\
	FST::RELATION('6', 0), FST::RELATION('7', 0), \
	\
	FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1),\
	FST::RELATION('6', 1), FST::RELATION('7', 1)), \
	FST::NODE(1, FST::RELATION('o', 2)),\
	FST::NODE()

#define LITERAL_STR 4,	\
	FST::NODE(2, FST::RELATION('\"', 1), FST::RELATION('\"', 2)),\
	FST::NODE(158,	\
	FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1), FST::RELATION('e', 1), FST::RELATION('f', 1),\
	FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1), FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1),\
	FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1), FST::RELATION('p', 1), FST::RELATION('q', 1), FST::RELATION('r', 1),\
	FST::RELATION('s', 1), FST::RELATION('t', 1), FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1),\
	FST::RELATION('y', 1), FST::RELATION('z', 1), FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1),\
	FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 1),\
	\
	FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1),\
	FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1),\
	FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1),\
	FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1),\
	FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1), FST::RELATION('�', 1),\
	FST::RELATION('+', 1), FST::RELATION('{', 1), FST::RELATION('}', 1), FST::RELATION(' ', 1), FST::RELATION('.', 1), FST::RELATION(',', 1),\
	FST::RELATION('\'', 1), FST::RELATION('/', 1), FST::RELATION(';', 1), FST::RELATION('*', 1), FST::RELATION('-', 1), FST::RELATION(')', 1),\
	FST::RELATION('(', 1), \
	\
	FST::RELATION('a', 2), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 2), FST::RELATION('e', 2), FST::RELATION('f', 2),\
	FST::RELATION('g', 2), FST::RELATION('h', 2), FST::RELATION('i', 2), FST::RELATION('j', 2), FST::RELATION('k', 2), FST::RELATION('l', 2),\
	FST::RELATION('m', 2), FST::RELATION('n', 2), FST::RELATION('o', 2), FST::RELATION('p', 2), FST::RELATION('q', 2), FST::RELATION('r', 2),\
	FST::RELATION('s', 2), FST::RELATION('t', 2), FST::RELATION('u', 2), FST::RELATION('v', 2), FST::RELATION('w', 2), FST::RELATION('x', 2),\
	FST::RELATION('y', 2), FST::RELATION('z', 2), FST::RELATION('1', 2), FST::RELATION('2', 2), FST::RELATION('3', 2), FST::RELATION('4', 2),\
	FST::RELATION('5', 2), FST::RELATION('6', 2), FST::RELATION('7', 2), FST::RELATION('8', 2), FST::RELATION('9', 2), FST::RELATION('0', 2),\
	\
	FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2),\
	FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2),\
	FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2),\
	FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2),\
	FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2), FST::RELATION('�', 2),\
	FST::RELATION('+', 2), FST::RELATION('{', 2), FST::RELATION('}', 2), FST::RELATION(' ', 2), FST::RELATION('.', 2), FST::RELATION(',', 2),\
	FST::RELATION('\'', 2), FST::RELATION('/', 2), FST::RELATION(';', 2), FST::RELATION('*', 2), FST::RELATION('-', 2), FST::RELATION(')', 2),\
	FST::RELATION('(', 2)),\
	\
	FST::NODE(1, FST::RELATION('\"', 3)),\
	FST::NODE()

#define PLUS 2,	\
	FST::NODE(1, FST::RELATION('+', 1)),\
	FST::NODE()

#define MINUS 2,	\
	FST::NODE(1, FST::RELATION('-', 1)),\
	FST::NODE()

#define STAR 2,	\
	FST::NODE(1, FST::RELATION('*', 1)),\
	FST::NODE()

#define DIRSLASH 2,	\
	FST::NODE(1, FST::RELATION('/', 1)),\
	FST::NODE()

#define MODULE 2,	\
	FST::NODE(1, FST::RELATION('%', 1)),\
	FST::NODE()

#define SEMICOLON 2,	\
	FST::NODE(1, FST::RELATION(';', 1)),\
	FST::NODE()

#define COMMA 2,	\
	FST::NODE(1, FST::RELATION(',', 1)),\
	FST::NODE()

#define LEFTBRACE 2,	\
	FST::NODE(1, FST::RELATION('{', 1)),\
	FST::NODE()

#define BRACELET 2,	\
	FST::NODE(1, FST::RELATION('}', 1)),\
	FST::NODE()

#define LEFTTHESIS 2, \
FST::NODE(1, FST::RELATION('(', 1)), \
FST::NODE()

#define RIGHTTHESIS 2, \
FST::NODE(1, FST::RELATION(')', 1)), \
FST::NODE()

#define RAVNO 2,	\
	FST::NODE(1, FST::RELATION('=', 1)),\
	FST::NODE()
