#include <tchar.h>
#include <iostream>
#include <locale>
#include <cwchar>

#include "Out.h"
#include "Error.h"
#include "In.h"
#include "Log.h"
#include "Parm.h"
#include "FSt.h"
#include "LexAnalysis.h"
#include "LT.h"
#include "IT.h"

int _tmain(int argc, _TCHAR* argv[])
{

    //argc = 1;
    //argv[0] = (_TCHAR*)L"-in:D:\\KpoLabs\\SeLab17_copy\\ErorrTests\\in65.txt";

    setlocale(LC_ALL, "Rus");

    Log::LOG log = Log::INITLOG;
    Out::OUT out = Out::INITOUT;
    try
    {
        Parm::PARM parm = Parm::getparm(argc, argv);

        log = Log::getlog(parm.log);
        out = Out::getout(parm.out);

        Log::WriteLog(log);
        Log::WriteParm(log, parm);
        In::IN in = In::getin(parm.in);
    Log:WriteIn(log, in);
        Out::WriteOut(out, in);

        LT::LexTable lexTable;
        IT::IdTable	idTable;

        LA::LexicalAnalyzer(in, lexTable, idTable);

        lexTable.PrintLexTable(L"TableOfLexems.txt");
        idTable.PrintIdTable(L"TableOfIdentificators.txt");

        lexTable.Delete();
        idTable.Delete();
        Log::Close(log);
        Out::Close(out);
    }
    catch (Error::ERROR e)
    {
        Log::WriteError(log, e);
        Out::WriteError(out, e);
    }

    return 0;
}
