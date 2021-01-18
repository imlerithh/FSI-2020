#pragma once
#define	ID_MAXSIZE		5			// максимальное количество символов в идентификатореID_MAXSIZE
#define	TI_MAXSIZE		4196		// максимальное количество строк в таблице идентификаторов
#define	TI_INT_DEFAULT	0x00000000	// значение по умолчанию дл€ типа int
#define	TI_STR_DEFAULT	0x00		// значеник по умолчанию дл€ типа string 
#define TI_BOOL_DEFAULT false			// значение по умолчанию дл€ типа bool
#define	TI_NULLIDX		0xffffffff	// нет элемента таблицы идентификаторов
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
		N = 0,		//ничего
		V = 1,		//переменна€	
		F = 2,		//функци€ 
		P = 3,		//параметр
		L = 4		//литерал
	};

	struct Entry									// строка таблицы идентефикаторов
	{
		int			idxfirstLE;						// индекс первой строки в таблице лексем
		char		id[ID_MAXSIZE];				//идентефикатор (автоматически усекаетс€ до ID_MAXSIZE)
		IDDATATYPE	iddatatype;						//тип данных
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

	struct  IdTable						// экземпл€р таблицы идентефикаторов
	{
		short lit = 0;
		int maxsize;					// емкость таблицы идентефикаторов < TI_MAXSIZE
		int size;						// текущий размер таблицы идентефикаторов < maxsize
		Entry* table;					// массив строк таблицы идентефикаторов
	};


	IdTable Create(						// создать таблицу идентефикаторов	
		int size						// емкость таблицы идентефикаторов < TI_MAXSIZE 
	);
	void Add(							// добавить строку в таблицу идентефикаторов
		IdTable& idtable,				// экземпл€р таблицы идентефикаторов
		Entry entry						// строка таблицы идентефикаторов
	);
	Entry Getentry(IdTable& idtable, int n);
	void SetEntry(IdTable& entry, int idxfirstLE, char id[ID_MAXSIZE], int line, IDDATATYPE iddatatype, IDTYPE idtype);
	int IsId(IdTable& idtable, char id[ID_MAXSIZE]);

	void Delete(IdTable& idtable);		// удалить таблицу идентефикаторов ( освободить пам€ть );
}

