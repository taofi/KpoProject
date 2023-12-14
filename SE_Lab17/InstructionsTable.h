#pragma once
#define INSTTABLESIZE 255

#include "FST.h"


namespace INSTTB
{
	enum WORDTYPE { NODEF = -1, WORD = 0, LEX, IND, OPR, SPR, NOTA};
	struct Entry {
		char lexem; //лексема в которую переводится цепочка
		char id;	//index в таблице (первый символ эллемента)
		int nodeCount; //количество узлов
		WORDTYPE type;
		FST::NODE* nodes; //узлы конечного автомата
		Entry* next; //следующий эллемент таблицы
		Entry(char l, const char* str, WORDTYPE type, int notation); //создание конечного автомата для систем счисления
		Entry(char l, const char* str, WORDTYPE type);//создание конечного автомата для слов
		Entry(char id);//индитификаторы
	};

	struct FSTGen {
		char lex; //лексема
		char* analizStr;
		WORDTYPE type;
		Entry* next; //следующая цепочка если эта не пойдет 
		FST::FST fst; //конечный автомат
		//WORDTYPE type;
		FSTGen(char lex, char* analizStr, FST::FST fst, Entry* next, WORDTYPE type);
		bool NextFst();
	};

	struct Table
	{
		Entry* table[INSTTABLESIZE]; //таблица 
		void Add(Entry* el);
		void DeleteTable();
		FSTGen GetFST(char index, char* analizStr);
	};
	void InitTable(Table& table);
	void DeleteEntry(Entry* el);
}