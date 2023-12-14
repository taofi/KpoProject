#pragma once
#define INSTTABLESIZE 255

#include "FST.h"


namespace INSTTB
{
	enum WORDTYPE { NODEF = -1, WORD = 0, LEX, IND, OPR, SPR, NOTA};
	struct Entry {
		char lexem; //������� � ������� ����������� �������
		char id;	//index � ������� (������ ������ ���������)
		int nodeCount; //���������� �����
		WORDTYPE type;
		FST::NODE* nodes; //���� ��������� ��������
		Entry* next; //��������� �������� �������
		Entry(char l, const char* str, WORDTYPE type, int notation); //�������� ��������� �������� ��� ������ ���������
		Entry(char l, const char* str, WORDTYPE type);//�������� ��������� �������� ��� ����
		Entry(char id);//��������������
	};

	struct FSTGen {
		char lex; //�������
		char* analizStr;
		WORDTYPE type;
		Entry* next; //��������� ������� ���� ��� �� ������ 
		FST::FST fst; //�������� �������
		//WORDTYPE type;
		FSTGen(char lex, char* analizStr, FST::FST fst, Entry* next, WORDTYPE type);
		bool NextFst();
	};

	struct Table
	{
		Entry* table[INSTTABLESIZE]; //������� 
		void Add(Entry* el);
		void DeleteTable();
		FSTGen GetFST(char index, char* analizStr);
	};
	void InitTable(Table& table);
	void DeleteEntry(Entry* el);
}