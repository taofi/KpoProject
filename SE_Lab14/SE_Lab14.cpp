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

int _tmain(int argc, _TCHAR* argv[])
{
    setlocale(LC_ALL,"rus");
    FST::FST fst1(
        "aaabbbaba",
        4,
        FST::NODE(3, FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('a', 1)),
        FST::NODE(1, FST::RELATION('b', 2)),
        FST::NODE(1, FST::RELATION('a', 3)),
        FST::NODE()
    );
    if (FST::execute(fst1))
        std::cout << fst1.string << " распознана\n";
    else
        std::cout << fst1.string << " не распознана\n";
    FST::FST fst2(
        "aaabbbabba",
        4,
        FST::NODE(3, FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('a', 1)),
        FST::NODE(1, FST::RELATION('b', 2)),
        FST::NODE(1, FST::RELATION('a', 3)),
        FST::NODE()
    );
    if (FST::execute(fst2))
        std::cout << fst2.string << " распознана\n";
    else
        std::cout << fst2.string << " не распознана\n";
    FST::FST fst41(
        "ippcpopnpnpnpcpoppr",
        7,
        FST::NODE(1, FST::RELATION('i', 1)),//0
        FST::NODE(4, FST::RELATION('p', 1), FST::RELATION('p', 2), FST::RELATION('p', 4), FST::RELATION('p', 5)),//1
        FST::NODE(3, FST::RELATION('c', 3), FST::RELATION('o', 3), FST::RELATION('n', 3)),//2
        FST::NODE(4, FST::RELATION('p', 3), FST::RELATION('p', 2), FST::RELATION('p', 4), FST::RELATION('p', 5)),//3
        FST::NODE(2, FST::RELATION('p', 4), FST::RELATION('p', 5)),//4
        FST::NODE(1, FST::RELATION('r', 6)),//5
        FST::NODE()//6
    );
    if (FST::execute(fst41))
        std::cout << fst41.string << " распознана\n";
    else
        std::cout << fst41.string << " не распознана\n";
    FST::FST fst42(
        "ipcpr",
        7,
        FST::NODE(1, FST::RELATION('i', 1)),//0
        FST::NODE(4, FST::RELATION('p', 1), FST::RELATION('p', 2), FST::RELATION('p', 4), FST::RELATION('p', 5)),//1
        FST::NODE(3, FST::RELATION('c', 3), FST::RELATION('o', 3), FST::RELATION('n', 3)),//2
        FST::NODE(4, FST::RELATION('p', 3), FST::RELATION('p', 2), FST::RELATION('p', 4), FST::RELATION('p', 5)),//3
        FST::NODE(2, FST::RELATION('p', 4), FST::RELATION('p', 5)),//4
        FST::NODE(1, FST::RELATION('r', 6)),//5
        FST::NODE()//6
    );
    if (FST::execute(fst42))
        std::cout << fst42.string << " распознана\n";
    else
        std::cout << fst42.string << " не распознана\n";
    FST::FST fst43(
        "ipcp",
        7,
        FST::NODE(1, FST::RELATION('i', 1)),//0
        FST::NODE(4, FST::RELATION('p', 1), FST::RELATION('p', 2), FST::RELATION('p', 4), FST::RELATION('p', 5)),//1
        FST::NODE(3, FST::RELATION('c', 3), FST::RELATION('o', 3), FST::RELATION('n', 3)),//2
        FST::NODE(4, FST::RELATION('p', 3), FST::RELATION('p', 2), FST::RELATION('p', 4), FST::RELATION('p', 5)),//3
        FST::NODE(2, FST::RELATION('p', 4), FST::RELATION('p', 5)),//4
        FST::NODE(1, FST::RELATION('r', 6)),//5
        FST::NODE()//6
    );
    if (FST::execute(fst43))
        std::cout << fst43.string << " распознана\n";
    else
        std::cout << fst43.string << " не распознана\n";
    FST::FST fst44(
        "ipcppppr",
        7,
        FST::NODE(1, FST::RELATION('i', 1)),//0
        FST::NODE(4, FST::RELATION('p', 1), FST::RELATION('p', 2), FST::RELATION('p', 4), FST::RELATION('p', 5)),//1
        FST::NODE(3, FST::RELATION('c', 3), FST::RELATION('o', 3), FST::RELATION('n', 3)),//2
        FST::NODE(4, FST::RELATION('p', 3), FST::RELATION('p', 2), FST::RELATION('p', 4), FST::RELATION('p', 5)),//3
        FST::NODE(2, FST::RELATION('p', 4), FST::RELATION('p', 5)),//4
        FST::NODE(1, FST::RELATION('r', 6)),//5
        FST::NODE()//6
    );
    if (FST::execute(fst44))
        std::cout << fst44.string << " распознана\n";
    else
        std::cout << fst44.string << " не распознана\n";
    FST::FST fst45(
        "pcpnpopr",
        7,
        FST::NODE(1, FST::RELATION('i', 1)),//0
        FST::NODE(4, FST::RELATION('p', 1), FST::RELATION('p', 2), FST::RELATION('p', 4), FST::RELATION('p', 5)),//1
        FST::NODE(3, FST::RELATION('c', 3), FST::RELATION('o', 3), FST::RELATION('n', 3)),//2
        FST::NODE(4, FST::RELATION('p', 3), FST::RELATION('p', 2), FST::RELATION('p', 4), FST::RELATION('p', 5)),//3
        FST::NODE(2, FST::RELATION('p', 4), FST::RELATION('p', 5)),//4
        FST::NODE(1, FST::RELATION('r', 6)),//5
        FST::NODE()//6
    );
    if (FST::execute(fst45))
        std::cout << fst45.string << " распознана\n";
    else
        std::cout << fst45.string << " не распознана\n";
    FST::FST fst46(
        "ipcpnpopr",
        7,
        FST::NODE(1, FST::RELATION('i', 1)),//0
        FST::NODE(4, FST::RELATION('p', 1), FST::RELATION('p', 2), FST::RELATION('p', 4), FST::RELATION('p', 5)),//1
        FST::NODE(3, FST::RELATION('c', 3), FST::RELATION('o', 3), FST::RELATION('n', 3)),//2
        FST::NODE(4, FST::RELATION('p', 3), FST::RELATION('p', 2), FST::RELATION('p', 4), FST::RELATION('p', 5)),//3
        FST::NODE(2, FST::RELATION('p', 4), FST::RELATION('p', 5)),//4
        FST::NODE(1, FST::RELATION('r', 6)),//5
        FST::NODE()//6
    );
    if (FST::execute(fst46))
        std::cout << fst46.string << " распознана\n";
    else
        std::cout << fst46.string << " не распознана\n";
    FST::FST fst47(
        "ipr",
        7,
        FST::NODE(1, FST::RELATION('i', 1)),//0
        FST::NODE(4, FST::RELATION('p', 1), FST::RELATION('p', 2), FST::RELATION('p', 4), FST::RELATION('p', 5)),//1
        FST::NODE(3, FST::RELATION('c', 3), FST::RELATION('o', 3), FST::RELATION('n', 3)),//2
        FST::NODE(4, FST::RELATION('p', 3), FST::RELATION('p', 2), FST::RELATION('p', 4), FST::RELATION('p', 5)),//3
        FST::NODE(2, FST::RELATION('p', 4), FST::RELATION('p', 5)),//4
        FST::NODE(1, FST::RELATION('r', 6)),//5
        FST::NODE()//6
    );
    if (FST::execute(fst47))
        std::cout << fst47.string << " распознана\n";
    else
        std::cout << fst47.string << " не распознана\n";
    FST::FST fst9(
        "aaabab",
        4,
        FST::NODE(3, FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('a', 1)),
        FST::NODE(1, FST::RELATION('b', 2)),
        FST::NODE(1, FST::RELATION('a', 3)),
        FST::NODE()
    );
    if (FST::execute(fst9))
        std::cout << fst9.string << " распознана\n";
    else
        std::cout << fst9.string << " не распознана\n";
    FST::FST fst10(
        "aaabbbacba",
        4,
        FST::NODE(3, FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('a', 1)),
        FST::NODE(1, FST::RELATION('b', 2)),
        FST::NODE(1, FST::RELATION('a', 3)),
        FST::NODE()
    );
    if (FST::execute(fst10))
        std::cout << fst10.string << " распознана\n";
    else
        std::cout << fst10.string << " не распознана\n";
    /*Log::LOG log = Log::INITLOG;
    Out::OUT out = Out::INITOUT;
    try
    {
        Parm::PARM parm = Parm::getparm(argc, argv);
        log = Log::getlog(parm.log);
        out = Out::getout(parm.out);
        Log::WriteLine(log, (char*)"text: ", (char*)" without error \n", "");
        Log::WriteLine(log, (wchar_t*)L"text: ", (wchar_t*)L" without error \n", L"");
        Log::WriteLog(log);
        Log::WriteParm(log, parm);
        In::IN in = In::getin(parm.in);
        Out::WriteOut(out, in);
        Log::WriteIn(log, in);
        Log::Close(log);
        Out::Close(out);
    }
    catch (Error::ERROR e)
    {
        Log::WriteError(log, e);
        Out::WriteError(out, e);
    }
    */
    /*std::cout << "-- test get::getin  --" << std::endl;
    try
    {
        Parm::PARM parm = Parm::getparm(argc, argv);
        In::IN in = In::getin(parm.in);
        std::cout << in.text << std::endl;
        std::cout << "Всего симолов: " << in.size << std::endl;
        std::cout << "Всего строк: " << in.lines << std::endl;
        std::cout << "Пропушено: " << in.ignor << std::endl;
    }
    catch (Error::ERROR e)
    {
        std::cout << "Error " << e.id << ": " << e.message << " " << e.inext.line << ", " << e.inext.col << "\n";
    }*/
    
    /*std::cout << "-- test Parm::getparm  --" << std::endl;
    try
    {
        Parm::PARM parm = Parm::getparm(argc, argv);
        std::wcout << "-in:" << parm.in << ", -out:" << parm.out << ", -log" << parm.log << std::endl;
    }
    catch(Error::ERROR e)
    {
        std::cout << "Error " << e.id << ": " << e.message << std::endl;
    }
    */
    /*std::cout << "-- test Error::geterror  --" << std::endl;
    try { throw ERROR_THROW(100); }
    catch (Error::ERROR e) {
        std::cout << "Ошибка " << e.id << ": " << e.message << "\n\n";
    };

    std::cout << "-- test Error::geterrorin  --" << std::endl;
    try { throw ERROR_THROW_IN(111, 7, 7); }
    catch (Error::ERROR e) {
        std::cout << "Ошибка " << e.id << ": " << e.message << ", " << e.inext.line << ", " << e.inext.col << "\n\n";
    };*/
    //system("pause");
    return 0;
}