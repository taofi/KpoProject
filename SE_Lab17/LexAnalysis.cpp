#include "stdafx.h"

namespace LA
{
	void LexicalAnalyzer(const In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		bool isWord = false;

		int tempWordIndex = 0;
		int lexemaLine = 1;
		int lexemaPosition = 0;

		In::IN inTable;
		
		for (int i = 0; i < source.size; i++)
		{
			char* tempWord = new char[token_size] {};

			// Считывание слова
			while (inTable.code[source.text[i]] == inTable.T && source.text[i] != '|')
			{
				tempWord[tempWordIndex++] = source.text[i++];
				lexemaPosition++;
				isWord = true;
			}

			// Если считаталось слово
			if (isWord)
			{
				if (AnalyzeToken(tempWord, lexemaLine, lexTable, idTable))
				{
					tempWordIndex = 0;
					i--;
					isWord = false;
					continue;
				}
				else
					throw ERROR_THROW_IN(90, lexemaLine, lexemaPosition); // слово не распознано
			}

			// Считывание строкового литерала '
			if (source.text[i] == '\'')
			{
				tempWord[tempWordIndex++] = source.text[i++];

				while (source.text[i] != '\'')
				{
					if (tempWordIndex >= TI_STR_MAXSIZE)
						throw ERROR_THROW_IN(91, lexemaLine, lexemaPosition); // строковый литерал слишком длинный

					tempWord[tempWordIndex++] = source.text[i++];
				}

				tempWord[tempWordIndex] = source.text[i];

				if (AnalyzeToken(tempWord, lexemaLine, lexTable, idTable))
				{
					tempWordIndex = 0;
					continue;
				}
				else
					throw ERROR_THROW_IN(92, lexemaLine, lexemaPosition); // строковый литерал не распознан автоматом
			}

			// Считывание символа сепаратора или оператора
			if (inTable.code[source.text[i]] == inTable.S || inTable.code[source.text[i]] == inTable.O)
			{
				if (source.text[i] == ' ' || source.text[i] == '\t')
					continue;

				tempWord[tempWordIndex] = source.text[i];

				if (!AnalyzeToken(tempWord, lexemaLine, lexTable, idTable))
					throw ERROR_THROW_IN(123, lexemaLine, lexemaPosition); // символ операции или сепаратор не распознан

				lexemaPosition++;
				tempWord = 0;

				continue;
			}

			if (source.text[i] == '|')
			{
				//std::cout << lexemaLine << " " << i << " " << source.text[i] << std::endl;
				lexemaLine++;
				lexemaPosition = 0;
			}
		}
	}

