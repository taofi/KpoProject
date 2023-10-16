#include "stdafx.h"

namespace LT
{
	LT::LexTable::LexTable()
	{
		maxsize = LT_MAXSIZE;
		size = 0;
		table = new Entry[LT_MAXSIZE];
	}

	void LexTable::Add(Entry entry)
	{
		if (size >= maxsize)
			throw ERROR_THROW(60);

		table[size++] = entry;
	}
	Entry LexTable::GetEntry(int n)
	{
		if (n >= 0 && n < maxsize)
			return table[n];
	}
	void LexTable::Delete()
	{
		delete[] table;
		table = nullptr;
	}
	void LexTable::PrintLexTable(const wchar_t* in)
	{
		ofstream lexStream(in);

		if (!lexStream.is_open())
			throw ERROR_THROW(63);

		int num_string = 0;

		for (int i = 0; i < size;)
		{
			if (num_string == table[i].sn) {
				lexStream << table[i++].lexema;
				continue;
			}

			lexStream << '\n' << ++num_string << ".\t";
		}

		lexStream.close();
	}

	LT::Entry::Entry()
	{
		lexema = '\0';
		sn = LT_TI_NULLXDX;
		idxTI = LT_TI_NULLXDX;
	}

	LT::Entry::Entry(const char lex, int str_n, int idxTI)
	{
		lexema = lex;
		sn = str_n;
		this->idxTI = idxTI;
	}
}