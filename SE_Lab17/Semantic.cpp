#include "stdafx.h"
#include "Semantic.h"
#include "LexAnalysis2.h"
#include "Error.h"
#include <queue>
#include <stack>
#include <iostream>
#include <cstring>

stack<Error::ERROR>* warningQ;
namespace SA
{
	
	std::stack<EnvironmentToken> envStack;
	EToken::EToken(EnvironmentToken token, Environment* envRef)
	{
		this->envRef = envRef;
		this->token = token;
	}

	bool FunRetAnlz(LEXA::Tables& tables)
	{
		stack<EnvironmentToken> rstack;
		stack<EnvironmentToken> astack;
		int blockCount = 0;
		IT::IDDATATYPE ftype;
		for (int i = 0; i < tables.LexTable.size; i++)
		{
			if (tables.LexTable.table[i].lexema == '{' || tables.LexTable.table[i].lexema == '}')
				rstack.push(EnvironmentToken(tables.LexTable.table[i].lexema, SPR, i, tables.LexTable.table[i].idxTI));
			else if (tables.LexTable.table[i - 1].lexema == 'f' && tables.LexTable.table[i].lexema == 'i' || tables.LexTable.table[i].lexema == 'm')
				rstack.push(EnvironmentToken(tables.LexTable.table[i].lexema, FUN, i, tables.LexTable.table[i].idxTI));
			else if (tables.LexTable.table[i].lexema == 'r')
				rstack.push(EnvironmentToken(tables.LexTable.table[i].lexema, RET, i, tables.LexTable.table[i].idxTI));
		}
		while (!rstack.empty())
		{
			if (rstack.top().type == FUN)
			{
				bool retFound = false;
				ftype = tables.idTable.table[rstack.top().inIdTable].iddatatype;
				do
				{
					if (astack.top().lex == '{')
						blockCount++;
					else if (astack.top().lex == '}')
						blockCount--;
					else if (astack.top().type == RET)
					{
						retFound = true;
						for (int i = astack.top().inLexTable + 1; tables.LexTable.table[i].lexema != ';'; i++)
						{
							if ((tables.LexTable.table[i].lexema == '('))
							{
								while (tables.LexTable.table[i].lexema != ')')
									i++;
							}
							if ((tables.LexTable.table[i].lexema == LEX_ID || tables.LexTable.table[i].lexema == LEX_LITERAL) && tables.idTable.table[tables.LexTable.table[i].idxTI].iddatatype != ftype)
								throw ERROR_THROW_IN(125, tables.LexTable.table[i].sn, -1);
						}
					}
					astack.pop();
				} while (blockCount != 0);
				if(!retFound && ftype != IT::NODEF)
					throw ERROR_THROW_IN(132, tables.LexTable.table[rstack.top().inLexTable].sn, -1);
			}
			if (rstack.top().type == SPR || rstack.top().type == RET)
				astack.push(rstack.top());
			rstack.pop();
		}
		return true;
	}

