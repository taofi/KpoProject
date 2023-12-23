#include "stdafx.h"

namespace Error
{
	//    0 - 99 - системные ошибки
	// 100 - 109 - ошибки параметров
	// 110 - 119 - ошибки открытия и чтения файлов

	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"),
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),
		ERROR_ENTRY(30, "Таблица инструкций: недопустимый индекс инструкции"),
		ERROR_ENTRY(31, "Таблица инструкций: недопустимая система счисления"),
		ERROR_ENTRY(32, ""),
		ERROR_ENTRY(33, ""),
		ERROR_ENTRY(34, ""),
		ERROR_ENTRY(35, "Переполнение количества идентификаторов в окружение"),
		ERROR_ENTRY(36, "Переполнение количества объявлений идентификаторов в окружение"),
		ERROR_ENTRY(37, "Таблица операторов: неизвестный оператор"),
		ERROR_ENTRY(38, "Таблица операторов: длинна оператора привышает допустимый размер"),
		ERROR_ENTRY(39, ""),
		ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50),
		// ошибки таблиц
		ERROR_ENTRY(60, "Таблица лексем: ошибка при добавлении элемента, таблица переполнена"),
		ERROR_ENTRY(61, "Таблица лексем: ошибка при получени элемента по индексу, индекс за границами таблицы"),
		ERROR_ENTRY_NODEF(62),
		ERROR_ENTRY(63, "Таблица лексем: не удалось открыть поток для вывода таблицы"),
		ERROR_ENTRY_NODEF(64), 
		ERROR_ENTRY(65, "Таблица идентификаторов: название идентификатора больше пяти символов"),
		ERROR_ENTRY(66, "Таблица идентификаторов: ошибка при добавлении элемента, таблица переполнена"),
		ERROR_ENTRY(67, "Таблица идентификаторов: ошибка при получени элемента по индексу, индекс за границами таблицы"),
		ERROR_ENTRY_NODEF(68), ERROR_ENTRY_NODEF(69),
		ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80),

		// ошибки лексического анализатора
		ERROR_ENTRY(90, "Лексический анализатор. Слово не распознано"),
		ERROR_ENTRY(91, "Лексический анализатор. Строковый литерал превышает допустимый размер"),
		ERROR_ENTRY(92, "Лексический анализатор. Строковый литерал не распознан"),
		ERROR_ENTRY(93, "Лексический анализатор. Идентификатор не распознан"),
		ERROR_ENTRY(94, "Лексический анализатор. Неверный вид идентификатора"),
		ERROR_ENTRY(95, "Лексический анализатор. Неизвестный тип переменной"),
		ERROR_ENTRY(96, "Лексический анализатор. Литерал не распознан"),
		ERROR_ENTRY(97, "Лексический анализатор. Неизвестная переменная"),
		ERROR_ENTRY_NODEF(98),
		ERROR_ENTRY_NODEF(99),
		ERROR_ENTRY(100, "Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),

		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113, "Ошибка при создании файла выхода (-out)"),
		ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115), ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117),
		ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120, "Семантическая ошибка. Функция объявлена несколько раз"),
		ERROR_ENTRY(121, "Семантическая ошибка. Переменная объявлена несколько раз"),
		ERROR_ENTRY(122, "Семантическая ошибка. Количество аргументов вызова не совпадает с вызываемой функцией"),
		ERROR_ENTRY(123, "Семантическая ошибка. Превышено максимальное количество аргументов функции"),
		ERROR_ENTRY(124, "Семантическая ошибка. Невозможно преобразовать типы данных"),
		ERROR_ENTRY(125, "Семантическая ошибка. Тип возвращаемого выражения не равен типу функции"),
		ERROR_ENTRY(126, "Семантическая ошибка. Неизвестная переменная"),
		ERROR_ENTRY(127, "Семантическая ошибка. Не найден прототип функции"),
		ERROR_ENTRY(128, "Семантическая ошибка. Переменная не может иметь тип nodef"),
		ERROR_ENTRY(129, "Семантическая ошибка. Строки не могу использоваться в булевых выражениях"),
		ERROR_ENTRY(130, "Семантическая ошибка. Ожидалось булевое вырожение"),
		ERROR_ENTRY(131, "Семантическая ошибка. Неверные типы параметров обработчика событий"),
		ERROR_ENTRY(132, "Семантическая ошибка. В функции ожидался оператор return"),
		ERROR_ENTRY(133, "Возможно перполнение переменной"), 
		ERROR_ENTRY_NODEF(134),
		ERROR_ENTRY_NODEF(135), ERROR_ENTRY_NODEF(136), ERROR_ENTRY_NODEF(137), ERROR_ENTRY_NODEF(138), ERROR_ENTRY_NODEF(139),
		ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),
		ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "Синтаксическая ошибка. Неверная структура программы"),
		ERROR_ENTRY(601, "Синтаксическая ошибка. Ошибочный оператор"),
		ERROR_ENTRY(602, "Синтаксическая ошибка. Ошибка в выражении"),
		ERROR_ENTRY(603, "Синтаксическая ошибка. Ошибка в операторах выражений"),
		ERROR_ENTRY(604, "Синтаксическая ошибка. Ошибка в объявление параметров функции"),
		ERROR_ENTRY(605, "Синтаксическая ошибка. Ошибка в параметрах вызова функции"),
		ERROR_ENTRY(606, "Синтаксическая ошибка. Ошибка в структуре блока"),
		ERROR_ENTRY(607, "Синтаксическая ошибка. Ошибка в параметрах функции"),
		ERROR_ENTRY(608, "Синтаксическая ошибка. Ошибка в вызове параметрах вызова функции"),
		ERROR_ENTRY(609, "Синтаксическая ошибка. Ошибка в задание параметров обработчика события"),
		ERROR_ENTRY_NODEF(610),ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700),
		ERROR_ENTRY_NODEF100(800),
	};
	ERROR geterror(int id)
	{
		if (id > ERROR_MAX_ENTRY - 1 || id < 1)
			return errors[0];
		return errors[id];
	}
	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		if (id > ERROR_MAX_ENTRY - 1 || id < 1)
			return errors[0];
		else
		{
			errors[id].inext.col = col;
			errors[id].inext.line = line;
			return errors[id];
		}
	}
};