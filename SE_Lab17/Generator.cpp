#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>

#include "Generator.h"


namespace GEN 
{
	
	Entry::Entry(const char* JsLex, LEXTYPE type) 
	{
		this->JsLex = JsLex;
		this->lexType = type;
	}
	Entry::Entry(LEXTYPE type)
	{
		this->lexType = type;
	}
	Entry::Entry()
	{
		this->lexType = NODEF;
	}
	void Entry::Delete()
	{
		delete(this->JsLex);
	}

	Entry genTable[LITERALMAXCODE];
	void TableInit()
	{
		//std::cout << (int)LEX_FUNCTION << std::endl;
		for (int i = 0; i < LITERALMAXCODE; i++)
			genTable[i] = {};
		genTable[LEX_FUNCTION] = { IGNR};
		genTable[LEX_COMMA] = {" , ", DIRCT};
		genTable[LEX_DECLARE] = { IGNR };
		genTable[LEX_DATATYPE] = { IGNR };
		genTable[LEX_EQUAL_SIGN] = { " = ", DIRCT };
		genTable[LEX_ID] = { INDF };
		genTable['w'] = {"while", DIRCT};
		genTable[LEX_LEFTBRACE] = { "{\n", DIRCT };
		genTable[LEX_LEFTHESIS] = { "( ", DIRCT };
		genTable[LEX_MAIN] = { "function main() ", DIRCT };
		genTable[LEX_RETURN] = { "return ", DIRCT };
		genTable[LEX_RIGHTBRACE] = { "}\n", RIGHTBR };
		genTable[LEX_RIGHTHESIS] = { " )", DIRCT };
		genTable[LEX_SEMICOLON] = { ";\n", SEMICLN };
		genTable[PLUS] = { " + ", DIRCT };
		genTable[MINUS] = { " - ", DIRCT };
		genTable[LEX_OPERATOR] = { OPRT };
		genTable[LEX_LITERAL] = { INDF };
	}

	void Generator(LEXA::Tables& tables, wchar_t outfile[])
	{
		std::ofstream file(outfile);
		TableInit();
		for (int i = 0; i < tables.fTable.size; i++)
		{
			if(tables.idTable.table[i].refCount != 0)
				file << tables.fTable.inJsCode[i];
		}

		bool wasIgnoredVar = false;
		bool wasIgnoredFun = false;
		for (int i = 0; i < tables.LexTable.size; i++)
		{
			if (genTable[tables.LexTable.table[i].lexema].lexType == IGNR)
				continue;
			if (genTable[tables.LexTable.table[i].lexema].lexType == RIGHTBR)
			{
				if (wasIgnoredFun)
					wasIgnoredFun = false;
				else
					file << genTable[tables.LexTable.table[i].lexema].JsLex;
			}
			if (wasIgnoredFun)
				continue;
			if (genTable[tables.LexTable.table[i].lexema].lexType == SEMICLN)
			{
				if (wasIgnoredVar)
					wasIgnoredVar = false;
				else
					file << genTable[tables.LexTable.table[i].lexema].JsLex;
			}
			if (wasIgnoredVar)
				continue;
			if (genTable[tables.LexTable.table[i].lexema].lexType == DIRCT)
			{
				file << genTable[tables.LexTable.table[i].lexema].JsLex;
			}
			else if (genTable[tables.LexTable.table[i].lexema].lexType == INDF)
			{
				IT::Entry ITEntry = tables.idTable.table[tables.LexTable.table[i].idxTI];
				//std::cout << ITEntry.id << " " << ITEntry.refCount << std::endl;
				if (ITEntry.idtype == IT::IDTYPE::P)
				{
					file << ITEntry.id;
				}
				else if (ITEntry.idtype == IT::IDTYPE::F)
				{
					if (ITEntry.firstApi == i)
					{
						if (ITEntry.indEnv == tables.global)
						{
							file << "function " << ITEntry.id;
						}
						else
							file << "let " << ITEntry.id << " = function";
						
					}
					else
					 file << ITEntry.id;
				}
				else if (ITEntry.idtype == IT::IDTYPE::V)
				{
					if (ITEntry.refCount == 0)
					{
						wasIgnoredVar = true;
						continue;
					}
					if (ITEntry.firstApi == i)
					{
						file << "let " << ITEntry.id;
						///*if (lexTable.table[i + 1].lexema == LEX_EQUAL_SIGN);	
						//	continue;
						//if (ITEntry.iddatatype == IT::NODEF)
						//	continue;*/
						//else 
						if (ITEntry.iddatatype == IT::INT && tables.LexTable.table[i + 1].lexema == LEX_SEMICOLON)
							file << " = 0";
						else if(ITEntry.iddatatype == IT::STR && tables.LexTable.table[i + 1].lexema == LEX_SEMICOLON)
							file << " = ''";
					}
					else
						file << ITEntry.id;
				}
				else if (ITEntry.idtype == IT::IDTYPE::L)
				{
					if(ITEntry.iddatatype == IT::INT)
						file << ITEntry.value.vint;
					else if(ITEntry.iddatatype == IT::STR || ITEntry.iddatatype == IT::BOOL)
						file << ITEntry.value.vstr.str;
				}
				
			}
			else if(genTable[tables.LexTable.table[i].lexema].lexType == OPRT)
			{
				file  << " " << tables.LexTable.table[i].opr->opr << " ";
			}
		}


		file << "\nmain();";
		file.close();
	}

}