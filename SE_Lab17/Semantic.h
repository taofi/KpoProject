#pragma once
#include "LexAnalysis2.h"
#include "IT.h"
#include "LT.h"
using namespace ENV;


namespace SA
{
	struct EToken
	{
		EnvironmentToken token;
		Environment* envRef;
		EToken(EnvironmentToken token, Environment* envRef);
	};


	int CountIdInEnvironment(const char* id, ENV::Environment* env, LEXA::Tables& tables);
	void GetNewId(IT::Entry& el);
	char* intToChar(int num);
	char GetTypeInChar(IT::IDDATATYPE type);
	bool Semantic(LEXA::Tables& tables);
	bool EnvironmentAnalyz(LEXA::Tables& tables);
	int ExpressionCheck(int index, LEXA::Tables& tables);
	int FunParmTypeCheck(int index, LEXA::Tables& tables);

	void EnvironmentAnalyzDeep(ENV::Environment* env, LEXA::Tables& tables);
	void EnvironmentAnalyzUp(int lexIndex, ENV::Environment* env, LEXA::Tables& tables);
}