#include "valve.h"
#include <cmath>
#include <iostream>
#include <cassert>
#include <exception>

namespace fittings {

	using namespace math;
	using namespace math::units;
	using namespace physics;
	using namespace physics::units;

	// -------------------------- реализация методов клапана ------------------------------------

	Valve::Valve(settings::Settings& settings) 
		: _settings(settings)
	{}

	double Valve::GetMassConsumption() {
		/*
			Формула рассчёта массового расхода

			Qm = E * C * Kш * Kп * ε * (π * d^2 / 4) * (2 * ρ * ∆P)^0.5 
			где, E - коэффициент скорости входа
				C - коэффициент истечения потока
				Kш - коэффициент погрешности на шероховатость стенок трубы, принимаем за 1.0, так как не учитываем
				Kп - поправка на притупление входной кромки, также не учитываем, принимаем за 1.0
				ε - коэффициент расширения вещества
				π - математическая константа Пи
				d - диаметр отверстия диафрагмы
				ρ - плотность газа для указанной температуры
				∆P - падение давления на переходе
		*/

		double PiD = math::constants::_PI * std::pow(_settings._aperture_diameter._value._value, 2.0) / 4.0;
		double RoP = std::pow(GetPressureDropAtTheAperture()._value * 2 * 
			physics::StreamDensity(_settings._gas_input_pressure, _settings._gas_type_str, _settings._gas_celsium_temp)._value, 0.5);

		return GetEntryCoefficient() * GetFlowCoefficient() * GetExpansionCoefficient() * PiD * RoP;
	}

	double Valve::GetVolumeConsumption() {
		/*
			Формула рассчёта объемного расхода

			Qo = Qm / ρ;
			где, Qo - массовый расход газа
				ρ - плотность газа для указанной температуры
		*/

		return GetMassConsumption() / physics::StreamDensity(_settings._gas_input_pressure, _settings._gas_type_str, _settings._gas_celsium_temp)._value;
	}

	pressure::MPa Valve::GetPressureDropAtTheAperture() {
		return { _settings._gas_input_pressure._value - _settings._gas_output_pressure._value };
	}

	Diameter Valve::GetRealTimeDiameter(Diameter diam) {
		/*
			Формулы пересчёта диаметров
			Dr = D [1 + γ(t − 20)];
			где D - diam, t - температура среды в цельсиях,

			γ = 10e-6[ae + (10e-3 * t * be) - (10e-6 * t^2 * ce)];
			где ae, be, ce - коэфициенты для определенной марки стали, t - температура среды в цельсиях
		*/

		matherials::SteelCoef coef = matherials::GetSteelCoef(_settings._pipe_steel_mark);

		double be_group = (double)10e-3 * _settings._gas_celsium_temp._value * coef._be;
		double ce_group = (double)10e-6 * std::pow(_settings._gas_celsium_temp._value, 2) * coef._ce;
		double y = (double)10e-6 * (coef._ae + be_group - ce_group);

		return Diameter({ diam._value._value * (1.0 + (y * (_settings._gas_celsium_temp._value - 20.0)))});
	}

	Diameter Valve::GetPipeRealInnerDiameter() {
		return GetRealTimeDiameter(_settings._pipe_inner_diameter);
	}

	Diameter Valve::GetApertureRealDiameter() {
		return GetRealTimeDiameter(_settings._aperture_diameter);
	}

	double Valve::GetDiametersRatio() const {
		return _settings._aperture_diameter._value._value / _settings._pipe_inner_diameter._value._value;
	}

	double Valve::GetEntryCoefficient() {
		/*
			Высчитываается по формуле 1 / (1 - отношение диаметров в степени 4) в степени 0,5
		*/

		double value = 1.0f - std::pow(GetDiametersRatio(), 4.0);
		return 1.0 / std::pow(value, 0.5);
	}

	double Valve::GetFlowCoefficient() {
		/*
			Для вычисления коэффициента воспользуемся следующей формулой

			С = 0,5959 + 0,0312(β^2,1) - 0,1840(β^8) + (0,090L1(β^4) * (1 - (β^4))^-1) - 0,0337L2(β^3);

			где, β - соотношение диаметров диафрагмы к диаметру трубы
				L1 - (при фланцевом отборе) принимаем как 25,4/D
				L2 - (при фланцевом отборе) принимаем как 25,4/D

				где, D - диаметр трубы
		*/

		double beta = GetDiametersRatio();
		double L1 = 25.4 / _settings._pipe_inner_diameter._value._value;

		/*
			формулу разделим на 6 элементов, fc0 = 0.5959f;
		*/

		double fc1 = 0.0312 * (std::pow(beta, 2.1));
		double fc2 = 0.1840 * (std::pow(beta, 8.0));
		double fc3 = 0.0900 * L1 * (std::pow(beta, 4.0));
		double fc4 = std::pow((1 - std::pow(beta, 4.0)), -1.0);
		double fc5 = 0.0337 * L1 * (std::pow(beta, 3.0));

		return 0.5959 + fc1 - fc2 + (fc3 * fc4) - fc5;
	}

	double Valve::GetExpansionCoefficient() {
		/*
			Для вычисления коэффициента воспольуземся формулой

			ε = 1 - ((0,41 + 0,35(β^4)) * ∆P / k * p)
			где, β - соотношение диаметров диафрагмы к диаметру трубы
				∆P - замеренный перепад давления на диафрагме
				р – абсолютное давление перед диафрагмой
				k – коэффициент адиабаты измеряемой газовой среды
		*/

		double numerator = (0,41 + (0,35 * std::pow(GetDiametersRatio(), 4))) * GetPressureDropAtTheAperture()._value;
		double denominator = _settings._gas_input_pressure._value
			* physics::constants::GetGasAdiabaticIndex(_settings._gas_type_str, _settings._gas_celsium_temp);
		return 1.0 - (numerator / denominator);
	}

}