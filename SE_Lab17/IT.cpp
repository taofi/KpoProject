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
		indexPF = 0;
	}
	void Entry::AddParm(IDDATATYPE iddatatype)
	{
		value.parm.type[value.parm.parmQuantity++] = iddatatype;
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
		indexPF = 0;
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
		else if (iddatatype == INT)
		{
			value.vint = 0;
			int size = strlen(ch);
			for (int i = 0; i < size; i++)
			{
				value.vint += (ch[i] - '0') * pow(10, size - i - 1);
			}
		}
		
		indexPF = 0;
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

	void IdTable::PrintIdTable(const wchar_t* inFile)
	{
		ofstream idStream(inFile);

		if (!idStream.is_open())
			throw ERROR_THROW(64);

		idStream << "------------------ �������� ------------------" << endl;
		idStream << setw(15) << "�������������:" << setw(17) << "��� ������:" << setw(15) << "��������:" << setw(27) << "����� ������:" << setw(27) << "������ ���������:" << endl;

		for (int i = 0; i < size; i++)
		{
			if (table[i].idtype == IT::IDTYPE::L)
			{
				idStream << setw(4) << i << "  ";
				cout.width(25);
				switch (table[i].iddatatype)
				{
				case IDDATATYPE::INT:
					idStream << this->table[i].id << setw(17) << "INT " << setw(15) << table[i].value.vint << setw(27) << "-" << setw(27) << table[i].firstApi << endl;
					break;
				case IDDATATYPE::STR:
					idStream << this->table[i].id << setw(17) << "STR " << setw(15) << table[i].value.vstr.str << setw(27) << (int)table[i].value.vstr.len << setw(27) << table[i].firstApi << endl;
					break;
				case IDDATATYPE::BOOL:
					idStream << this->table[i].id << setw(17) << "BOOL " << setw(15) << table[i].value.vstr.str << setw(27) << (int)table[i].value.vstr.len << setw(27) << table[i].firstApi << endl;
					break;
				}
			}
		}

		idStream << "\n\n\n";
		idStream << "------------------ ������� ------------------" << endl;
		idStream << setw(15) << "�������������:" << setw(26) << "��� ������ ��������:" << setw(36) << "���������� ���������� ����������:" << setw(22) << "������ ���������:"  << setw(22) << "���������" << endl;

		for (int i = 0; i < size; i++)
		{
			if (this->table[i].idtype == IT::IDTYPE::F || this->table[i].idtype == IT::IDTYPE::DF)
			{
				idStream << setw(4) << i << "  ";
				switch (table[i].iddatatype)
				{
				case IDDATATYPE::INT:
					idStream << table[i].id << setw(28 - strlen(table[i].id)) << "INT " << setw(36) << table[i].value.parm.parmQuantity << setw(22) << table[i].firstApi << setw(10);
					break;
				case IDDATATYPE::STR:
					idStream << table[i].id << setw(28 - strlen(table[i].id)) << "STR " << setw(36) << table[i].value.parm.parmQuantity << setw(22) << table[i].firstApi << setw(10);
					break;
				case BOOL:
					idStream << table[i].id << setw(28 - strlen(table[i].id)) << "BOOL " << setw(36) << table[i].value.parm.parmQuantity << setw(22) << table[i].firstApi << setw(10);
					break;
				case NODEF:
					idStream << table[i].id << setw(28 - strlen(table[i].id)) << "NODEF  " << setw(36) << table[i].value.parm.parmQuantity << setw(22) << table[i].firstApi << setw(10);
					break;
				}
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
					case IDDATATYPE::NODEF:
						idStream << "NODEF ";
						break;
					}
				}
				idStream << endl;
			}
		}
		idStream << "\n\n\n";
		idStream << "------------------ ���������� ------------------" << endl;
		idStream << setw(25) << "��� ������������� �����:" << setw(20) << "�������������:" << setw(16) << "��� ������:" << setw(24) << "��� ��������������:" << setw(21) << "������ ���������:" << endl;

		for (int i = 0; i < size; i++)
		{
			//idStream << i << " ";
			if (table[i].idtype == IT::IDTYPE::V)
			{
				idStream << setw(4) << i;
				switch (table[i].iddatatype)
				{
				case IDDATATYPE::INT:
					idStream<< setw(18) << table[i].indEnv->name << setw(20) << table[i].id << setw(20) << "INT " << setw(15) << "V" << setw(21) << table[i].firstApi << endl;
					break;
				case IDDATATYPE::STR:
					idStream << setw(18) << table[i].indEnv->name << setw(20) << table[i].id << setw(20) << "STR " << setw(15) << "V" << setw(21) << table[i].firstApi << endl;
					break;
				}
			}

			if (table[i].idtype == IT::IDTYPE::P)
			{
				idStream << setw(4) << i;
				switch (table[i].iddatatype)
				{
				case IDDATATYPE::INT:
					idStream << setw(18) << table[i].indEnv->name << setw(20) << table[i].id << setw(20) << "INT " << setw(15) << "P" << setw(21) << table[i].firstApi << endl;
					break;
				
				case IDDATATYPE::STR:
					idStream << setw(18) << table[i].indEnv->name << setw(20) << table[i].id << setw(20) << "STR " << setw(15) << "P" << setw(21) << table[i].firstApi << endl;
					break;
				}
			}
		}

		idStream << "\n\n\n";

		idStream.close();
	}
}