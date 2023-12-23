#define _CRT_SECURE_NO_WARNINGS
#include <stack>
#include <vector>
#include "OperatorTable.h"
#include "LexAnalysis2.h"
#include "Error.h"

#define MAXBYTE 127
#define MINBYTE -128
#define MAXNUM 2147483647
#define MINNUM -2147483648

IT::IDDATATYPE LastVarType;

int lexemaLine = 1;
int lexemaPosition = 0;

long int CharToInt(const char* charArray) {
	long int value = 0;
	for (int i = 0; charArray[i] != '\0'; ++i) {
		if (i > 10)
			throw ERROR_THROW_IN(93, lexemaLine, lexemaPosition);
		value = value * 10 + (charArray[i] - '0');
	}
	return value;
}

int NotationToDec(char* s)
{
	char notationstr[3];
	int notation = 0;
	int size = 0;
	while (s[size] != 'x')
		notationstr[size] = s[size++];
	if (size == 2)
		notation += 10 * (notationstr[0] - '0');
	notation += (notationstr[size - 1] - '0');
	int res = 0;
	int sizestr = strlen(s);
	for (int i = sizestr - 1; s[i] != 'x'; i--)
	{
		if(s[i] >= '0' && s[i] <= '9')
			res += (s[i] - '0') * pow(notation, (sizestr - i - 1));
		else
			res += (s[i] - 'A' + 10) * pow(notation, (sizestr - i - 1));

	}

	return res;
}
char* intToString(int number) {
	int numDigits = 1;
	int temp = number;
	while (temp /= 10) {
		numDigits++;
	}
	char* charArray = new char[numDigits + 1];
	for (int i = numDigits - 1; i >= 0; i--) {
		charArray[i] = '0' + (number % 10);
		number /= 10;
	}
	charArray[numDigits] = '\0';
	return charArray;
}
void ChangeLastType(char* ch, int strLine)
{
	if (strcmp(ch, "number") == 0)
		LastVarType = IT::INT;
	else if (strcmp(ch, "str") == 0)
		LastVarType = IT::STR;
	else if (strcmp(ch, "byte") == 0)
		LastVarType = IT::BYTE;
	else if (strcmp(ch, "bool") == 0)
		LastVarType = IT::BOOL;
	else if (strcmp(ch, "htmlobj") == 0)
		LastVarType = IT::HTMLOBJ;
	else if (strcmp(ch, "nodef") == 0)
		LastVarType = IT::NODEF;
	else
		throw ERROR_THROW_IN(95, strLine, -1);
}
namespace LEXA
{
	In::IN inTable;


	Token::Token(char* word, INSTTB::WORDTYPE type)
	{
		this->word[0] = '\0';
		strcpy(this->word, word);
		size = strlen(word);
		this->type = type;
		id = word[0];
	}

	Token::Token()
	{
		word[0] = '\0';
		id = '0';
		size = 0;
		type = INSTTB::NODEF;
	}

	void AddDecFun(LEXA::Tables& tables, const char* id, IT::IDDATATYPE funType, std::string js, int parmCount, IT::IDDATATYPE parmTypes...)
	{
		IT::IDDATATYPE* types = &parmTypes;
		tables.fTable.inJsCode[tables.idTable.size] = js;
		tables.fTable.size++;
		tables.idTable.Add(IT::Entry(id, funType, IT::F, -1, -1));
		tables.global->AddInd(tables.idTable.size - 1);
		for (int i = 0; i < parmCount; i++)
		{
			tables.idTable.table[tables.idTable.size - 1].AddParm(*types);
			types++;
		}
	}

