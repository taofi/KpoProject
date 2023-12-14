#pragma once
//#define WORDMAXSIZE 1000
#include <stack>
#include <string>
#include "In.h"
#include "LT.h"
#include"InstructionsTable.h"
#include "Environment.h"
#include "OperatorTable.h"
#include "IT.h"

namespace LEXA
{

	struct FunTable
	{
		int size;
		std::string inJsCode[TI_MAXSIZE];
	};

	
	struct Token
	{
		char word[TI_STR_MAXSIZE];
		int size;
		char id;
		INSTTB::WORDTYPE type;
		Token(char* word, INSTTB::WORDTYPE type);
		Token();
	};
	
	struct Tables
	{
		LT::LexTable LexTable;
		IT::IdTable  idTable;
		INSTTB::Table instTable;
		ENV::Environment* global;
		OT::Table oprTable;
		FunTable fTable;
		//Tables();
	};
	bool FSTExecute(INSTTB::FSTGen& fstg);
	void INDAnalyz(INSTTB::FSTGen& fstg, int strLine, Tables& tables);
	char* intToChar(int num);
	bool AnalyzeToken(Token& token, int strLine, Tables& tables);
	void LexicalAnalyzer(const In::IN& source, Tables& tables);
	void Delete(Tables& tables);
	void ChangeLastType(char ch, int strLine);
	void AddDecFun(LEXA::Tables& tables, const char* id, IT::IDDATATYPE funType, std::string js, int parmCount, IT::IDDATATYPE parmTypes...);
	void InitFunTable(Tables& tables);
	//Token ReadToken(int index, const In::IN& source);
}