	bool Semantic(LEXA::Tables& tables, stack<Error::ERROR>* wq)
	{
		warningQ = wq;
		//std::stack<FunToken> funIdInLex;
		for (int i = 0; i < tables.LexTable.size; i++)
		{
			if (tables.LexTable.table[i].lexema == '{' || tables.LexTable.table[i].lexema == '}')
				envStack.push(EnvironmentToken(tables.LexTable.table[i].lexema, SPR, i, tables.LexTable.table[i].idxTI));
			else if (tables.LexTable.table[i - 1].lexema == 'f' && tables.LexTable.table[i].lexema == 'i' || tables.LexTable.table[i].lexema == 'm')
				envStack.push(EnvironmentToken(tables.LexTable.table[i].lexema, FUN, i, tables.LexTable.table[i].idxTI));
			else if (tables.LexTable.table[i].lexema == 'i' && tables.LexTable.table[i - 1].lexema == 't')
				envStack.push(EnvironmentToken(tables.LexTable.table[i].lexema, FIND, i, tables.LexTable.table[i].idxTI));
			/*else if (tables.LexTable.table[i].lexema == 'r' )
				envStack.push(EnvironmentToken(tables.LexTable.table[i].lexema, RET, i, tables.LexTable.table[i].idxTI));*/
			else if (tables.LexTable.table[i].lexema == 'i' && tables.LexTable.table[i + 1].lexema == '(')
			{
				EnvironmentToken envt = EnvironmentToken(tables.LexTable.table[i].lexema, FUNIND, i, tables.LexTable.table[i].idxTI);
				strcpy(envt.id, tables.idTable.table[tables.LexTable.table[i].idxTI].id);
				i ++;
				while (tables.LexTable.table[i].lexema != ')')
				{
					if (tables.LexTable.table[i].lexema == LEX_ID || tables.LexTable.table[i].lexema == LEX_LITERAL)
						envt.parmLexIndex[envt.parmCount++] = i;
					i++;

				}
				
				envStack.push(envt);
			}
			else if(tables.LexTable.table[i].lexema == 'i')
				envStack.push(EnvironmentToken(tables.LexTable.table[i].lexema, IND, i, tables.LexTable.table[i].idxTI));
		}

		EnvironmentAnalyz(tables);


		for (int i = 0; i < tables.idTable.size; i++)
		{
			if (tables.idTable.table[i].idtype == IT::F)
				GetNewId(tables.idTable.table[i]);
		}

		EnvironmentAnalyzDeep(tables.global, tables);

		for (int i = 0; i < tables.idTable.size; i++)
		{
			if(tables.idTable.table[i].idtype == IT::V && tables.idTable.table[i].iddatatype == IT::NODEF)
				throw ERROR_THROW_IN(128, tables.idTable.table[i].str_number, -1);
			if (tables.idTable.table[i].idtype == IT::L)
				continue;
			if (CountIdInEnvironment(tables.idTable.table[i].id, tables.idTable.table[i].indEnv, tables) > 1)
			{
				if (tables.idTable.table[i].idtype == IT::F)
					throw ERROR_THROW_IN(120, tables.idTable.table[i].str_number, -1);
				
					throw ERROR_THROW_IN(121, tables.idTable.table[i].str_number, -1);
			}
		}

		
		//анализ выражений
		for (int i = 0; i < tables.LexTable.size; i++)
		{
			if (tables.LexTable.table[i].lexema == LEX_EQUAL_SIGN)
			{
				i += ExpressionCheck(i, tables);
			}
			else if (tables.LexTable.table[i].lexema == LEX_IF || tables.LexTable.table[i].lexema == LEX_WHILE)
			{
				i += ExpressionCheck(i, tables, IT::BOOL);
			}
			else if (tables.LexTable.table[i].lexema == LEX_EVENT)
			{
				if(tables.idTable.table[tables.LexTable.table[i - 1].idxTI].iddatatype != IT::HTMLOBJ ||
					tables.idTable.table[tables.LexTable.table[i + 1].idxTI].iddatatype != IT::STR)
					throw ERROR_THROW_IN(124, tables.LexTable.table[i].sn, -1);
			}
		}
		FunRetAnlz(tables);
		return false;
	}

	int ExpressionCheck(int index, LEXA::Tables& tables, IT::IDDATATYPE type)
	{
		if(type == IT::NODEF)
			type = tables.idTable.table[tables.LexTable.table[index - 1].idxTI].iddatatype;
		int size = 0;
		bool oprFound = false;
		bool hasBoolOpr = false;
		bool needBoolOpr = false;
		for (int i = index; tables.LexTable.table[i].lexema != LEX_SEMICOLON; i++)
		{
			if (tables.LexTable.table[i].lexema == '{')
				break;
			size++;
			if (tables.LexTable.table[i].lexema == LEX_ID && tables.LexTable.table[i + 1].lexema == LEX_LEFTHESIS && tables.LexTable.table[i - 1].lexema != LEX_FUNCTION)
			{
				if (type == IT::BOOL && tables.idTable.table[tables.LexTable.table[i].idxTI].iddatatype != type)
					needBoolOpr = true;
				if (type != IT::BOOL && tables.idTable.table[tables.LexTable.table[i].idxTI].iddatatype != type)
					throw ERROR_THROW_IN(124, tables.LexTable.table[i].sn, -1);
				while (tables.LexTable.table[i].lexema != ')')
					i++;
			}
			else if (tables.LexTable.table[i].lexema == LEX_LITERAL || tables.LexTable.table[i].lexema == LEX_ID)
			{
				if (tables.idTable.table[tables.LexTable.table[i].idxTI].iddatatype == IT::BYTE && type == IT::INT)
					continue;
				if(type == IT::BOOL && tables.idTable.table[tables.LexTable.table[i].idxTI].iddatatype == IT::STR)
					throw ERROR_THROW_IN(129, tables.LexTable.table[i].sn, -1);
				if (type == IT::BOOL && tables.idTable.table[tables.LexTable.table[i].idxTI].iddatatype != type)
					needBoolOpr = true;
				if (type != IT::BOOL &&tables.idTable.table[tables.LexTable.table[i].idxTI].iddatatype != type)
					throw ERROR_THROW_IN(124, tables.LexTable.table[i].sn, -1);
			}
			else if (tables.LexTable.table[i].lexema == LEX_OPERATOR)
			{
				oprFound = true;
				if (type == IT::BYTE && tables.LexTable.table[i].opr->type == IT::INT)
					continue;
				if (tables.LexTable.table[i].opr->type == IT::BOOL)
				{
					if(hasBoolOpr)
						throw ERROR_THROW_IN(124, tables.LexTable.table[i].sn, -1);
					hasBoolOpr = true;
				}
				if (type == IT::BOOL && tables.LexTable.table[i].opr->type != type)
					needBoolOpr = true;
				if (type != IT::BOOL && tables.LexTable.table[i].opr->type != type)
					throw ERROR_THROW_IN(124, tables.LexTable.table[i].sn, -1);
			}
		}
		if(needBoolOpr && !hasBoolOpr)
			throw ERROR_THROW_IN(130, tables.LexTable.table[index].sn, -1);
		if (oprFound && type == IT::BYTE)
			warningQ->push( Error::geterrorin(133, tables.LexTable.table[index].sn, -1) );
		return size;
	}


