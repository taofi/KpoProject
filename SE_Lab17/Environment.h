#pragma once
#define MAXINDCOUNT 300
#define ID_MAXSIZE 20
#define TI_MAX_COUNT_PARM 10
#include <fstream>

namespace ENV
{

	enum ETOKENTYPE { FUN = 0, FIND, IND, SPR, RET, FUNIND, ENVT };

	struct EnvironmentToken
	{
		char lex;  //лексема
		ETOKENTYPE type;			//тип токена
		int inLexTable;				//вхождение в таблице лексем			
		int inIdTable;				//вхождение в таблице индитификаторов
		int parmCount;
		int parmLexIndex[TI_MAX_COUNT_PARM];
		char id[ID_MAXSIZE];
		EnvironmentToken();
		EnvironmentToken(char lex, ETOKENTYPE type, int inLexTable, int inIdTable);
	};

	struct Environment
	{
		int level;
		char name[ID_MAXSIZE];
		int lexindcount;
		int indInIdTable[MAXINDCOUNT];  //массив индексов идентификаторов в таблице 
		EnvironmentToken indInLexTable[MAXINDCOUNT * 10];//массив индексов в таблице лексем
		int indcount; //количество идентификаторов
		int childcount; //количество потомков
		Environment* ParentEnvironment; //ссылка на родитля 
		Environment* СhildEnvironments[MAXINDCOUNT]; //массив потомков
		void AddInd(int index);
		void AddToLex(EnvironmentToken& index);
		void SetParent(Environment* Parent);
		void AddChild(Environment* Child);
		void Delete();
		void ChangeName(const char* str);
		void Print(std::ofstream& stream);
		Environment();
		Environment(const char* name);
	};
}