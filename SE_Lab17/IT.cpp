#include "stdafx.h"
#include <cmath>

namespace IT
{
	IdTable::IdTable()
	{
		noname_lexema_count = 0;
		maxsize = TI_MAXSIZE;
		size = 0;
		table = new Entry[TI_MAXSIZE];
		literalCount = 0;
		funCount = 0;
		varCount = 0;
	}
	Entry::Entry()
	{
		//parrent_function[0] = '\0';
		id[0] = '\0';
		//uId[0] = '\0';
		firstApi = 0;
		iddatatype = IT::IDDATATYPE::DEF;
		idtype = IT::IDTYPE::D;
		str_number = 0;
		refCount = 0;
		//indexPF = 0;
	}
	void Entry::AddParm(IDDATATYPE iddatatype)
	{
		value.parm.type[value.parm.parmQuantity++] = iddatatype;
		if(value.parm.parmQuantity >= TI_MAX_COUNT_PARM)
			throw ERROR_THROW_IN(132, this->str_number, -1);
	}

	Entry::Entry(const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, int str_number)
	{
		int i = 0;
		//this->parrent_function[0] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
			{
				this->id[i] = id[i];
			//	this->uId[i] = id[i];
			}
		if (idtype == F || idtype == DF)
			value.parm.parmQuantity = 0;
		//delete(id);
		this->str_number = str_number;
		this->firstApi = first;
		this->id[i] = '\0';
		//this->uId[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->refCount = 0;
		//indexPF = 0;
	}

	Entry::Entry(const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, const char* ch, int str_number)
	{
		int i = 0;
		//this->parrent_function[0] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
			{
				this->id[i] = id[i];
				//this->uId[i] = '\0';
			}
		this->str_number = str_number;
		this->firstApi = first;
		this->id[i] = '\0';
		//this->uId[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		refCount = 0;
		//strcpy_s(this->value.vstr.str, 255, ch);
		if (iddatatype == STR || iddatatype == BOOL)
		{
			this->value.vstr.len = strlen(ch);
			for (i = 0; i < value.vstr.len; i++)
				value.vstr.str[i] = ch[i];
			value.vstr.str[i] = '\0';
		}
		
		//indexPF = 0;
	}

	IdTable Create(int size)
	{
		IdTable id_table;
		id_table.size = size;
		id_table.maxsize = TI_MAXSIZE;
		id_table.table = new Entry[TI_MAXSIZE];
		return id_table;
	}
	