	void EnvironmentAnalyzDeep(ENV::Environment* env, LEXA::Tables& tables)
	{
		if (env->lexindcount != 0)
		{
			for (int i = 0; i < env->lexindcount; i++)
			{
				if (env->indInLexTable[i].type == FUNIND) //найден вызов функции
				{
					for (int j = 0; j < env->indInLexTable[i].parmCount; j++)
					{
						EnvironmentAnalyzUp(env->indInLexTable[i].parmLexIndex[j], env, tables);
					}
					if (env->indInLexTable[i].parmCount == 0)
					{
						int size = strlen(env->indInLexTable[i].id);
						env->indInLexTable[i].id[size++] = '0';
						env->indInLexTable[i].id[size] = '\0';
					}
					else
					{
						strcat(env->indInLexTable[i].id, intToChar(env->indInLexTable[i].parmCount));
						int size = strlen(env->indInLexTable[i].id);
						IT::IDDATATYPE type;
						for (int j = 0; j < env->indInLexTable[i].parmCount; j++)
						{
							type = tables.idTable.table[tables.LexTable.table[env->indInLexTable[i].parmLexIndex[j]].idxTI].iddatatype;
							env->indInLexTable[i].id[size++] = GetTypeInChar(type);
						}
						env->indInLexTable[i].id[size] = '\0';
					}
					int index = tables.idTable.IsId(env->indInLexTable[i].id);
					if (index == LT_TI_NULLXDX)
						throw ERROR_THROW_IN(127, tables.LexTable.table[env->indInLexTable[i].inLexTable].sn, -1);
					tables.LexTable.table[env->indInLexTable[i].inLexTable].idxTI = index;
					tables.idTable.table[index].refCount++;
				}
			
				EnvironmentAnalyzUp(env->indInLexTable[i].inLexTable, env, tables);
			}
		}
		for (int i = 0; i < env->childcount; i++)
		{
			EnvironmentAnalyzDeep(env->СhildEnvironments[i], tables);
		}
	}

	void EnvironmentAnalyzUp(int lexIndex, ENV::Environment* env, LEXA::Tables& tables)
	{
		if (tables.LexTable.table[lexIndex].idxTI == LT_TI_NULLXDX)
		{
			throw ERROR_THROW_IN(126, tables.LexTable.table[lexIndex].sn, -1);
			return;
		}
		if (tables.idTable.table[tables.LexTable.table[lexIndex].idxTI].idtype == IT::L)
			return;
		for (int i = 0; i < env->indcount; i++)
		{
			tables.idTable.table[env->indInIdTable[i]].indEnv = env;
			if (env->indInIdTable[i] == -1)
				continue;
			if (strcmp(tables.idTable.table[env->indInIdTable[i]].id, tables.idTable.table[tables.LexTable.table[lexIndex].idxTI].id) == 0)
			{
				if(tables.idTable.table[env->indInIdTable[i]].firstApi > lexIndex)
					throw ERROR_THROW_IN(126, tables.LexTable.table[lexIndex].sn, -1);
				tables.LexTable.table[lexIndex].idxTI = env->indInIdTable[i];
				tables.idTable.table[env->indInIdTable[i]].refCount++;
				return;
			}
		}
		if (env == tables.global)
			return;
		EnvironmentAnalyzUp(lexIndex, env->ParentEnvironment, tables);
	}

	int CountIdInEnvironment(const char* id, ENV::Environment* env, LEXA::Tables& tables)
	{
		int count = 0;
		for (int i = 0; i < env->indcount; i++)
		{
			if (strcmp(tables.idTable.table[env->indInIdTable[i]].id, id) == 0)
				count++;
		}
		return count;
	}

