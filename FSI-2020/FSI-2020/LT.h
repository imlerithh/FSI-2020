#pragma once
#define LEXEMA_FIXSIZE 1
#define LT_VISLA 7
#define LT_MAXSIZE 4196
#define LT_TI_NULLIDX 0xffffffff
#define LEX_INTEGER 'n'
#define LEX_STRING 's'
#define LEX_BOOL 'b'
#define LEX_CHAR 'j'

#define LEX_RANDOMNESS 'x'
#define LEX_TRANSFORMATIO 'y'
#define LEX_POW 'q'			//quadrum

#define LEX_FOR 'z'

#define LEX_IF 'u'			//conditio
#define LEX_ID 'i'
#define LEX_LITERAL 'l'
#define LEX_FUNCTION 'f'	//munus
#define LEX_DECLARE 'd'		//annuntiate
#define LEX_RETURN 'r'		//reditus
#define LEX_PRINT 'p'		//loquor
#define LEX_MAIN 'm'		//pelagus
#define LEX_SEMICOLON ';'	
#define LEX_COMMA ','
#define LEX_LEFTBRACE '{'
#define LEX_BRACELET '}'
#define LEX_LEFTHESIS '('
#define LEX_RIGHTHESIS ')'
#define LEX_PLUS 'v'
#define LEX_MINUS 'v'
#define LEX_STAR 'v'
#define LEX_DIRSLASH 'v'
#define LEX_MODULE 'v'
#define LEX_RAV '='

namespace LT
{
	struct Entry						// ������ ������� ������
	{
		char lexema;					// �������
		int	 sn = 0;					// ����� ������ � �������� ������
		int	 idxTI;						// ������ � ������� ���������������
		char* lt_vision;				//��� ���������
		char operat;					//����
		int count;						//����� �������
	};

	struct LexTable						// ��������� �������� ������
	{
		int maxsize;					// ������� ������� ������ < LT_MAXSIZE
		int size;						// ������� ������ ������� ������ < MAXSIZE
		Entry* table;					// ������ ����� ������� ������
	};

	LexTable Create(		 // ������� ������� ������
		int size // ������� ������� ������ < LT_MAXSIZE
	);
	void Add(					// �������� ������ � ������� ������ 
		LexTable& lextable,	// ��������� ������� ������
		Entry entry			// ������ ������� ������
	);
	Entry Getentry(LexTable& lextable, int n);
	void SetEntry(LT::LexTable* entry, unsigned char lexema, int indx, int line, int count, char* vision, char operat);
	void Delete(LexTable& lextable);	// ������� ������� ������ ( ���������� ������ )
};
