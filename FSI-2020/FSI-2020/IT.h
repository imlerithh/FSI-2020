#pragma once
#define	ID_MAXSIZE		5			// ������������ ���������� �������� � ��������������ID_MAXSIZE
#define	TI_MAXSIZE		4196		// ������������ ���������� ����� � ������� ���������������
#define	TI_INT_DEFAULT	0x00000000	// �������� �� ��������� ��� ���� int
#define	TI_STR_DEFAULT	0x00		// �������� �� ��������� ��� ���� string 
#define TI_BOOL_DEFAULT false			// �������� �� ��������� ��� ���� bool
#define	TI_NULLIDX		0xffffffff	// ��� �������� ������� ���������������
#define	TI_STR_MAXSIZE	255
#define TI_BOOL_MAXSIZE 6
#define TI_CHAR_DEAFAULT "' '"


namespace IT
{
	enum IDDATATYPE {
		NON = 0,
		INT = 1,			//ingeter
		STR = 2,			//string	
		BOO = 3,			//bool
		CHR = 4,			//char
	};
	enum IDTYPE {
		N = 0,		//������
		V = 1,		//����������	
		F = 2,		//������� 
		P = 3,		//��������
		L = 4		//�������
	};

	struct Entry									// ������ ������� ���������������
	{
		int			idxfirstLE;						// ������ ������ ������ � ������� ������
		char		id[ID_MAXSIZE];				//������������� (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE	iddatatype;						//��� ������
		IDTYPE		idtype;


		union
		{
			int vint;
			int vbool;
			char vchar[4];
			struct
			{
				char len;
				char str[TI_STR_MAXSIZE - 1];
			}	vstr[TI_STR_MAXSIZE];
		}value;
	};

	struct  IdTable						// ��������� ������� ���������������
	{
		short lit = 0;
		int maxsize;					// ������� ������� ��������������� < TI_MAXSIZE
		int size;						// ������� ������ ������� ��������������� < maxsize
		Entry* table;					// ������ ����� ������� ���������������
	};


	IdTable Create(						// ������� ������� ���������������	
		int size						// ������� ������� ��������������� < TI_MAXSIZE 
	);
	void Add(							// �������� ������ � ������� ���������������
		IdTable& idtable,				// ��������� ������� ���������������
		Entry entry						// ������ ������� ���������������
	);
	Entry Getentry(IdTable& idtable, int n);
	void SetEntry(IdTable& entry, int idxfirstLE, char id[ID_MAXSIZE], int line, IDDATATYPE iddatatype, IDTYPE idtype);
	int IsId(IdTable& idtable, char id[ID_MAXSIZE]);

	void Delete(IdTable& idtable);		// ������� ������� ��������������� ( ���������� ������ );
}

