#pragma once
#include "GRB.h"
#define GRB_ERROR_SERIES 600
namespace GRB
{
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
	Greibach greibach(NS('S'), TS('$'),
		6,

		Rule(NS('S'), GRB_ERROR_SERIES + 0,						// Синтаксическая ошибка. Неверная структура программы
			4,
			Rule::Chain(4, TS('m'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(9, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(10, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), NS('S')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S'))
			//Rule::Chain(15, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('d'), NS('S'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S'))
		),

		Rule(NS('N'), GRB_ERROR_SERIES + 1,					// Синтаксическая ошибка. Ошибочный оператор
			16,
			Rule::Chain(3, TS('t'), TS('i'), TS(';')),
			Rule::Chain(3, TS('r'), NS('E'), TS(';')),
			Rule::Chain(3, TS('{'), NS('N'), TS('}')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), TS('('), TS(')'), TS(';')),
			Rule::Chain(5, TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), TS(';')),
			Rule::Chain(4, TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(5, TS('w'), TS('('), NS('E'), TS(')'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('('), TS(')'), TS(';'), NS('N')),
			Rule::Chain(6, TS('i'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(6, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), NS('N')),
			Rule::Chain(6, TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(7, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), NS('N'))
			
		),

		Rule(NS('E'), GRB_ERROR_SERIES + 2,					//Синтаксическая ошибка. Ошибка в выражении
			9,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(3, TS('i'), TS('('), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))


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
		)

	);
}