	void InitFunTable(Tables& tables)
	{
		tables.fTable.size = 0;
		AddDecFun(tables, "console", IT::NODEF, "function console1s(str){console.log(str);}\n", 1, IT::STR);
		AddDecFun(tables, "sqrt", IT::INT, "function sqrt1i(number){return Math.sqrt(number);}\n", 1, IT::INT);
		AddDecFun(tables, "pow", IT::INT, "function pow2ii(number, degree){return Math.pow(number, degree);}n\n", 2, IT::INT, IT::INT);
		AddDecFun(tables, "concat", IT::STR, "function concat2ss(str1, str2){return str1 + str2;}\n", 2, IT::STR, IT::STR);
		AddDecFun(tables, "itos", IT::STR, "function itos1i(number){return String(number);}\n", 1, IT::INT);
		AddDecFun(tables, "strsize", IT::INT, "function strsize1s(str){return str.length;}\n", 1, IT::STR);
		AddDecFun(tables, "CreateVideo", IT::HTMLOBJ, "function CreateVideo1s(link) {\n"
													"    let iframe = document.createElement(\"iframe\");\n"
													"    iframe.width = \"560\";\n"
													"    iframe.height = \"315\";\n"
													"    iframe.src = link;\n"
													"    iframe.allow = \"accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share\";\n"
													"    iframe.allowFullscreen = true;\n"
													"    return iframe;\n"
													"}", 1, IT::STR);
		//AddDecFun(tables, "video", IT::NODEF, "function video1s(link)\n{\ndocument.body.innerHTML += `<iframe width=\"560\" height=\"315\" src=${link} title=\"YouTube video player\" frameborder=\"0\" allow=\"accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share\" allowfullscreen></iframe>`;\n}\n", 1, IT::STR);
		AddDecFun(tables, "tomas", IT::NODEF, "function tomas0()\n{\ndocument.body.innerHTML += '<iframe width=\"560\" height=\"315\" src=\"https://www.youtube.com/embed/X-ANZ8ba8jU?autoplay=1&loop=1\" title=\"YouTube video player\" frameborder=\"0\" allow=\"accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share\" allowfullscreen></iframe>';\n}\n", 0, IT::NODEF);
		AddDecFun(tables, "GetHtmlById", IT::HTMLOBJ, "function GetHtmlById1s(tag){return document.getElementById(tag);}\n", 1, IT::STR);
		AddDecFun(tables, "GetBody", IT::HTMLOBJ, "function GetBody0(){return document.body;}\n", 0, IT::NODEF);
		AddDecFun(tables, "Create", IT::HTMLOBJ, "function Create1s(tag){return document.createElement(tag);}\n", 1, IT::STR);
		AddDecFun(tables, "InsertToHtml", IT::NODEF, "function InsertToHtml2hh(parent, child){parent.appendChild(child);}\n", 2, IT::HTMLOBJ, IT::HTMLOBJ);
		AddDecFun(tables, "TextSet", IT::NODEF, "function TextSet2hs(tag, text){tag.innerHTML = text;}\n", 2, IT::HTMLOBJ, IT::STR);
		AddDecFun(tables, "write", IT::NODEF, "function write2hs(tag, text){tag.innerHTML += text;}\n", 2, IT::HTMLOBJ, IT::STR);
		AddDecFun(tables, "writeln", IT::NODEF, "function writeln2hs(tag, text){tag.innerHTML += `<br>${text}`;}\n", 2, IT::HTMLOBJ, IT::STR);
		AddDecFun(tables, "SetCSS", IT::NODEF, "function SetCSS2hs(tag, css){tag.style.cssText = css;}\n", 2, IT::HTMLOBJ, IT::STR);
		AddDecFun(tables, "AddCSS", IT::NODEF, "function AddCSS2hs(tag, css){tag.style.cssText += css;}\n", 2, IT::HTMLOBJ, IT::STR);
		AddDecFun(tables, "SetAttribute", IT::NODEF, "function SetAttribute3hss(tag, atr, value){tag.setAttribute(atr, value);}\n", 3, IT::HTMLOBJ, IT::STR, IT::STR);
	}
	
