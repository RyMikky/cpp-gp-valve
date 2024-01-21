#include "valve.h"
#include "console.h"

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

	setlocale(LC_ALL, "Russian");
	setlocale(LC_NUMERIC, "English");

	settings::Settings settings = console::ParseCommandLine(args, argv);
	fittings::Valve valve(settings);

	std::cout << "Gaz mass consumption is " << valve.GetMassConsumption() << " kg/sec" << std::endl;
	std::cout << "Gaz volume consumption is " << valve.GetVolumeConsumption() << " m3/sec" << std::endl;
}