	void GetNewId(IT::Entry& el)
	{
		if (el.value.parm.parmQuantity == 0)
		{
			int size = strlen(el.id);
			el.id[size++] = '0';
			el.id[size] = '\0';
			return;
		}
		strcat(el.id, intToChar(el.value.parm.parmQuantity));
		int size = strlen(el.id);
		for (int i = 0; i < el.value.parm.parmQuantity; i++)
		{
			el.id[size++] = GetTypeInChar(el.value.parm.type[i]);
		}
		el.id[size] = '\0';
	}

	char* intToChar(int num) {
		int length = static_cast<int>(log10(num)) + 1;
		char* str = new char[length + 1];
		str[length] = '\0';
		for (int i = length - 1; i >= 0; --i) {
			str[i] = '0' + (num % 10); 
			num /= 10;
		}
		return str;
	}

	char GetTypeInChar(IT::IDDATATYPE type)
	{
		switch (type)
		{
		case IT::BYTE:
		case IT::INT:
			return 'i';
		case IT::STR:
			return 's';
		case IT::DEF:
			return 'd';
		case IT::BOOL:
			return 'b';
		case IT::HTMLOBJ:
			return 'h';
		default:
			return 'u';
			break;
		}
	}

	
	bool EnvironmentAnalyz(LEXA::Tables& tables)
	{
		std::stack<EToken> anlStack;
		std::stack<int> parmIndex;
		int level = 0;
		while (!envStack.empty())
		{
			if (envStack.top().lex == '{')
			{
				ENV::Environment* env = new Environment();
				env->level = level;
				//tables.idTable.table[envStack.top().inIdTable].indEnv = env;
				//isParam = true;
				while (anlStack.top().token.lex != '}')
				{
					if (anlStack.top().token.type == ENVT)
						anlStack.top().envRef->SetParent(env);
					else if(anlStack.top().token.type == FIND || anlStack.top().token.type == FUN)
					{
						env->AddInd(anlStack.top().token.inIdTable);
						tables.idTable.table[anlStack.top().token.inIdTable].indEnv = env;
					}
					else if (anlStack.top().token.type == IND || anlStack.top().token.type == FUNIND)
					{
						env->AddToLex(anlStack.top().token);
					}
					anlStack.pop();
					if (anlStack.empty())
						throw ERROR_THROW(600);
				}
				anlStack.pop();
				anlStack.push(EToken(EnvironmentToken(), env));
				anlStack.top().token.type = ENVT;
				level--;
				if (level  == -1)
					throw ERROR_THROW(98);
			}
			else if (envStack.top().type == FUN)
			{
				
				while (anlStack.top().token.type != ENVT)
				{
					if (anlStack.top().token.type == FIND)
					{
						tables.idTable.table[envStack.top().inIdTable].AddParm(tables.idTable.table[anlStack.top().token.inIdTable].iddatatype);
						tables.idTable.table[anlStack.top().token.inIdTable].idtype = IT::P;
						parmIndex.push(anlStack.top().token.inIdTable);
						if (parmIndex.size() >= TI_MAX_COUNT_PARM)
							throw ERROR_THROW_IN(123, tables.idTable.table[envStack.top().inIdTable].str_number, -1);
					}
					anlStack.pop();
					if (anlStack.empty())
						throw ERROR_THROW(600);
				}
				anlStack.top().envRef->ChangeName(tables.idTable.table[envStack.top().inIdTable].id);
				while (!parmIndex.empty())
				{
					anlStack.top().envRef->AddInd(parmIndex.top());
					tables.idTable.table[parmIndex.top()].indEnv = anlStack.top().envRef;
					parmIndex.pop();
				}
				anlStack.push(EToken(envStack.top(), nullptr));
			}
			else
			{
				anlStack.push(EToken(envStack.top(), nullptr));
				if (anlStack.top().token.lex == '}')
					level++;
			}
			envStack.pop();
		}
		while (!anlStack.empty())
		{
			if (anlStack.top().token.type == ENVT)
				anlStack.top().envRef->SetParent(tables.global);
			else if (anlStack.top().token.type == IND)
				tables.global->AddToLex(anlStack.top().token);
			else if(anlStack.top().token.type == FIND || anlStack.top().token.type == FUN)
			{
				tables.global->AddInd(anlStack.top().token.inIdTable);
				tables.idTable.table[anlStack.top().token.inIdTable].indEnv = tables.global;
			}
			anlStack.pop();
		}
		return true;
	}
}