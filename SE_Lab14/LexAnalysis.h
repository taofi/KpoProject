#pragma once
#include "stdafx.h"

#define token_size 256

namespace LA
{
	struct TypeOfVar
	{
		int LT_posititon = -1;
		enum { DEF = 0, INT = 1, STR = 2 } type = DEF;
	};

	bool AnalyzeIdentifier(char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable, TypeOfVar& flag_type_variable);
	void LexicalAnalyzer(const In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable);
	bool AnalyzeToken(char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable);
}
