#pragma once
#include "Environment.h"	
#include <string>
#include <fstream>
#define TI_MAXSIZE		4096				// максимальное количество строк в таблице идентификаторов
#define TI_INT_DEFAULT  0x00000000			// значение по умолчанию дл€ типа integer
#define TI_STR_DEFAULT  0x00				// значение по умолчанию дл€ типа string
#define TI_NULLIDX		0xffffffff			// нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE  255					// максимальна€ длина строки


#define MAXSUFFIXSIZE 20
#define PARM_ID L".id.txt"


namespace IT								// таблица идентификаторов 
{
	enum IDDATATYPE { NODEF = -1, DEF = 0, INT = 1, STR, BOOL, HTMLOBJ, BYTE};				// типы данных
	enum IDTYPE { D, V, F, P, L, DF};			// типы идентификаторов: переменна€, функци€, параметр, литерал

	struct Entry							// строка таблицы идентификаторов
	{
		int str_number; //номер строки
		ENV::Environment* indEnv;						//ссылка на окружени€ идентификатора
		int firstApi;									// индекс первого вхождени€ в таблице лексем
		int firstInit;
		char id[ID_MAXSIZE + MAXSUFFIXSIZE + 5];		// идентификатор (автоматически усекаетс€ до ID_MAXSIZE)
		IDDATATYPE iddatatype;							// тип данных
		IDTYPE idtype;									// тип идентификатора
		union
		{
			int vint;									// значение integer
			char operation = '\0';
			struct
			{
				unsigned char len;						// количество символов в string
				char str[TI_STR_MAXSIZE];				// символы string
			} vstr;						// значение string
			struct
			{
				int parmQuantity;				//количество параметров 
				IDDATATYPE type[TI_MAX_COUNT_PARM];
			}parm;
		} value;						// значение идентификатора
		
		int refCount;					//колиетсво ссылок на идентификатор
		//void ChangeParrentFunction(const char* parrentFunc);
		void AddParm(IDDATATYPE iddatatype);
		Entry();
		Entry(const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, int str_number); 
		Entry(const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, const char* ch, int str_number);//строковый литерал
	};

	struct IdTable							// экземпл€р таблицы идентификаторов
	{
		int noname_lexema_count;				// счЄтчик неидентифицированных лексем
		int maxsize;							// емкость таблицы идентификаторов < TI_MAXSIZE
		int size;								// текущий размер таблицы идентификаторов < maxsize
		int literalCount;
		int funCount;
		int varCount;
		Entry* table;							// массив строк таблицы идентификаторов
		Entry GetEntry(							// получить строку таблицы идентификаторов
			int n									// номер получаемой строки
		);
		int IsId(								// возврат: номер строки (если есть), TI_NULLIDX(если нет)
			const char id[ID_MAXSIZE]				// идентификатор
		);

		int IsFirstApi(int FirstApi);

		void Add(								// добавить строку в таблицу идентификаторов 
			Entry entry								// строка таблицы идентификторов
		);
		void PrintIdTable(std::ofstream& idStream);	// вывод таблицы идентификаторов
		IdTable();
		char* GetLexemaName();
	};


	void Delete(IdTable& idtable);			// удалить таблицу лексем (освободить пам€ть)
};

