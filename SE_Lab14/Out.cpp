#define _CRT_SECURE_NO_WARNINGS
#include "Out.h"
#include "In.h"
#include "Error.h"
#include <fstream>
#include <stdio.h>  
#include <ctime>
#include <stdlib.h>
#include <string>
#include <iostream>

namespace Out
{
	OUT getout(wchar_t outfile[])
	{
		OUT a;
		wcscpy_s(a.outfile, outfile);
		a.stream = new std::ofstream(outfile, std::ofstream::out);
		a.stream = new std::ofstream;
		a.stream->open(outfile);
		if (a.stream->fail()) {
			throw ERROR_THROW(113);
		}
		wcscpy_s(a.outfile, outfile);
		return a;
	}

	void WriteLine(OUT out, const char* c, ...)
	{
		const char** pc = &c;
		int len = 0;
		while (*pc != "")
		{
			len += strlen(*pc);
			pc++;
		}
		char* str = new char[len + 1];
		str[0] = 0;
		pc = &c;
		while (*pc != "")
		{
			strcat(str, *pc);
			pc++;
		}
		out.stream->write(str, len);
		delete[] str;
	}

	void WriteOut(OUT out, In::IN in)
	{
		*out.stream <<  in.text << std::endl;
	}

	void WriteError(OUT log, Error::ERROR error)
	{
		*log.stream << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ",позиция " << error.inext.col << std::endl;
	}

	void Close(OUT log)
	{
		log.stream->close();
		delete log.stream;
		log.stream = NULL;
	}
}