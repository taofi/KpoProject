#include "In.h"
#include "Error.h"
#include <fstream>
#include <locale>
#include <iostream>
#include <string.h>

namespace In
{
	IN getin(wchar_t infile[])
	{
		IN in;
		in.lines = 0;
		in.ignor = 0;
		in.size = 0;
		
		int constCode[256] = IN_CODE_TABLE;
		for (int i = 0; i < 256; i++)
			in.code[i] = constCode[i];
		std::ifstream ifs;
		ifs.open(infile, std::ifstream::in);
		if (ifs.fail())
		{
			throw ERROR_THROW(110);
		}
		int posSymb = 0;
		int posInLine = 0;

		ifs.seekg(0, std::ios::end);
		std::streampos fileSize = ifs.tellg();
		in.size = fileSize;						//get size of file
		ifs.seekg(0, std::ios::beg);
		std::cout << in.size << std::endl;

		wchar_t c = ifs.get();
		in.text = new unsigned char[in.size];
		while (ifs.good())
		{
			if (in.code[c] == IN::F)
			{
				throw ERROR_THROW_IN(111, in.lines, posInLine);
			}
			else if (in.code[c] == IN::I || (posSymb != 0 && c == ' ' && in.text[posSymb - 1] == c))
			{
				in.ignor++;
			}
			else if (in.code[c] == IN::T || in.code[c] == IN::O)
			{
				in.text[posSymb] = c;
				posSymb++;
			}
			else if (in.code[c] >= 0 && in.code[c] < 256)
			{
				in.text[posSymb] = in.code[c];
				posSymb++;
				if (c == IN_CODE_ENDL)
				{
					in.lines++;
					posInLine = 0;
				}
			}
			posInLine++;
			c = ifs.get();
		}
		in.text[posSymb] = 0;
		ifs.close();

		return in;
	}
}