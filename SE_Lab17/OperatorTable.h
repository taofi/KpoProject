#pragma once
#include <map>
#include <string>
#define MAXOPRSIZE 20

namespace OT
{
	struct OEntry
	{
		char opr[MAXOPRSIZE];
		int oPriority;
		OEntry(const char* opr, int oPriority);
		OEntry();
	};
	struct Table
	{
		std::map<std::string, OEntry> table;
		void Add(std::string opr, OEntry el);
		OEntry* Get(std::string opr);
		
	};
	void InitOprTable(Table& table);
}