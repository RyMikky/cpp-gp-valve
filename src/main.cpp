﻿#include "handler.h"

#include <cassert>
#include <iostream>


int main(char args, char** argv) {

	/*
		Модель клапана. Среда: метан (100 %), параметры: 12-14МПа, 10-15 град С;
		Расположение: на участке трубы, сопротивлением трубы пренебрегаем,
		за трубой емкость «бесконечного» объема, в емкости поддерживается давление 12-14 МПа;
		Требуется: определить расход в зависимости от проходного сечения клапана.
	*/

	/*
		Принимаем в качестве условий рассчёта факты:
		1) Процесс протекания газа адиабатический (без изменения температуры)
		2) Поток находится в состоянии идеального газа
		3) Потерями на трение и сопрротивление кромки диафрагмы пренебрегаем
	*/

	/*
		Для работы приложения необходимы: 
		1) Система интерпретации языка Python 3.9+
		2) Библиотеки numpy и matplotlib (pip3 install numpy, etc)
		3) Корректно прописанные пути для линковки хеддеров, библиотек и python

			Например:
			\dev\python\include
			\dev\python\Lib\site-packages\numpy\core\include
			\dev\python\libs

		Обёртка matplotlib-cpp работает только в конфигурации Release.
		Debug компилируется, но во время отладки PyImport_Import(PyObject*)
		возвращает nullptr, что приводит к возникновению исключения
	*/

	/*
		Варианты запуска для примера
		-t=15 -g=methane -s=15m -p=100 -a=75 -i=12 -o=11.95
		--text -n=report_file -t=15 -g=methane -s=15m -p=100 -a=75 -i=12 -o=11.95
		--image --text -n=report_file -t=15 -g=methane -s=15m -p=100 -a=75 -i=12 -o=11.95

		-t=0 -g=methane -s=15m -p=100 -a=75 -i=150 -d=0.0 -l=2.5 -e=0.5 --atm
		-t=0 -g=methane -s=15m --text -n=report_file -p=100 -a=75 -i=150 -d=0.0 -l=2.5 -e=0.5 --atm
		-t=0 -l=2.5 -s=15m --text -n=report_file -p=100 -a=75 --image -i=150 -d=0.0 -e=0.5 --atm -g=methane
	*/

	setlocale(LC_ALL, "Russian");
	setlocale(LC_NUMERIC, "English");

	handler::Handler(args, argv).Run();
}