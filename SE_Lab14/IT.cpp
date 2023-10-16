#include "stdafx.h"

namespace IT
{
	IdTable::IdTable()
	{
		noname_lexema_count = 0;
		maxsize = TI_MAXSIZE;
		size = 0;
		table = new Entry[TI_MAXSIZE];
	}
	Entry::Entry()
	{
		parrent_function[0] = '\0';
		id[0] = '\0';
		idxfirstLE = 0;
		iddatatype = IT::IDDATATYPE::DEF;
		idtype = IT::IDTYPE::D;
		parmQuantity = 0;
	}

	Entry::Entry(const char* parrent_function, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->idxfirstLE = first;
		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
	}
	Entry::Entry(const char* parrent_function, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, int it)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->idxfirstLE = first;
		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
		this->value.vint = it;
	}
	Entry::Entry(const char* parrent_function, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, char* ch)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->idxfirstLE = first;
		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
		strcpy_s(this->value.vstr->str, 255, ch);
		this->value.vstr->len = strlen(ch);
	}
	Entry::Entry(const char* parrent_function, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, const char* ch)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->idxfirstLE = first;
		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
		strcpy_s(this->value.vstr->str, 255, ch);
		this->value.vstr->len = strlen(ch);
	}
	Entry::Entry(char* parrent_function, char* id, IDDATATYPE iddatatype, IDTYPE idtype)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
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

		if (size >= maxsize)
			throw ERROR_THROW(66);

		if (entry.idtype != IDTYPE::F)
			entry.id[5] = '\0';

		table[size] = entry;

		switch (entry.iddatatype)
		{
		case IDDATATYPE::INT:
		{
			table[size].value.vint = TI_INT_DEFAULT;
			break;
		}
		case IDDATATYPE::STR:
		{
			table[size].value.vstr->str[0] = TI_STR_DEFAULT;
			table[size].value.vstr->len = 0;
			break;
		}
		}

		size++;
	}
	Entry IdTable::GetEntry(int n)
	{
		if (n >= 0 && n < maxsize)
			return table[n];
	}
	int IdTable::IsId(const char id[ID_MAXSIZE])
	{
		for (int i = 0; i < size; i++)
			if (strcmp(table[i].id, id) == 0)
				return i;

		return TI_NULLIDX;
	}
	int IdTable::IsId(const char id[ID_MAXSIZE], const char parrent_function[ID_MAXSIZE + 5])
	{
		for (int i = 0; i < size; i++)
			if ((strcmp(this->table[i].id, id) == 0) &&
				(strcmp(this->table[i].parrent_function, parrent_function) == 0))
				return i;

		return TI_NULLIDX;
	}
	void IdTable::Delete()
	{
		delete[] table;
		table = nullptr;
	}

	char* IdTable::GetLexemaName()
	{
		char buffer[5];
		_itoa_s(noname_lexema_count, buffer, 10);
		strcat_s(buffer, 5, "_l");
		noname_lexema_count++;
		return buffer;
	}
	void IdTable::PrintIdTable(const wchar_t* inFile)
	{
		ofstream idStream(inFile);

		if (!idStream.is_open())
			throw ERROR_THROW(64);


		idStream << "##########################################################################################################################" << endl;
		idStream << "------------------ Литералы ------------------" << endl;
		idStream << setw(15) << "Идентификатор:" << setw(17) << "Тип данных:" << setw(15) << "Значение:" << setw(27) << "Длина строки:" << setw(20) << "Первое вхождение:" << endl;

		for (int i = 0; i < size; i++)
		{
			if (table[i].idtype == IT::IDTYPE::L)
			{
				cout.width(25);
				switch (table[i].iddatatype)
				{
				case IDDATATYPE::INT:
					idStream << "   " << this->table[i].id << "\t\t\t" << "INT " << "\t\t" << table[i].value.vint << "\t\t\t" << "-\t\t" << table[i].idxfirstLE<< endl;
					break;
				case IDDATATYPE::STR:
					idStream << "   " << this->table[i].id << "\t\t\t" << "STR " << "\t    " << table[i].value.vstr->str << setw(30 - strlen(table[i].value.vstr->str)) << (int)table[i].value.vstr->len << "\t\t" << table[i].idxfirstLE << endl;
					break;
				}
			}
		}

		idStream << "\n\n\n";

		idStream << "##########################################################################################################################" << endl;
		idStream << "------------------ Функции ------------------" << endl;
		idStream << setw(15) << "Идентификатор:" << setw(26) << "Тип данных возврата:" << setw(36) << "Количество переданных параметров:" << setw(22) << "Первое вхождение:" << endl;

		for (int i = 0; i < size; i++)
		{
			if (this->table[i].idtype == IT::IDTYPE::F)
			{
				switch (table[i].iddatatype)
				{
				case IDDATATYPE::INT:
					idStream << "   " << table[i].id << setw(28 - strlen(table[i].id)) << "INT " << "\t\t\t\t" << table[i].parmQuantity << "\t\t\t\t" << table[i].idxfirstLE << endl;
					break;
				case IDDATATYPE::STR:
					idStream << "   " << table[i].id << setw(28 - strlen(table[i].id)) << "STR " << "\t\t\t\t" << table[i].parmQuantity << "\t\t\t\t" << table[i].idxfirstLE << endl;
					break;
				}
			}
		}
		idStream << "\n\n\n";
		idStream << "##########################################################################################################################" << endl;
		idStream << "------------------ Переменные ------------------" << endl;
		idStream << setw(25) << "Имя родительского блока:" << setw(20) << "Идентификатор:" << setw(16) << "Тип данных:" << setw(24) << "Тип идентификатора:" << setw(21) << "Первое вхождение:" << endl;

		for (int i = 0; i < size; i++)
		{
			if (table[i].idtype == IT::IDTYPE::V)
			{
				switch (table[i].iddatatype)
				{
				case IDDATATYPE::INT:
					idStream << "   " << table[i].parrent_function << setw(35 - strlen(table[i].parrent_function)) << table[i].id << setw(20) << "INT " << setw(15) << "V" << "\t\t\t" << table[i].idxfirstLE << endl;
					break;
				case IDDATATYPE::STR:
					idStream << "   " << table[i].parrent_function << setw(35 - strlen(table[i].parrent_function)) << table[i].id << setw(20) << "STR " << setw(15) << "V" << "\t\t\t" << table[i].idxfirstLE << endl;
					break;
				}
			}

			if (table[i].idtype == IT::IDTYPE::P)
			{
				switch (table[i].iddatatype)
				{
				case IDDATATYPE::INT:
					idStream << "   " << table[i].parrent_function << setw(35 - strlen(table[i].parrent_function)) << table[i].id << setw(20) << "INT " << setw(15) << "P" << "\t\t\t" << table[i].idxfirstLE << endl;
					break;

				case IDDATATYPE::STR:
					idStream << "   " << table[i].parrent_function << setw(35 - strlen(table[i].parrent_function)) << table[i].id << setw(20) << "STR " << setw(15) << "P" << "\t\t\t" << table[i].idxfirstLE << endl;
					break;
				}
			}
		}

		idStream << "\n\n\n";

		idStream.close();
	}

}