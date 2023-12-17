#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Error.h"
#include "InstructionsTable.h"
#define ALPHABETSIZE 94
#define ALPHABETNOTATIONSIZE 37
#define ALPHOBETIDSIZE 63

char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*\\()- _=+:;<>,./'?\\{}[]\n";
char alphabetid[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
char alphabetNotation[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
FST::NODE* nodeid;
FST::NODE* nodevar;
FST::NODE* nodealph;


namespace INSTTB
{
	Entry::Entry(char l, const char* str, WORDTYPE type)
	{
		if (l >= INSTTABLESIZE)
			throw ERROR_THROW(30);
		this->type = type;
		this->lexem = l;
		this->id = str[0];
		this->nodeCount = strlen(str) + 1;
		if (str[0] >= '0' && str[0] <= '9')
		{
			nodes = nodevar;
			nodeCount = 1;
		}
		else if (str[0] == '\'')
		{
			nodes = nodealph;
			nodeCount = 3;
		}
		else
		{
			nodes = new FST::NODE[nodeCount];
			for (int i = 0; i < nodeCount - 1; i++)
				nodes[i] = FST::NODE(1, FST::RELATION(str[i], i + 1));
			nodes[nodeCount - 1] = FST::NODE();
		}
		
		this->next = nullptr;
	}
	Entry::Entry(char l, const char* str, WORDTYPE type, int notation)
	{
		if (l >= INSTTABLESIZE)
			throw ERROR_THROW(30);
		this->type = type;
		this->lexem = l;
		this->id = str[0];
		this->nodeCount = strlen(str) + 2;
		this->next = nullptr;
		if (nodeCount > 6)
			throw ERROR_THROW(30);
		nodes = new FST::NODE[nodeCount];
		for (int i = 0; i < nodeCount - 2; i++)
			nodes[i] = FST::NODE(1, FST::RELATION(str[i], i + 1));
		FST::RELATION rel[ALPHABETNOTATIONSIZE];
		if(notation >= ALPHABETNOTATIONSIZE || notation <= 1)
			throw ERROR_THROW(30);
		nodeCount--;
		for (int i = 0; i < notation; i++)
			rel[i] = FST::RELATION(alphabetNotation[i], nodeCount - 1);
		nodes[nodeCount - 1] = FST::NODE(notation, rel);

		nodes[nodeCount] = FST::NODE();
	}
	Entry::Entry(char id)
	{
		if(id >= INSTTABLESIZE)
			throw ERROR_THROW(30);
		this->type = NODEF;
		this->lexem = 'i';
		this->id = id;
		this->nodeCount = 1;
		nodes = nodeid;
		next = nullptr;
	}

	FSTGen::FSTGen(char lex, char* analizStr, FST::FST fst, Entry* next, WORDTYPE type)
	{
		this->lex = lex;
		this->type = type;
		this->analizStr = analizStr;
		this->next = next;
		this->fst = fst;
	}

	bool FSTGen::NextFst()
	{
		if (this->next == nullptr)
			return false;
		Entry* temp = this->next;
		this->lex = temp->lexem;
		this->next = temp->next;
		this->type = temp->type;
		this->fst = FST::FST(this->analizStr, temp->nodeCount, temp->nodes);
		return true;
	}

	FSTGen Table::GetFST(char index, char* analizStr)
	{
		return FSTGen(table[index]->lexem, analizStr, FST::FST(analizStr, table[index]->nodeCount, table[index]->nodes), table[index]->next, table[index]->type);
	}

	void Table::Add(Entry* el)
	{
		Entry* temp = table[el->id];
		el->next = temp;
		table[el->id] = el;
	}

	void InitTable(Table& table)
	{
		nodeid = new FST::NODE[2];
		FST::RELATION relid[ALPHOBETIDSIZE];
		for (int i = 0; i < ALPHOBETIDSIZE; i++)
			relid[i] = FST::RELATION(alphabetid[i], 0);
		nodeid[0] = FST::NODE(ALPHOBETIDSIZE, relid);
		nodeid[1] = FST::NODE();

		nodealph = new FST::NODE[3];
		FST::RELATION relalp[ALPHABETSIZE + 1];
		nodealph[0] = FST::NODE(1, FST::RELATION('\'', 1));
		for (int i = 0; i < ALPHABETSIZE; i++)
			relalp[i] = FST::RELATION(alphabet[i], 1);
		relalp[ALPHABETSIZE] = FST::RELATION('\'', 2);
		nodealph[1] = FST::NODE(ALPHABETSIZE + 1, relalp);
		nodealph[2] = FST::NODE();

		nodevar = new FST::NODE[2];
		FST::RELATION relvar[10];
		for (int i = 0; i < 10; i++)
			relvar[i] = FST::RELATION('0' + i, 0);
		nodevar[0] = FST::NODE(10, relvar);
		nodevar[1] = FST::NODE();

		for (int i = 0; i < INSTTABLESIZE; i++)
			table.table[i] = new Entry((char)i);
		table.Add(new Entry('l', "''", LEX));
		table.Add(new Entry('l', "1", LEX));
		table.Add(new Entry('l', "2", LEX));
		table.Add(new Entry('l', "3", LEX));
		table.Add(new Entry('l', "4", LEX));
		table.Add(new Entry('l', "5", LEX));
		table.Add(new Entry('l', "6", LEX));
		table.Add(new Entry('l', "7", LEX));
		table.Add(new Entry('l', "8", LEX));
		table.Add(new Entry('l', "9", LEX));
		table.Add(new Entry('l', "0", LEX));
		table.Add(new Entry('l', "16x", NOTA, 16));
		table.Add(new Entry('l', "8x", NOTA, 8));
		table.Add(new Entry('l', "2x", NOTA, 2));
		table.Add(new Entry('l', "true\0", LEX));
		table.Add(new Entry('l', "false\0", LEX));
		table.Add(new Entry('f', "function\0", WORD));
		table.Add(new Entry('t', "string\0", WORD));
		table.Add(new Entry('t', "number\0", WORD));
		table.Add(new Entry('t', "htmlobj\0", WORD));
		table.Add(new Entry('t', "nodef\0", WORD));
		table.Add(new Entry('t', "bool\0", WORD));
		table.Add(new Entry('r', "return\0", WORD));
		table.Add(new Entry('w', "while\0", WORD));
		table.Add(new Entry('j', "if\0", WORD));
		table.Add(new Entry('e', "else\0", WORD));
		table.Add(new Entry('m', "main\0", IND));
		table.Add(new Entry('{', "{\0", SPR));
		table.Add(new Entry('}', "}\0", SPR));
		table.Add(new Entry('(', "(\0", SPR));
		table.Add(new Entry(')', ")\0", SPR));
		table.Add(new Entry(';', ";\0", SPR));
		table.Add(new Entry(',', ",\0", SPR));
		table.Add(new Entry('v', "+\0", OPR));
		table.Add(new Entry('v', "-\0", OPR));
		table.Add(new Entry('v', "*\0", OPR));
		table.Add(new Entry('v', "/\0", OPR));
		table.Add(new Entry('v', "<\0", OPR));
		table.Add(new Entry('v', ">\0", OPR));
		table.Add(new Entry('=', "=\0", OPR));
		table.Add(new Entry('=', "!=\0", OPR));
		
	}
	
	void Table::DeleteTable()
	{
		for (int i = 0; i < INSTTABLESIZE; i++)
			DeleteEntry(table[i]);
		delete nodealph;
		delete nodeid;
		delete nodevar;
	}
	void DeleteEntry(Entry* el)
	{
		if (el != NULL)
			return;
		if(el->nodes != nodealph && el->nodes!=nodeid && el->nodes != nodevar)
			delete(el->nodes);
		DeleteEntry(el->next);
		delete(el);
	}

	
}