#pragma once

#include "defines.h"
#include "stdint.h"
#include "math.h"
#include "physics.h"


namespace fittings {

	struct ValveSettings {
		STREAM_PREASSURE        // давленние потока газа
		STREAM_MOL_MASS         // молярная масса газа
		STREAM_С_TEMP           // температура потока в цельсиях
		VALVE_RADIUS            // радиус клапана
		PIPE_RADIUS             // радиус труб
		VALVE_STANCE            // процент открытия клапана

		ValveSettings() = delete;
		ValveSettings(PRESSURE_PTR, CTEMP_PTR);
		
		// Устанавливаает давление газа в системе
		ValveSettings& SetStreamPressure(PRESSURE_PTR);
		// Задаёт молярную массу газа, поданного в систему
		ValveSettings& SetStreamMolarMass(MASS);
		// Задёт температуру потока в градусах Цельсия
		ValveSettings& SetStreamTemperature(CTEMP_PTR);
		// Задает радиус пропускного отверстия клапана
		ValveSettings& SetValveRadius(RADIUS);
		// Задаёт радиус сеченния труб
		ValveSettings& SetPipeRadius(RADIUS);
		// Задаёт процент открытия клапана
		ValveSettings& SetValveStance(PRECENT);
	};
	
	class Valve {
	public:

		explicit Valve(const ValveSettings&);

		// Возвращает расход газа проходящегго через клапан с установленным параментрами в м.куб/с
		CONSUMPTION GetСonsumption() const;

		FLAG IsClosed() const;
		FLAG IsOpened() const;
		
		// Задаёт радиус сечерения клапана
		Valve& SetValveRadius(RADIUS);
		// Задаёт радиус сеченния трубы
		Valve& SetPipeRadius(RADIUS);
		// Задаёт давление потока
		Valve& SetStreamPreassure(PRESSURE_PTR);
		// Задаёт молярную массу газа в потоке
		Valve& SetStreamMolarMass(MASS);
		// Задаёт темературу потока в градусах Цельсия
		Valve& SetStreamTemperature(CTEMP_PTR);
		// Задаёт процент открытия клапана
		Valve& SetValveStance(PRECENT);

	private:

		STREAM_PREASSURE
		STREAM_MOL_MASS
		STREAM_С_TEMP
		VALVE_RADIUS
		PIPE_RADIUS
		VALVE_STATUS
		VALVE_STANCE

		// Выставляет флаг открытия клапана
		VOID CheckValveStatus();
		// Проверяет что заданные параметры введены корректно
		VOID CheckParamIsCorrect();

		// Переводит температуру из цельсий в кельвины
		KTEMP TransmuteCelsuimToKelvin(CTEMP);

		// Переводит температуру из кельвина в цельсий
		CTEMP TransmuteKelvinToCelsuim(KTEMP);
		
		// Возвращает площадь сечения клапана
		VSQARE GetValveSquare() const;

		// Возвращает эффективность клапана
		EFFECTIVENESS GetValveEffectiveness() const;
	};


} // namespace fittings