#pragma once
#include "GRB.h"
#define GRB_ERROR_SERIES 600
namespace GRB
{
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
	Greibach greibach(NS('S'), TS('$'),
		10,

		Rule(NS('S'), GRB_ERROR_SERIES + 0,						// Синтаксическая ошибка. Неверная структура программы
			2,
			Rule::Chain(4, TS('m'), TS('{'), NS('N'), TS('}')),
			//Rule::Chain(9, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(8, TS('t'), TS('f'), TS('i'), NS('P'), TS('{'), NS('N'), TS('}'), NS('S'))
			//Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S'))
			//Rule::Chain(15, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('d'), NS('S'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S'))
		),

		Rule(NS('N'), GRB_ERROR_SERIES + 1,					// Синтаксическая ошибка. Ошибочный оператор
			16,
			Rule::Chain(2, TS('r'), TS(';')),
			Rule::Chain(3, TS('i'), NS('K'), TS(';')),
			Rule::Chain(3, TS('t'), TS('i'), TS(';')),
			Rule::Chain(3, TS('r'), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), TS('p'), NS('A'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), NS('K'), TS(';'), NS('N')),
			Rule::Chain(4, TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('p'), NS('A'), TS(';'), NS('N')),
			Rule::Chain(5, TS('w'), TS('('), NS('E'), TS(')'), NS('U')),
			Rule::Chain(5, TS('j'), TS('('), NS('E'), TS(')'), NS('U')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(6, TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(7, TS('j'), TS('('), NS('E'), TS(')'), NS('U'), TS('e'), NS('U')),
			Rule::Chain(5, TS('t'), TS('f'), TS('i'), NS('P'), NS('U'))
			
		),

		Rule(NS('E'), GRB_ERROR_SERIES + 2,					//Синтаксическая ошибка. Ошибка в выражении
			8,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(2, TS('i'), NS('K')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(3, TS('i'), NS('K'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M'))
		),

		Rule(NS('M'), GRB_ERROR_SERIES + 3, // Синтаксическая ошибка. Ошибка в операторах выражений
			2,

			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M'))

		),

		Rule(NS('F'), GRB_ERROR_SERIES + 4, // Синтаксическая ошибка. Ошибка в параметрах функции
			2,
			//Rule::Chain(0, TS('t')),
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),

		Rule(NS('W'), GRB_ERROR_SERIES + 5, // Синтаксическая ошибка. Ошибка в параметрах вызываемой функции
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(NS('U'), GRB_ERROR_SERIES + 6, // Синтаксическая ошибка. Ошибка в струторе блока
			4,
			Rule::Chain(2, TS('{'), TS('}')),
			Rule::Chain(3, TS('{'), TS('}'), NS('N')),
			Rule::Chain(3, TS('{'), NS('N'), TS('}')),
			Rule::Chain(4, TS('{'), NS('N'), TS('}'), NS('N'))
		),
		Rule(NS('P'), GRB_ERROR_SERIES + 7, // Синтаксическая ошибка. Ошибка в парметрах функции
			2,
			Rule::Chain(2, TS('('), TS(')')),
			Rule::Chain(3, TS('('), NS('F'), TS(')'))
		),
		Rule(NS('K'), GRB_ERROR_SERIES + 8, // Синтаксическая ошибка. Ошибка в вызове функции
			2,
			Rule::Chain(2, TS('('), TS(')')),
			Rule::Chain(3, TS('('), NS('W'), TS(')'))
		),
		Rule(NS('A'), GRB_ERROR_SERIES + 9, // Синтаксическая ошибка. Ошибка в задание параметров оброботчика события
			2,
			Rule::Chain(4, TS('l'), TS(','), TS('i'), NS('K')),
			Rule::Chain(4, TS('i'), TS(','), TS('i'), NS('K'))
		)
	);
}