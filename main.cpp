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


	//// Параметры задаваемые по ссылке, чтобы они менялись автоматом
	//CTEMP temp = 11;                                     // температура газа в системе в град Цельсия
	//PRESSURE pres = physics::convert::ConvertMPAtoPA(14);                  // давление в системе в Па
	//
	//fittings::Valve valve(
	//	fittings::ValveSettings(&pres, &temp)
	//	.SetValveRadius(math::convert::ConvertMillimeterToMeter(300))				       	  // в мм
	//	.SetPipeRadius(math::convert::ConvertMillimeterToMeter(300))					   	  // в мм
	//	.SetStreamMolarMass(physics::constants::_METHAN_MOLAR_MASS));

	//assert(valve.IsClosed());

	//valve.SetValveStance(1.0f);          // полностью открываем клапан

	std::cout << "Gaz mass consumption is " << valve.GetMassConsumption() << " kg/sec" << std::endl;
	std::cout << "Gaz volume consumption is " << valve.GetVolumeConsumption() << " m3/sec" << std::endl;
}