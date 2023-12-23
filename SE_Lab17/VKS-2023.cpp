#include "stdafx.h"
#include "MFST.h"
#include "Semantic.h"
#include "Generator.h"
#include "LexAnalysis2.h"
#include "GRB.h"
#include <queue>


int _tmain(int argc, _TCHAR* argv[])
{

   // argc = 1;
    //argv[0] = (_TCHAR*)L"-in:D:\\projects\\KpoProject\\Debug\\in2.vks";
    setlocale(LC_ALL, "Rus");

    stack<Error::ERROR> warningQ;
    Log::LOG log = Log::INITLOG;
    LEXA::Tables tables;
    try
    {
        Parm::PARM parm = Parm::getparm(argc, argv);
        log = Log::getlog(parm.log);
        Log::WriteLog(log);
        Log::WriteParm(log, parm);
        In::IN in = In::getin(parm.in);
        Log:WriteIn(log, in);
        tables.global = new ENV::Environment("Global\0");
        INSTTB::InitTable(tables.instTable);
        OT::InitOprTable(tables.oprTable);
        LEXA::InitFunTable(tables);
        LEXA::LexicalAnalyzer(in, tables);
       
        cout << "\n--------------------------------------------------------------------------\n";
        cout << "               Лексический анализ завершен успешно";
        cout << "\n--------------------------------------------------------------------------\n";
        Log::WriteLine(log, "\n\n-------------------------------------\n Лексический анализ завершен успешно\n-------------------------------------\n\n");
        Log::WriteLine(log, "\n\n----------------------------------------------\n Таблица лексем\n-------------------------------------------------\n\n");
        tables.LexTable.PrintLexTable(*log.stream);
       // LA::LexicalAnalyzer(in, tabel.LexTable, tabel.idTable);
        Log::WriteLine(log, "\n\n\n-------------------------------------\nтрасировка сематического анализатора\n-------------------------------------\n");
        MFST_TRACE_START
        MFST::Mfst mfst(tables, GRB::getGreibach());
        mfst.start(log);
        mfst.savededucation();
        mfst.printrules();
        SA::Semantic(tables, &warningQ);
        tables.idTable.PrintIdTable(*log.stream);
        std::ofstream stream("TableEnv.txt");
        tables.global->Print(stream);
        cout << "\n--------------------------------------------------------------------------\n";
        cout << "               Семантический анализ завершен успешно";
        cout << "\n--------------------------------------------------------------------------\n";
        stream.close();
        GEN::Generator(tables, parm.out);
        cout << "\n--------------------------------------------------------------------------\n";
        cout << "               Генерация кода прошла успешно";
        cout << "\n--------------------------------------------------------------------------\n";
        while (!warningQ.empty())
        {
            Error::ERROR error = warningQ.top();
            warningQ.pop();
            Log::WriteWarning(log, error);
            if (error.inext.line == -1)
                cout << "Предупреждение " << error.id << ": " << error.message << std::endl;
            else if (error.inext.col == -1)
                cout << "Предупреждение " << error.id << ": " << error.message << ", строка " << error.inext.line << std::endl;
            else
                cout << "Предупреждение " << error.id << ": " << error.message << ", строка " << error.inext.line << ",позиция " << error.inext.col << std::endl;
        }
        
       
    }
    catch (Error::ERROR error)
    {
        while (!warningQ.empty())
        {
            Error::ERROR error = warningQ.top();
            warningQ.pop();
            Log::WriteWarning(log, error);
            if (error.inext.line == -1)
                cout << "Предупреждение " << error.id << ": " << error.message << std::endl;
            else if (error.inext.col == -1)
                cout << "Предупреждение " << error.id << ": " << error.message << ", строка " << error.inext.line << std::endl;
            else
                cout << "Предупреждение " << error.id << ": " << error.message << ", строка " << error.inext.line << ",позиция " << error.inext.col << std::endl;
        }
        Log::WriteError(log, error);
        if (error.inext.line == -1)
            cout << "Ошибка " << error.id << ": " << error.message << std::endl;
        else if (error.inext.col == -1)
            cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << std::endl;
        else
            cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ",позиция " << error.inext.col << std::endl;
        //Out::WriteError(out, e);
        LEXA::Delete(tables);
        Log::Close(log);
    }

    return 0;
}
