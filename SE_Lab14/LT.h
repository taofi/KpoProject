#pragma once
#define LEXEMA_FIXSIZE 1
#define LT_MAXSIZE 4096
#define	LT_TI_NULLXDX	-1			// нет элемента таблицы идентификаторов	
#define	LEX_DATATYPE 't'			// лексема для типа данных
#define	LEX_INTEGER	't'			// лексема для integer
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
#define	LEX_EQUAL_SIGN	'='			// лексема для =

#define PLUS '+'
#define MINUS '-'
#define STAR '*'
#define DIRSLASH '/'


namespace LT
{

	struct Entry
	{
		char lexema; // лексема
		int sn;						// номер строки
		int idxTI;					// индекс в таблице лексем

		Entry();
		Entry(const char lex, int str_n, int idxTI);
	};

	struct LexTable
	{
		int maxsize;				 // макс размер таблицы лексем
		int size;					 // текущий размер
		Entry* table; 				 // массив строк таблицы лексем

		LexTable Create(int size);

		void Add(
			Entry entry					 // строка таблицы лексем
		);

		Entry GetEntry(					 // получить строку в таблицу лексем
			int n						 // номер получаемой строки			
		);

		void Delete(); // удалить таблицу лексем
		void PrintLexTable(const wchar_t* in);		// вывод таблицы лексем
		LexTable();
	};


	
};