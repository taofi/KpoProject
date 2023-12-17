#include "stdafx.h"

namespace LT
{
	LT::LexTable::LexTable()
	{
		maxsize = LT_MAXSIZE;
		size = 0;
		table = new Entry[LT_MAXSIZE];
	}

	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.size >= lextable.maxsize)
			throw ERROR_THROW(60);

		lextable.table[lextable.size++] = entry;
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
	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
		lextable.table = nullptr;
	}
	void LexTable::PrintLexTable(const wchar_t* in)
	{
		ofstream lexStream(in);

		if(!lexStream.is_open())
			throw ERROR_THROW(63);

		int num_string = 0;
		lexStream << ++num_string << " ";
		for (int i = 0; i < size;)
		{
			if (num_string == table[i].sn) {
				lexStream << table[i++].lexema;
				continue;
			}
			
			lexStream << '\n' << ++num_string << " ";
		}

		lexStream.close();
	}

	void LexTable::UnformattedPrintLexTable(const wchar_t* in)
	{
		ofstream lexStream(in);

		if (!lexStream.is_open())
			throw ERROR_THROW(63);
		lexStream << setw(3) << "i" << "|" << setw(3) << "lex" << " | " << setw(2) << "TI" << " | " << " sn" << "\n";
		for (int i = 0; i < size; i++)
		{
			lexStream << setw(3) << i << "|" << setw(4) << table[i].lexema << "|" << setw(4)<< table[i].idxTI << "|" << setw(3) << table[i].sn <<"\n";
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
		opr = nullptr;
	}
	/*LT::Entry::Entry(const char lex, int str_n, int idxTI, char oSymbol)
	{
		lexema = lex;
		sn = str_n;
		this->idxTI = idxTI;
		this->oSymbol = oSymbol;
	}*/
}