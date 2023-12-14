#pragma once
#include "LT.h"
#include "IT.h"
#include "LexAnalysis2.h"
#define LITERALMAXCODE 255


namespace GEN 
{
	enum LEXTYPE { NODEF = -1, IGNR = 0, DIRCT = 1, INDF = 2, OPRT = 3, SEMICLN = 4, RIGHTBR = 5}; //тип литтерала в таблице генератора

	struct Entry
	{
		const char* JsLex;
		LEXTYPE lexType;
		Entry();
		Entry(LEXTYPE type);
		Entry(const char* JsLex, LEXTYPE type);
		void Delete();
	};
	void TableInit();
	void Generator(LEXA::Tables& tables, wchar_t outfile[]);
	//char* IdentifierGen(int index, LT::LexTable& lexTable, IT::IdTable& idTable);
	//void concatOut(const char* str1, const char* str2, std::ofstream& file);
}