	void IdTable::Add(Entry entry)
	{
		if (strlen(entry.id) > ID_MAXSIZE && entry.idtype != IDTYPE::F)
			throw ERROR_THROW(65);

		if(size >= maxsize)
			throw ERROR_THROW(66);
		table[size ++] = entry;
	}
	Entry IdTable::GetEntry(int n)
	{
		if (n >= 0 && n < maxsize)
			return table[n];
	}
	int IdTable::IsFirstApi(int FirstApi)
	{
		for (int i = 0; i < size; i++)
			if (table[i].firstApi == FirstApi)
				return i;

		return TI_NULLIDX;
	}
	int IdTable::IsId(const char id[ID_MAXSIZE])
	{
		for (int i = 0; i < size; i++)
			if (strcmp(table[i].id, id) == 0)
				return i;

		return TI_NULLIDX;
	}
	

	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
		idtable.table = nullptr;
	}

	char* IdTable::GetLexemaName()
	{
		char buffer[5];
		_itoa_s(noname_lexema_count, buffer, 10);
		strcat_s(buffer, 5, "_l");
		noname_lexema_count++;
		return buffer;
	}

	void IdTable::PrintIdTable(std::ofstream &idStream)
	{

		if (!idStream.is_open())
			throw ERROR_THROW(63);

		idStream << "------------------ Литералы ------------------" << endl;
		idStream << setw(15) << "Идентификатор:" << setw(17) << "Тип данных:" << setw(15) << "Значение:" << setw(27) << "Длина строки:" << setw(27) << "Первое вхождение:" << endl;

		for (int i = 0; i < size; i++)
		{
			if (table[i].idtype == IT::IDTYPE::L)
			{
				idStream << setw(4) << i << "  " << this->table[i].id << setw(17);
				cout.width(25);
				switch (table[i].iddatatype)
				{
				case BYTE:
					idStream << "BYTE " << setw(15);
					break;
				case IDDATATYPE::INT:
					idStream  << "INT " << setw(15) ;
					break;
				case IDDATATYPE::STR:
					idStream << "STR " << setw(15); 
					break;
				case IDDATATYPE::BOOL:
					idStream << "BOOL " << setw(15);
					break;
				}
				if (table[i].iddatatype == BYTE || table[i].iddatatype == INT)
					idStream << table[i].value.vint << setw(27) << "-" << setw(27) << table[i].firstApi << endl;
				else
					idStream << table[i].value.vstr.str << setw(27) << (int)table[i].value.vstr.len << setw(27) << table[i].firstApi << endl;
			}	
		}

		idStream << "\n\n\n";
		idStream << "------------------ Функции ------------------" << endl;
		idStream << setw(15) << "Идентификатор:" << setw(26) << "Тип данных возврата:" << setw(36) << "Количество переданных параметров:" << setw(22) << "Первое вхождение:"  << setw(22) << "параметры" << endl;

		for (int i = 0; i < size; i++)
		{
			if (this->table[i].idtype == IT::IDTYPE::F || this->table[i].idtype == IT::IDTYPE::DF)
			{
				idStream << setw(4) << i << "  " << table[i].id << setw(28 - strlen(table[i].id));
				switch (table[i].iddatatype)
				{
				case BYTE:
					idStream << "BYTE " << setw(36);
					break;
				case INT:
					idStream  << "INT " << setw(36);
					break;
				case IDDATATYPE::STR:
					idStream << "STR " << setw(36) ;
					break;
				case BOOL:
					idStream  << "BOOL " << setw(36);
					break;
				case NODEF:
					idStream  << "NODEF  " << setw(36);
					break;
				case HTMLOBJ:
					idStream << "HTMLOBJ  " << setw(36);
					break;
				}
				idStream << table[i].value.parm.parmQuantity << setw(22) << table[i].firstApi << setw(10);
				for (int j = 0; j < table[i].value.parm.parmQuantity; j++)
				{
					switch (table[i].value.parm.type[j])
					{
					case INT:
						idStream << "INT ";
						break;
					case STR:
						idStream << "STR ";
						break;
					case BOOL:
						idStream << "BOOL ";
						break;
					case HTMLOBJ:
						idStream << "HTMLOBJ ";
						break;
					case IDDATATYPE::NODEF:
						idStream << "NODEF ";
						break;
					}
				}
				idStream << endl;
			}
		}
		idStream << "\n\n\n";
		idStream << "------------------ Переменные ------------------" << endl;
		idStream << setw(25) << "Имя окружения:" << setw(20) << "Идентификатор:" << setw(16) << "Тип данных:" << setw(24) << "Тип идентификатора:" << setw(21) << "Первое вхождение:" << endl;

		for (int i = 0; i < size; i++)
		{
			//idStream << i << " ";
			if (table[i].idtype == IT::IDTYPE::V || table[i].idtype == IT::IDTYPE::P)
			{
				idStream << setw(4) << i;
				idStream << setw(18) << table[i].indEnv->name << setw(20) << table[i].id << setw(20);
				switch (table[i].iddatatype)
				{
				case BYTE:
					idStream << "BYTE " << setw(36);
					break;
				case IDDATATYPE::INT:
					idStream << "INT " << setw(15);
					break;
				case IDDATATYPE::STR:
					idStream << "STR " << setw(15);
					break;
				case IDDATATYPE::BOOL:
					idStream << "BOOL " << setw(15);
					break;
				case IDDATATYPE::HTMLOBJ:
					idStream << "HTMLOBJ " << setw(15);
					break;
				}
				if(table[i].idtype == IT::V)
					idStream << "V" ;
				else
					idStream << "P";
				idStream << setw(21) << table[i].firstApi << endl;
			}
		}

		idStream << "\n\n\n";
	}
}