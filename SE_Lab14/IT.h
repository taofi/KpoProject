#pragma once
#define ID_MAXSIZE		5
#define TI_MAXSIZE		4096
#define TI_INT_DEFAULT	0x00000000
#define TI_STR_DEFAULT	0x00
#define TI_NULLIDX		0xffffffff
#define TI_STR_MAXSIZE	255

namespace IT {

	enum IDDATATYPE { DEF = 0, INT = 1, STR = 2};// ���� ������ ����������������: integer , string
	enum IDTYPE { D = 0, V = 1, F = 2, P = 3, L = 4 };    // ���� ���������������: ����������, �������, ��������, �������

	struct Entry {
		char parrent_function[ID_MAXSIZE + 5];			// ������������� ������������ �������
		int idxfirstLE;									// ������ ������ ������ � ������� ������
		char id[ID_MAXSIZE];					// �������������
		IDDATATYPE iddatatype;					// ��� ������
		IDTYPE idtype;							// ��� ��������������
		union Value
		{
			int vint;							// �������� integer
			struct
			{
				int len;						// ���������� �������� � string
				char str[TI_STR_MAXSIZE - 1];	// c������ string
			}vstr[TI_STR_MAXSIZE];				// �������� string
		}value;									 // �������� ��������������
		int parmQuantity;
		Entry();
		Entry(const char* parrentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first);
		Entry(const char* parrentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, int it);
		Entry(const char* parrentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, char* str);
		Entry(const char* parrentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, const char* str);
		Entry(char* parrentFunc, char* id, IDDATATYPE iddatatype, IDTYPE idtype);
	};

	struct IdTable
	{
		int maxsize;
		int size;
		int noname_lexema_count;
		Entry* table;

		IdTable Create(int size);

		void Add( Entry entry);

		Entry GetEntry(int n);
		IdTable();
		int IsId(const char id[ID_MAXSIZE]);		// ���� �� �������������� � �������
		int IsId(const char id[ID_MAXSIZE], const char parrent_function[ID_MAXSIZE + 5]);
		char* GetLexemaName();
		void Delete();
		void PrintIdTable(const wchar_t* inFile);
	};

	
}