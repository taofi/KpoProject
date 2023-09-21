#pragma once
#define IN_MAX_LEN_TEXT 1024*1024	
#define IN_CODE_ENDL '\n'
          /// 0       1      2      3      4      5      6     7		8	  9     a       b      c      d     e      f
#define IN_CODE_TABLE {\
/*0*/		IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*1*/		IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*2*/		IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*3*/		IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*4*/		IN::F, IN::F, IN::F, IN::F, IN::T, IN::T, IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, \
/*5*/		IN::T, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::T, IN::I,   '!', IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*6*/		IN::F, IN::F, IN::F, IN::F, IN::T, IN::T, IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, \
/*7*/		IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
			\
/*8*/		IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*9*/		IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*a*/		IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*b*/		IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*c*/		IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, \
/*d*/		IN::T, IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*e*/		IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, \
/*f*/		IN::T, IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
} 
//f - bad i - ignor t - good
namespace In
{
	struct IN
	{
		enum { T = 1024, F = 2048, I = 4096, S = 8192, P = 16000, Q = 8 };
		int size;
		int lines;
		int ignor;
		unsigned char* text;
		int code[256];
	};
	IN getin(wchar_t infile[]);
};
