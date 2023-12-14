#include "OperatorTable.h"
#include "Error.h"

namespace OT
{
	

	OEntry::OEntry(const char* opr, int oPriority)
	{
		this->oPriority = oPriority;
		int i = 0;
		while (opr[i] != '\0')
		{
			this->opr[i] = opr[i];
			i++;
			if (i >= MAXOPRSIZE)
				throw ERROR_THROW(37);
		}
		this->opr[i] = '\0';
	}
	
	OEntry::OEntry()
	{
		this->oPriority = -10;
		opr[0] = '\0';
	}

	void Table::Add(std::string opr, OEntry el)
	{
		table[opr] = el;
	}
	OEntry* Table::Get(std::string opr)
	{
		auto search = table.find(opr);
		if (search != table.end()) {
			return& search->second;
		}
		else {
			throw ERROR_THROW(37);
		}
	}

	void InitOprTable(Table& table)
	{
		table.Add("+", OEntry("+", 2));
		table.Add("-", OEntry("-", 2));
		table.Add("*", OEntry("*", 3));
		table.Add("/", OEntry("/", 3));
		table.Add("<", OEntry("<", 1));
		table.Add(">", OEntry(">", 1));
		table.Add("<=", OEntry("<=", 1));
		table.Add("=>", OEntry("=>", 1));
		table.Add("=", OEntry("=", 0));
	}
}