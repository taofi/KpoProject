#pragma once
#pragma once
#include "IT.h"
#include <fstream>
#include "OperatorTable.h"
#define LEXEMA_FIXSIZE  1			// ������������� ������ �������
#define	LT_MAXSIZE		4096		// ������������ ���������� ����� � ������� ������	
#define	LT_TI_NULLXDX	-1			// ��� �������� ������� ���������������		
#define	LEX_DATATYPE	't'			// ������� ��� ���� ������	
#define	LEX_INTEGER		't'			// ������� ��� integer
#define	LEX_STRING		't'			// ������� ��� string
#define	LEX_ID			'i'			// ������� ��� ��������������
#define	LEX_LITERAL		'l'			// ������� ��� ��������
#define	LEX_FUNCTION	'f'			// ������� ��� function
#define	LEX_DECLARE		'd'			// ������� ��� declare
#define	LEX_RETURN		'r'			// ������� ��� return
#define	LEX_PRINT		'p'			// ������� ��� print
#define	LEX_MAIN		'm'			// ������� ��� main
#define	LEX_STRLEN		'e'			// ������� ��� strlen
#define	LEX_SEMICOLON	';'			// ������� ��� ;
#define	LEX_COMMA		','			// ������� ��� ,
#define	LEX_LEFTBRACE	'{'			// ������� ��� {
#define	LEX_RIGHTBRACE	'}'			// ������� ��� }
#define	LEX_LEFTHESIS	'('			// ������� ��� (
#define	LEX_RIGHTHESIS	')'			// ������� ��� )
#define	LEX_PLUS		'v'			// ������� ��� +
#define	LEX_MINUS		'v'			// ������� ��� -
#define	LEX_STAR		'v'			// ������� ��� *
#define LEX_OPERATOR	'v'
#define	LEX_EQUAL_SIGN	'='			// ������� ��� =
#define LEX_IF			'j'			//������� ��� if
#define LEX_WHILE		'w'			//������� ��� while
#define LEX_EVENT		'p'			//������� ��� �������



namespace LT									// ������� ������
{
	struct Entry								// ������ ������� ������
	{
		char lexema;							// �������
		int sn;									// ����� ������ � �������� ������
		int idxTI;								// ������ � ������� ��������������� ��� LT_TI_NULLIDX
		OT::OEntry* opr;								// ������ ��������� 
		Entry();
		Entry(const char lex, int str_n, int idxTI);
		Entry(const char lex, int str_n, int idxTI, char oSymbol);
	};

	struct LexTable								// �������� ������� ������
	{
		int maxsize;							// ������� ������� ������ < LT_MAXSIZE
		int size;								// ������� ������ ������� ������ < maxsize
		Entry* table;							// ������ ����� ������� ������
		Entry GetEntry(								// �������� ������ ������� ������
			int n									// ����� ���������� ������
		);

		void PrintLexTable(std::ofstream& lexStream);		// ����� ������� ������
		void UnformattedPrintLexTable(const wchar_t* in);
		LexTable();
		void Add(									// �������� ������ � ������� ������
			Entry entry								// ������ ������� ������
		);
	};

	void Add(									// �������� ������ � ������� ������
		LexTable& lextable,						// ��������� ������� ������
		Entry entry								// ������ ������� ������
	);

	void Delete(LexTable& lextable);			// ������� ������� ������ (���������� ������)
};