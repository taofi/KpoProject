#include "stdafx.h"
#include "PolishNotation.h"
#include "MFST.h"
#include "Semantic.h"
#include "Generator.h"
#include "LexAnalysis2.h"
#include "GRB.h"


int _tmain(int argc, _TCHAR* argv[])
{

    argc = 1;
    argv[0] = (_TCHAR*)L"-in:D:\\projects\\KpoProject\\Debug\\in2.vks";
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
        LEXA::Tables tables;
        tables.global = new ENV::Environment("Global\0");
        INSTTB::InitTable(tables.instTable);
        OT::InitOprTable(tables.oprTable);
        LEXA::InitFunTable(tables);
        LEXA::LexicalAnalyzer(in, tables);
        cout << "\n--------------------------------------------------------------------------\n";
        cout << "               Ћексический анализ завершен успешно";
        cout << "\n--------------------------------------------------------------------------\n";
        tables.LexTable.PrintLexTable(L"TableOfLexems.txt");
       // LA::LexicalAnalyzer(in, tabel.LexTable, tabel.idTable);
        Log::WriteLine(log, "\n\n-------------------------------------\nтрасировка сематического анализатора\n-------------------------------------\n");
        MFST_TRACE_START
        MFST::Mfst mfst(tables, GRB::getGreibach());
        mfst.start(log);
        mfst.savededucation();
        mfst.printrules();
        SA::Semantic(tables);
       
        tables.LexTable.UnformattedPrintLexTable(L"UFTableOfLexems.txt");
        tables.idTable.PrintIdTable(L"TableOfIdentificators.txt");
        std::ofstream stream("TableEnv.txt");
        tables.global->Print(stream);
        cout << "\n--------------------------------------------------------------------------\n";
        cout << "               —емантический анализ завершен успешно";
        cout << "\n--------------------------------------------------------------------------\n";
        stream.close();
        GEN::Generator(tables, parm.gen);
        cout << "\n--------------------------------------------------------------------------\n";
        cout << "               √енераци€ кода прошла успешно";
        cout << "\n--------------------------------------------------------------------------\n";
        LEXA::Delete(tables);
        Log::Close(log);
        Out::Close(out);
    }
    catch (Error::ERROR e)
    {
        Log::WriteError(log, e);
        cout << e.id << " " << e.message << endl;
        //Out::WriteError(out, e);
    }

    return 0;
}