	bool AnalyzeToken(char* token, const int str_number, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		static TypeOfVar flag_type_variable;

		switch (token[0])
		{
		case LEX_COMMA:
			Add(lexTable, { LEX_COMMA ,str_number, LT_TI_NULLXDX });
			return true;
		case LEX_LEFTBRACE:
			Add(lexTable, { LEX_LEFTBRACE,str_number,LT_TI_NULLXDX });
			return true;
		case LEX_RIGHTBRACE:
			Add(lexTable, { LEX_RIGHTBRACE,str_number,LT_TI_NULLXDX });
			return true;
		case LEX_LEFTHESIS:
			Add(lexTable, { LEX_LEFTHESIS,str_number,LT_TI_NULLXDX });
			return true;
		case LEX_RIGHTHESIS:
			Add(lexTable, { LEX_RIGHTHESIS,str_number,LT_TI_NULLXDX });
			return true;
		case LEX_SEMICOLON:
			Add(lexTable, { LEX_SEMICOLON,str_number,LT_TI_NULLXDX });
			return true;
		case LEX_EQUAL_SIGN:
			Add(lexTable, { LEX_EQUAL_SIGN, str_number, LT_TI_NULLXDX });
			return true;

		case '+':
			Add(lexTable, { LEX_PLUS,str_number,idTable.size - 1, token[0]});
			return true;
		case '-':
			Add(lexTable, { LEX_MINUS, str_number, idTable.size - 1, token[0]});
			return true;
		case '*':
			Add(lexTable, { LEX_STAR, str_number, idTable.size - 1, token[0]});
			return true;
		case '/':
			Add(lexTable, { LEX_DIRSLASH, str_number, idTable.size - 1, token[0]});
			return true;

		case 'f':
		{
			FST::FST function(FUNCTION(token));
			if (FST::execute(function))
			{
				Add(lexTable, { LEX_FUNCTION, str_number, LT_TI_NULLXDX });
				return true;
			}
			else
				return AnalyzeIdentifier(token, str_number, lexTable, idTable, flag_type_variable);
		}
		case 'i':
		{
			FST::FST integer(INTEGER(token));
			if (FST::execute(integer))
			{
				Add(lexTable, { LEX_INTEGER, str_number, LT_TI_NULLXDX });

				flag_type_variable.LT_posititon = lexTable.size - 1;
				flag_type_variable.type = TypeOfVar::INT;
				return true;
			}
			else
				return AnalyzeIdentifier(token, str_number, lexTable, idTable, flag_type_variable);
		}
		case 's':
		{
			FST::FST string(STRING(token));
			if (FST::execute(string))
			{
				Add(lexTable, { LEX_STRING, str_number, LT_TI_NULLXDX });

				flag_type_variable.LT_posititon = lexTable.size - 1;
				flag_type_variable.type = TypeOfVar::STR;
				return true;
			}
			else
				return AnalyzeIdentifier(token, str_number, lexTable, idTable, flag_type_variable);
		}

		case 'd':
		{
			FST::FST declare(DECLARE(token));
			if (FST::execute(declare))
			{
				Add(lexTable, { LEX_DECLARE, str_number, LT_TI_NULLXDX });
				return true;
			}
			else
				return AnalyzeIdentifier(token, str_number, lexTable, idTable, flag_type_variable);
		}

		case 'r':
		{
			FST::FST _return(RETURN(token));
			if (FST::execute(_return))
			{
				Add(lexTable, { LEX_RETURN, str_number, LT_TI_NULLXDX });
				return true;
			}
			else
				return AnalyzeIdentifier(token, str_number, lexTable, idTable, flag_type_variable);
		}
		case 'p':
		{
			FST::FST print(PRINT(token));
			if (FST::execute(print))
			{
				Add(lexTable, { LEX_PRINT, str_number, LT_TI_NULLXDX });
				return true;
			}
			else
				return AnalyzeIdentifier(token, str_number, lexTable, idTable, flag_type_variable);
		}
		case '\'':
		{
			FST::FST stringLiteral(STRING_LITERAL(token));
			if (FST::execute(stringLiteral))
			{
				int i = idTable.IsId(token);

				if (i != LT_TI_NULLXDX)
					Add(lexTable, { LEX_LITERAL, str_number, i });
				else
				{
					idTable.Add({ "\0", (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexema == '=') ? idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).id : idTable.GetLexemaName() , IT::IDDATATYPE::STR, IT::IDTYPE::L, lexTable.size, str_number });
					idTable.table[idTable.size - 1].value.vstr.len = 0;
					int i = 0, j = 0;
					for (; token[i] != '\0'; i++)
					{
						idTable.table[idTable.size - 1].value.vstr.str[j] = token[i];
						idTable.table[idTable.size - 1].value.vstr.len++;
						j++;
					}
					idTable.table[idTable.size - 1].value.vstr.str[j] = '\0';

					Add(lexTable, { LEX_LITERAL, str_number,idTable.size - 1 });
				}
				return true;
			}
		}
		default:
		{
			FST::FST numberLiteral(INTEGER_LITERAL(token));
			if (FST::execute(numberLiteral))
			{
				int i = idTable.IsId(token);
				if (i != LT_TI_NULLXDX)
					Add(lexTable, { LEX_LITERAL, str_number, i });
				else
				{
					idTable.Add({ "\0", (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexema == '=') ? idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).id : idTable.GetLexemaName() , IT::IDDATATYPE::INT, IT::IDTYPE::L, lexTable.size, str_number });
					idTable.table[idTable.size - 1].value.vint = atoi(token);
					Add(lexTable, { LEX_LITERAL,str_number, idTable.size - 1 });
				}
				return true;
			}
			else
				return AnalyzeIdentifier(token, str_number, lexTable, idTable, flag_type_variable);
		}
		}
	}

	bool AnalyzeIdentifier(char* token, int str_number, LT::LexTable& lexTable, IT::IdTable& idTable, TypeOfVar& flagTypeVariable)
	{
		FST::FST id(IDENTIFICATOR(token));

		if (!FST::execute(id))
			throw ERROR_THROW_IN(93, str_number, -1);

		// main
		if (strcmp(token, "main") == 0)
		{
			for (int i = 0; i < lexTable.size; i++)
				if (lexTable.GetEntry(i).lexema == LEX_MAIN)
					throw ERROR_THROW_IN(94, str_number, -1);

			idTable.Add({ "\0", token, IT::IDDATATYPE::INT, IT::IDTYPE::F, lexTable.size, str_number});
			Add(lexTable, { LEX_MAIN, str_number, idTable.size - 1 });
			return true;
		}

		// Функция
		if (lexTable.GetEntry(lexTable.size - 1).lexema == LEX_FUNCTION
			&& lexTable.GetEntry(lexTable.size - 2).lexema == LEX_DATATYPE)
		{
			switch (flagTypeVariable.type)
			{
			case TypeOfVar::INT:
				idTable.Add({ "\0", token, IT::IDDATATYPE::INT, IT::IDTYPE::F, lexTable.size,str_number, str_number });
				break;
			case TypeOfVar::STR:
				idTable.Add({ "\0", token, IT::IDDATATYPE::STR, IT::IDTYPE::F, lexTable.size,str_number, str_number });
				break;
			}

			flagTypeVariable.type = TypeOfVar::DEF;
			Add(lexTable, { LEX_ID, str_number, idTable.size - 1 });

			return true;
		}

		// Параметр функции
		if (lexTable.GetEntry(lexTable.size - 1).lexema == 't')
		{
			for (int i = lexTable.size - 1; i > 0; i--)
			{
				if (lexTable.GetEntry(i).lexema == LEX_LEFTBRACE || lexTable.GetEntry(i).lexema == LEX_RIGHTBRACE)
					break;
				if (lexTable.GetEntry(i - 2).lexema == LEX_DATATYPE
					&& lexTable.GetEntry(i - 1).lexema == LEX_FUNCTION
					&& lexTable.GetEntry(i).lexema == LEX_ID
					&& idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F)
				{
					//if (idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).idxTI).id) != -1) // нужно исправить поиск родителя для перегрузки
					//	throw ERROR_THROW_IN(96, str_number, -1);

					switch (flagTypeVariable.type)
					{
					case TypeOfVar::INT:
						idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, token, IT::IDDATATYPE::INT, IT::IDTYPE::P, lexTable.size, str_number });
						idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity++;
						break;
					case TypeOfVar::STR:
						idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, token, IT::IDDATATYPE::STR, IT::IDTYPE::P, lexTable.size, str_number });
						idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity++;
						break;
					}

					flagTypeVariable.type = TypeOfVar::DEF;
					Add(lexTable, { LEX_ID, str_number, idTable.size - 1 });

					return true;
				}
			}
		}

		// Переменная
		if (lexTable.GetEntry(lexTable.size - 1).lexema == LEX_DATATYPE
			&& lexTable.GetEntry(lexTable.size - 2).lexema == LEX_DECLARE || lexTable.GetEntry(lexTable.size - 1).lexema == 't')
		{
			for (int i = lexTable.size - 1; i >= 0; i--)
			{
				// Поиск родительской функции
				if ((lexTable.GetEntry(i).lexema == LEX_ID || lexTable.GetEntry(i).lexema == LEX_MAIN)
					&& idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F)
				{
					//if (idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).idxTI).id) != -1)  // нужно исправить поиск родителя для перегрузки
					//	throw ERROR_THROW_IN(96, str_number, -1);

					switch (flagTypeVariable.type)
					{
					case TypeOfVar::INT:
						idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, token, IT::IDDATATYPE::INT, IT::IDTYPE::V, lexTable.size, str_number });
						break;
					case TypeOfVar::STR:
						idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, token, IT::IDDATATYPE::STR, IT::IDTYPE::V, lexTable.size, str_number });
						break;
					}

					flagTypeVariable.type = TypeOfVar::DEF;
					Add(lexTable, { LEX_ID, str_number, idTable.size - 1 });

					return true;
				}
			}
		}

		
		bool LeftBrace = false;
		for (int i = lexTable.size - 1; i >= 0; i--)
		{
			if (lexTable.GetEntry(i).lexema == LEX_LEFTBRACE)
				LeftBrace = true;
			if (LeftBrace && (lexTable.GetEntry(i).lexema == LEX_ID || lexTable.GetEntry(i).lexema == LEX_MAIN) 
				&& idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F)
			{
				int temp = idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).idxTI).id);
				if (temp != -1)
				{
					Add(lexTable, { LEX_ID,str_number,temp });
					idTable.table[temp].refCount++;
					return true;
				}
				else
				{
					temp = idTable.IsId(token);
					if (idTable.GetEntry(temp).idtype != IT::IDTYPE::F)
					{
						token[5] = '\0';
					}
					if (temp != -1 && idTable.GetEntry(temp).idtype == IT::IDTYPE::F)
					{
						Add(lexTable, { LEX_ID,str_number,temp });
						return true;
					}
					else throw ERROR_THROW_IN(97, str_number, -1);
				}
			}
		}
		return false;
	}
}