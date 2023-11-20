#include "valve.h"

#include <cassert>
#include <iostream>

int main(char argv, char** args) {

	/*
		Модель клапана. Среда: метан (100 %), параметры: 12-14МПа, 10-15 град С;
		Расположение: на участке трубы, сопротивлением трубы пренебрегаем,
		за трубой емкость «бесконечного» объема, в емкости поддерживается давление 12-14 МПа;
		Требуется: определить расход в зависимости от проходного сечения клапана.
	*/


	// Параметры задаваемые по ссылке, чтобы они менялись автоматом
	CTEMP temp = 11;                                     // температура газа в системе в град Цельсия
	PRESSURE pres = physics::convert::ConvertMPAtoPA(14);                  // давление в системе в Па
	
	fittings::Valve valve(
		fittings::ValveSettings(&pres, &temp)
		.SetValveRadius(math::convert::ConvertMillimeterToMeter(300))				       	  // в мм
		.SetPipeRadius(math::convert::ConvertMillimeterToMeter(300))					   	  // в мм
		.SetStreamMolarMass(physics::constants::_METHAN_MOLAR_MASS));

	assert(valve.IsClosed());

	valve.SetValveStance(1.0f);          // полностью открываем клапан

	std::cout << "Gaz consumption is " << valve.GetСonsumption() << " m3/sec" << std::endl;
}