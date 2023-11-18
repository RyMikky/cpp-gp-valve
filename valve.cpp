#include "valve.h"
#include <cmath>
#include <iostream>
#include <cassert>
#include <exception>

namespace fittings {

	using namespace math;
	using namespace physics;

	ValveSettings::ValveSettings(PRESSURE_PTR pres, CTEMP_PTR temp) 
		: _pres(pres), _c_temp(temp) {
		_m_mass = 0.0f;
		_p_rad = 0.0f;
		_v_rad = 0.0f;
		_scale = 0.0f;
	}

	// -------------------------- сеттеры структуры настройки клапана ---------------------------

	ValveSettings& ValveSettings::SetStreamPressure(PRESSURE_PTR pres) {
		_pres = pres;
		return *this;
	}
	ValveSettings& ValveSettings::SetStreamMolarMass(MASS mass) {
		_m_mass = mass;
		return *this;
	}
	ValveSettings& ValveSettings::SetStreamTemperature(CTEMP_PTR temp) {
		_c_temp = temp;
		return *this;
	}
	ValveSettings& ValveSettings::SetValveRadius(RADIUS rad) {
		_v_rad = rad;
		return *this;
	}
	ValveSettings& ValveSettings::SetPipeRadius(RADIUS rad) {
		_p_rad = rad;
		return *this;
	}
	ValveSettings& ValveSettings::SetValveStance(PRECENT prec) {
		_scale = prec;
		return *this;
	}

	// -------------------------- реализация методов клапана ------------------------------------

	Valve::Valve(const ValveSettings& settings) 
		: _pres(settings._pres)
		, _m_mass(settings._m_mass)
		, _c_temp(settings._c_temp)
		, _v_rad(settings._v_rad)
		, _p_rad(settings._p_rad) 
		, _scale(settings._scale)
	{
		CheckParamIsCorrect();
		CheckValveStatus();
	}

	CONSUMPTION Valve::GetСonsumption() const {

		if (IsClosed()) return math::constants::_ZERO;

		/*
			Для рассчёта расхода воспользуемся формулой
			Расход (Q) = 
			Эффективость клапана (C), умноженное на 
			Площадь сечения клапана (S), умноженное на 
			Процент открытия клапана (Preccent), умноженное на

			Квадратный корень из
			Два умноженное на Давление газа в трубе (Р),
			Деленное на плотность газа (Ро)
		*/

		EFFECTIVENESS effect = GetValveEffectiveness();
		VSQARE square = GetValveSquare();
		DENSITY density = physics::StreamDensity(*_pres, _m_mass, 
			physics::convert::ConvertTemperature(*_c_temp, physics::CELSIUM_TO_KELVIN));

		return effect * square * _scale * std::sqrt((2 * (*_pres)) / density);
	}
	
	FLAG Valve::IsClosed() const {
		return _is_closed;
	}
	FLAG Valve::IsOpened() const {
		return !IsClosed();
	}

	// -------------------------- сеттеры настройки клапана -------------------------------------

	Valve& Valve::SetValveRadius(RADIUS rad) {
		_v_rad = rad;
		return *this;
	}
	Valve& Valve::SetPipeRadius(RADIUS rad) {
		_p_rad = rad;
		return *this;
	}
	Valve& Valve::SetStreamPreassure(PRESSURE_PTR pres) {
		_pres = pres;
		return *this;
	}
	Valve& Valve::SetStreamMolarMass(MASS mass) {
		_m_mass = mass;
		return *this;
	}
	Valve& Valve::SetStreamTemperature(CTEMP_PTR temp) {
		_c_temp = temp;
		return *this;
	}
	Valve& Valve::SetValveStance(PRECENT scale) {
		_scale = scale;
		CheckValveStatus();
		return *this;
	}

	VOID Valve::CheckValveStatus() {
		using namespace math::constants;
		(_scale - _ZERO <= _EPSILON) ? _is_closed = true : _is_closed = false;
	}
	VOID Valve::CheckParamIsCorrect() {
		assert(_v_rad >= 0 && _p_rad >= 0);
		assert(_v_rad <= _p_rad);
		assert(_scale >= 0 && _scale <= 1);
	}

	KTEMP Valve::TransmuteCelsuimToKelvin(CTEMP c_temp) {
		return physics::convert::ConvertTemperature(c_temp, physics::TEMP_TRANSMUTE_TYPE::CELSIUM_TO_KELVIN);
	}

	CTEMP Valve::TransmuteKelvinToCelsuim(KTEMP k_temp) {
		return physics::convert::ConvertTemperature(k_temp, physics::TEMP_TRANSMUTE_TYPE::KELVIN_TO_CELSIUM);
	}

	VSQARE Valve::GetValveSquare() const {
		return PI * (float)std::pow(_v_rad, 2);
	}

	EFFECTIVENESS Valve::GetValveEffectiveness() const {
		try
		{
			// эффективность клапана рассчитывааем как отношение 
			// площади сечеия клапана к площади сечения труб
			return GetValveSquare() / (PI * (float)std::pow(_p_rad, 2));
		}
		catch (const std::exception& e)
		{
			std::cerr << "Valve::GetValveEffectiveness()::Exception\n";
			std::cerr << e.what() << std::endl;
			throw e;
		}
	}
}