	void LexicalAnalyzer(const In::IN& source, Tables& tables)
	{
		bool isWord = false;
		In::IN inTable;
		//int tabCount = 0;
		for (int i = 0; i < source.size; i++)
		{
			Token token;
			
			if (source.text[i] == '|')
			{
			
				lexemaLine++;
				lexemaPosition = 0;
				continue;
			}
			if (source.text[i] == '\'') // —читывание строкового литерала '
			{
				
				token.type = INSTTB::LEX;
				token.word[token.size++] = source.text[i++];

				while (source.text[i] != '\'')
				{
					if (token.size >= TI_STR_MAXSIZE)
						throw ERROR_THROW_IN(91, lexemaLine, lexemaPosition);
					if (source.text[i] == '\\' && source.text[i + 1] == '\'')
					{
						token.word[token.size++] = source.text[i++];
						if (token.size >= TI_STR_MAXSIZE)
							throw ERROR_THROW_IN(91, lexemaLine, lexemaPosition);
					}
					token.word[token.size++] = source.text[i++];
				}

				token.word[token.size++] = source.text[i];

			}
			else if (inTable.code[source.text[i]] == inTable.S || inTable.code[source.text[i]] == inTable.O) // —читывание символа сепаратора или оператора
			{
				
				if (source.text[i] == ' ' || source.text[i] == '\t')
					continue;
				if (inTable.code[source.text[i]] == inTable.S)
				{
					token.type = INSTTB::SPR;
					token.word[token.size++] = source.text[i];
					lexemaPosition++;
				}
				else
				{
					token.type = INSTTB::OPR;
					while (inTable.code[source.text[i]] == inTable.O)
					{
						token.word[token.size++] = source.text[i];
						i++;
						lexemaPosition++;
					}
					lexemaPosition--;
					i--;
				}	
			}
			else
				token.type = INSTTB::WORD;

			// —читывание слова
			while (inTable.code[source.text[i]] == inTable.T && source.text[i] != '|')
			{
				token.word[token.size++] = source.text[i++];
				lexemaPosition++;
				if (!(inTable.code[source.text[i]] == inTable.T && source.text[i] != '|'))
				{
					i--;
					break;
				}
			}
			token.word[token.size] = '\0';
			token.id = token.word[0];
			AnalyzeToken(token, lexemaLine, tables);
		}

	}

	bool AnalyzeToken(Token& token, int strLine, Tables& tables)
	{
		INSTTB::FSTGen fstg = tables.instTable.GetFST(token.id, token.word);

		FSTExecute(fstg);
		if(fstg.type == INSTTB::NODEF)
			throw ERROR_THROW_IN(93, strLine, lexemaPosition);
		if (fstg.type == INSTTB::OPR) // считывание оператора
		{
			tables.LexTable.Add(LT::Entry(fstg.lex, strLine, LT_TI_NULLXDX));
			tables.LexTable.table[tables.LexTable.size - 1].opr = tables.oprTable.Get(fstg.analizStr);//запись в opr ссылку на оператора в таблице операторов
			return true;
		}
		if (fstg.type == INSTTB::WORD || fstg.type == INSTTB::SPR)
		{
			tables.LexTable.Add(LT::Entry(fstg.lex, strLine, LT_TI_NULLXDX));
			if (fstg.lex == 't')
				ChangeLastType(fstg.analizStr, strLine);
			return true;
		}
		INDAnalyz(fstg, strLine, tables);

		return false;
	}

