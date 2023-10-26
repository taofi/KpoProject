#pragma once
#define IN_MAX_LEN_TEXT 1024*1024	
#define IN_CODE_ENDL '\n'

//	  0       1      2      3      4      5      6      7      8      9      A      B      C      D      E      F
#define IN_CODE_TABLE {\
	IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T,  '|' , IN::T, IN::T,	IN::T, IN::T, IN::T,\
	IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T,\
	IN::S,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::S, IN::S,	IN::S, IN::O, IN::O, IN::S,	IN::O, IN::T, IN::O,\
	IN::T,	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::S, IN::T,	IN::O, IN::T, IN::T,\
	IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T, IN::I,	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	IN::T,  IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::S, IN::T, IN::S, IN::T, IN::T,\
																													\
	IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T,\
	IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T,\
	IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T,\
	IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T,\
    IN::T,  IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	IN::T,  IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T,\
    IN::T,	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
    IN::T,  IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T, IN::T,	IN::T, IN::T, IN::T\
}

namespace In
{
	struct IN
	{
		enum { T = 1024, F = 2048, I = 4096, S = 8192, O = 16384 };
		int size;
		int lines;
		int ignor;
		unsigned char* text;
		int code[256] = IN_CODE_TABLE;
	};
	IN getin(wchar_t infile[]);
}