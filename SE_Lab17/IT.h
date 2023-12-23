#pragma once
#include "Environment.h"	
#include <string>
#include <fstream>
#define TI_MAXSIZE		4096				// ������������ ���������� ����� � ������� ���������������
#define TI_INT_DEFAULT  0x00000000			// �������� �� ��������� ��� ���� integer
#define TI_STR_DEFAULT  0x00				// �������� �� ��������� ��� ���� string
#define TI_NULLIDX		0xffffffff			// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE  255					// ������������ ����� ������


#define MAXSUFFIXSIZE 20
#define PARM_ID L".id.txt"


namespace IT								// ������� ��������������� 
{
	enum IDDATATYPE { NODEF = -1, DEF = 0, INT = 1, STR, BOOL, HTMLOBJ, BYTE};				// ���� ������
	enum IDTYPE { D, V, F, P, L, DF};			// ���� ���������������: ����������, �������, ��������, �������

	struct Entry							// ������ ������� ���������������
	{
		int str_number; //����� ������
		ENV::Environment* indEnv;						//������ �� ��������� ��������������
		int firstApi;									// ������ ������� ��������� � ������� ������
		int firstInit;
		char id[ID_MAXSIZE + MAXSUFFIXSIZE + 5];		// ������������� (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE iddatatype;							// ��� ������
		IDTYPE idtype;									// ��� ��������������
		union
		{
			int vint;									// �������� integer
			char operation = '\0';
			struct
			{
				unsigned char len;						// ���������� �������� � string
				char str[TI_STR_MAXSIZE];				// ������� string
			} vstr;						// �������� string
			struct
			{
				int parmQuantity;				//���������� ���������� 
				IDDATATYPE type[TI_MAX_COUNT_PARM];
			}parm;
		} value;						// �������� ��������������
		
		int refCount;					//��������� ������ �� �������������
		//void ChangeParrentFunction(const char* parrentFunc);
		void AddParm(IDDATATYPE iddatatype);
		Entry();
		Entry(const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, int str_number); 
		Entry(const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, const char* ch, int str_number);//��������� �������
	};

	struct IdTable							// ��������� ������� ���������������
	{
		int noname_lexema_count;				// ������� �������������������� ������
		int maxsize;							// ������� ������� ��������������� < TI_MAXSIZE
		int size;								// ������� ������ ������� ��������������� < maxsize
		int literalCount;
		int funCount;
		int varCount;
		Entry* table;							// ������ ����� ������� ���������������
		Entry GetEntry(							// �������� ������ ������� ���������������
			int n									// ����� ���������� ������
		);
		int IsId(								// �������: ����� ������ (���� ����), TI_NULLIDX(���� ���)
			const char id[ID_MAXSIZE]				// �������������
		);

		int IsFirstApi(int FirstApi);

		void Add(								// �������� ������ � ������� ��������������� 
			Entry entry								// ������ ������� ��������������
		);
		void PrintIdTable(std::ofstream& idStream);	// ����� ������� ���������������
		IdTable();
		char* GetLexemaName();
	};


	void Delete(IdTable& idtable);			// ������� ������� ������ (���������� ������)
};