	void INDAnalyz(INSTTB::FSTGen& fstg, int strLine, Tables& tables)
	{
		IT::IDDATATYPE indType;
		long int value;
		bool isNota = fstg.type == INSTTB::NOTA;
		if (fstg.type == INSTTB::NOTA)
		{
			value = NotationToDec(fstg.analizStr);
			strcpy(fstg.analizStr, intToChar(value));
			fstg.type = INSTTB::LEX;
		}
		if (fstg.type == INSTTB::LEX)
		{
			if (fstg.analizStr[0] == '\'')
				indType = IT::STR;
			else if (fstg.analizStr[0] == 'f' || fstg.analizStr[0] == 't')
				indType = IT::BOOL;
			else
			{
				if (!isNota)
					value = CharToInt(fstg.analizStr);
				if (tables.LexTable.table[tables.LexTable.size - 1].lexema == LEX_OPERATOR && tables.LexTable.table[tables.LexTable.size -1 ].opr->opr[0] == '-'
					&& (tables.LexTable.table[tables.LexTable.size - 2].lexema == LEX_EQUAL_SIGN || tables.LexTable.table[tables.LexTable.size - 2].lexema == LEX_LEFTBRACE))
					value *= -1;
				if(value > MAXNUM || value < MINNUM)
					throw ERROR_THROW_IN(93, lexemaLine, lexemaPosition);
				if (value > MAXBYTE || value < MINBYTE)
					indType = IT::INT;
				else
					indType = IT::BYTE;
			}
			int n = tables.idTable.literalCount;
			int size = 4;
			char id[93] = "l_";
			if (n != 0)
			{
				char* suf = intToChar(n);
				size += strlen(suf);
				strcat(id, suf);
			}
			else
			{
				id[2] = '0';
				id[3] = '\0';
			}
			if (indType == IT::BYTE || indType == IT::INT)
			{
				tables.idTable.Add(IT::Entry(id, indType, IT::L, tables.LexTable.size, strLine));
				tables.idTable.table[tables.idTable.size -1].value.vint = value;
				if(value < 0)
					tables.LexTable.table[tables.LexTable.size - 1] = LT::Entry(fstg.lex, strLine, tables.idTable.size - 1);
				else
					tables.LexTable.Add(LT::Entry(fstg.lex, strLine, tables.idTable.size - 1));
			}
			else
			{
				tables.idTable.Add(IT::Entry(id, indType, IT::L, tables.LexTable.size, fstg.analizStr, strLine));
				LT::Add(tables.LexTable, LT::Entry(fstg.lex, strLine, tables.idTable.size - 1));
			}
			tables.idTable.literalCount++;
			return;
		}
		if(fstg.type == INSTTB::LEX && fstg.analizStr[0] >= '0' && fstg.analizStr[0] <= '9')
			throw ERROR_THROW_IN(95, strLine, -1);
		if (fstg.lex != 'm' && tables.LexTable.size == 0)
			throw ERROR_THROW_IN(97, strLine, -1);
		if (fstg.lex == 'm' || tables.LexTable.table[tables.LexTable.size - 1].lexema == LEX_FUNCTION) //первое объ€вление функции
		{
			if(fstg.lex == 'm')
				tables.idTable.Add(IT::Entry(fstg.analizStr, IT::NODEF, IT::F, tables.LexTable.size, strLine));
			else
				tables.idTable.Add(IT::Entry(fstg.analizStr, LastVarType, IT::F, tables.LexTable.size, strLine));
			tables.LexTable.Add(LT::Entry(fstg.lex, strLine, tables.idTable.size - 1));
			tables.idTable.funCount++;
			//envStack.push(EnvironmentToken(fstg.analizStr, FUN, tables.LexTable.size - 1, tables.idTable.size - 1));
			return;
		}
		if (tables.LexTable.table[tables.LexTable.size - 1].lexema == LEX_DATATYPE) //первое объ€вление переменной
		{
			tables.idTable.Add(IT::Entry(fstg.analizStr, LastVarType, IT::V, tables.LexTable.size, strLine));
			tables.LexTable.Add(LT::Entry(fstg.lex, strLine, tables.idTable.size - 1));
			tables.idTable.varCount++;
			//envStack.push(EnvironmentToken(fstg.analizStr, FIND, tables.LexTable.size - 1, tables.idTable.size - 1));
			return;
		}
		int indexInIt = tables.idTable.IsId(fstg.analizStr);
		if(indexInIt == LT_TI_NULLXDX)
			throw ERROR_THROW_IN(93, strLine, lexemaPosition);
		tables.LexTable.Add(LT::Entry(fstg.lex, strLine, tables.idTable.IsId(fstg.analizStr)));
		//envStack.push(EnvironmentToken(fstg.analizStr, IND, tables.LexTable.size - 1, LT_TI_NULLXDX));
	}

	bool FSTExecute(INSTTB::FSTGen& fstg)
	{
		if (fstg.type == INSTTB::NODEF)
		{
			if (FST::execute(fstg.fst))
				fstg.type = INSTTB::IND;
			return false;
		}
		if (FST::execute(fstg.fst))
			return true;
		fstg.NextFst();
		return FSTExecute(fstg);
	}

	

	char* intToChar(int num) {
		int length = static_cast<int>(log10(num)) + 1;
		char str[90];
		str[length] = '\0';
		for (int i = length - 1; i >= 0; --i) {
			str[i] = '0' + (num % 10);
			num /= 10;
		}
		return str;
	}

	void Delete(Tables& tables)
	{
		LT::Delete(tables.LexTable);
		IT::Delete(tables.idTable);
		tables.instTable.DeleteTable();
		tables.global->Delete();
	}
}