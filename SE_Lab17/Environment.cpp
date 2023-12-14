#define _CRT_SECURE_NO_WARNINGS
#include "Environment.h"
#include <iomanip>
#include <cstring>
#include <fstream>

namespace ENV
{

	EnvironmentToken::EnvironmentToken(char lex, ETOKENTYPE type, int inLexTable, int inIdTable)
	{
		this->type = type;
		this->inLexTable = inLexTable;
		this->inIdTable = inIdTable;
		this->lex = lex;
		parmCount = 0;
		id[0] = '\0';
	}

	EnvironmentToken::EnvironmentToken()
	{}


	void Environment::ChangeName(const char* str)
	{
		int i = 0;
		while (str[i] != '\0')
			name[i] = str[i++];
		name[i] = '\0';
	}
	void Environment::AddInd(int index)
	{
		indInIdTable[indcount++] = index;
	}
	void Environment::AddToLex(EnvironmentToken& index)
	{
		indInLexTable[lexindcount++] = index;
	}
	void Environment::SetParent(Environment* Parent)
	{
		this->ParentEnvironment = Parent;
		Parent->AddChild(this);
	}
	void Environment::AddChild(Environment* Child)
	{
		this->ÑhildEnvironments[childcount++] = Child;
	}
	Environment::Environment()
	{
		this->name[0] = '\0';
		level = 0;
		childcount = 0;
		indcount = 0;
		lexindcount = 0;
		ParentEnvironment = nullptr;
	}
	Environment::Environment(const char* name)
	{
		this->name[0] = '\0';
		strcpy(this->name, name);
		level = 0;
		childcount = 0;
		indcount = 0;
		lexindcount = 0;
		ParentEnvironment = nullptr;
	}
	void Environment::Delete()
	{
		for (int i = 0; i < childcount; i++)
			ÑhildEnvironments[i]->Delete();
		delete this;
	}


	void Environment::Print(std::ofstream& stream)
	{
	
		/*if (!stream.is_open())
			throw ERROR_THROW(63);*/
		stream << level << " " << name << '\n';
		for (int i = 0; i < indcount; i++)
			stream << indInIdTable[i] << " ";
		stream << '\n';
		for (int i = 0; i < lexindcount; i++)
			stream << indInLexTable[i].inLexTable << " ";
		stream << '\n';
		if (childcount == 0)
			return;
		for (int i = 0; i < childcount; i++)
			ÑhildEnvironments[i]->Print(stream);
	}

}