#pragma once
#define LEXEMA_FIXSIZE 1
#define LT_MAXSIZE 4096
#define	LT_TI_NULLXDX	-1			// ��� �������� ������� ���������������	
#define	LEX_DATATYPE 't'			// ������� ��� ���� ������
#define	LEX_INTEGER	't'			// ������� ��� integer
#define	LEX_STRING 't'
#define LEX_ID 'i'
#define LEX_LITERAL 'l'
#define LEX_FUNCTION 'f'
#define LEX_DECLARE 'd'
#define LEX_RETURN 'r'
#define LEX_PRINT 'p'
#define LEX_SEMICOLON ';'
#define LEX_COMMA  ','
#define LEX_LEFTBRACE '{'
#define LEX_BRACELET '}'
#define LEX_LEFTHESIS '('
#define LEX_RIGHTHESIS ')'
#define LEX_PLUS 'v'
#define LEX_MINUS 'v'
#define LEX_STAR 'v'
#define LEX_DIRSLASH 'v'
#define	LEX_EQUAL_SIGN	'='			// ������� ��� =

#define PLUS '+'
#define MINUS '-'
#define STAR '*'
#define DIRSLASH '/'


namespace LT
{

	struct Entry
	{
		char lexema; // �������
		int sn;						// ����� ������
		int idxTI;					// ������ � ������� ������

		Entry();
		Entry(const char lex, int str_n, int idxTI);
	};

	struct LexTable
	{
		int maxsize;				 // ���� ������ ������� ������
		int size;					 // ������� ������
		Entry* table; 				 // ������ ����� ������� ������

		LexTable Create(int size);

		void Add(
			Entry entry					 // ������ ������� ������
		);

		Entry GetEntry(					 // �������� ������ � ������� ������
			int n						 // ����� ���������� ������			
		);

		void Delete(); // ������� ������� ������
		void PrintLexTable(const wchar_t* in);		// ����� ������� ������
		LexTable();
	};


	
};