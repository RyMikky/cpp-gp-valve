#pragma once

#include <typeinfo>
#include <exception>
#include <stdexcept>
#include <type_traits>
#include <string_view>
#include <unordered_map>

namespace physics {

	namespace constants {

		// универсальная газовая постоянная
		static const double _R = 8.3145;
		static const double _K_TEMP_SCALER = 273.15;
		static const double _ATM_IN_ONE_MPA = 9.8692;
		static const double _MPA_IN_ONE_ATM = 0.10133;

	} // namespace constants

	namespace domines {

		template <typename T>
		struct IsNumeric {
			static const bool _value = std::is_arithmetic<T>::_value;
		};

	} // namespace domines

	// Физические единицы их размерности
	namespace units {

		namespace pressure {

			struct Pa {
				double _value = 0.0;
			};

			struct MPa {
				double _value = 0.0;
			};

			struct Atm {
				double _value = 0.0;
			};

		} // namespace pressure

		namespace temperature {

			struct Cels {
				double _value = 0.0;
			};

			struct Kalv {
				double _value = 0.0;
			};

			struct Fahr {
				double _value = 0.0;
			};

		} // namespace temperature

		namespace molar_mass {

			struct gMol {
				double _value = 0.0;
			};

			struct KgMol {
				double _value = 0.0;
			};

		} // namespace molar_mass

		namespace density {

			struct KgM3 {
				double _value = 0.0;
			};

		} // namespace density

		namespace speed {

			struct MeterSec {
				double _value = 0.0;
			};

		} // namespace speed


		// Возвращает температуру в цельсиях
		static temperature::Cels Convert(const temperature::Kalv& temp) {
			return { temp._value - constants::_K_TEMP_SCALER };
		}

		// Возвращает температуру в кельвинах
		static temperature::Kalv Convert(const temperature::Cels& temp) {
			return { temp._value + constants::_K_TEMP_SCALER };
		}

		// Возвращает давление в паскалях
		static pressure::Pa Convert(const pressure::MPa& press) {
			return { press._value * (double)1e6 };
		}

		// Возвращает давление в мегапаскалях
		static pressure::MPa Convert(const pressure::Pa& press) {
			return { press._value / (double)1e6 };
		}
		
		// Возвращает давление в мегапаскалях
		static pressure::MPa Convert(const pressure::Atm& press) {
			return { press._value / constants::_ATM_IN_ONE_MPA };
		}

		// Возвращает молярную массу в г/моль = кг/кмоль
		static molar_mass::gMol Convert(const molar_mass::KgMol& mass) {
			return { mass._value * (double)1e3 };
		}

		// Возвращает молярную массу в кг/моль
		static molar_mass::KgMol Convert(const molar_mass::gMol& mass) {
			return { mass._value / (double)1e3 };
		}

	} // namespace units

	namespace constants {

		using namespace std::string_view_literals;

		// Таблица молярных масс газов в завимисти от латинских названий в г/моль == кг/кмоль
		static const std::unordered_map<std::string_view, ::physics::units::molar_mass::gMol> _GAS_MOLAR_MASS =
		{
			{"methane"sv, {16.04}}, {"propane"sv, {44.09}}, {"ethylene"sv, {28.05}}, {"ethan"sv, {30.07}}
			// можно продолжать и добавлять другие данные из открытых источников
		};

		// Вовзращает из таблицы молярную массу запрошенного газа в г/моль == кг/кмоль.
		// Внимание! Ввод должен быть осуществлён в виде латинского названия в нижнем регистре
		static const ::physics::units::molar_mass::gMol& GetGasMolarMassGMol (std::string_view line) {
			if (_GAS_MOLAR_MASS.count(line)) return _GAS_MOLAR_MASS.at(line);
			throw std::out_of_range(
				"The data table does not contain the specified entry, \
				make sure that the character input and case are correct");
		}

		// Вовзращает из таблицы молярную массу запрошенного газа в кг/моль.
		// Внимание! Ввод должен быть осуществлён в виде латинского названия в нижнем регистре
		static ::physics::units::molar_mass::KgMol GetGasMolarMassKgMol(std::string_view line) {
			if (_GAS_MOLAR_MASS.count(line)) return ::physics::units::Convert(_GAS_MOLAR_MASS.at(line));
			throw std::out_of_range(
				"The data table does not contain the specified entry, \
				make sure that the character input and case are correct");
		}

		// Показатель адиабаты для конкретного газа по его температуре в град. Цельсия и давлении в 1 атм.
		struct AdiabaticIndex {
			double _t20 = 0.0;
			double _t200 = 0.0;
			double _t400 = 0.0;
			double _t600 = 0.0;
		};

		// Таблица показателей адиабаты различных газов, в зависимости от их температуры, под давлением в 1 атм
		static const std::unordered_map<std::string_view, AdiabaticIndex> _GAS_ADIABATIC_INDEX =
		{
			{"methane"sv, {1.31, 1.23, 1.17, 1.14}}, {"ethylene"sv, {1.24, 1.16, 1.12, 1.10}}, {"ethan"sv, {1.20, 1.12, 1.09, 1.08}}
			// можно продолжать и добавлять другие данные из открытых источников
		};

		// Вовзращает из таблицы показателей адиабаты для запрошенного газа.
		// Внимание! Ввод должен быть осуществлён в виде латинского названия в нижнем регистре
		static const AdiabaticIndex& GetGasAdiabaticIndex(std::string_view line) {
			if (_GAS_ADIABATIC_INDEX.count(line)) return _GAS_ADIABATIC_INDEX.at(line);
			throw std::out_of_range(
				"The data table does not contain the specified entry, \
				make sure that the character input and case are correct");
		}

		// Возвращает показатель адиабаты указанного газа для указанной температуры
		static double GetGasAdiabaticIndex(std::string_view line, ::physics::units::temperature::Cels cTemp) {

			/* 1. Получаем табличную страницу показателей адиабаты для газа */
			static const AdiabaticIndex& table = GetGasAdiabaticIndex(line);

			/* 
				2. Высчитываем показатель для указанной температуры

				Для температур ниже границы в 20 град. Цельсия и выше границы 
				в 600 град. Цельия принимаем равным граничным значениям.

				Для значений входяхих в диапазоны воспользуемся пропорциями
				steps - количество шагов изменения температуры
				range - измененени показателя адиабаты в границах диапазона
				dTemp - разница в тепературах между указанным значением и нижней границей
			*/

			if (cTemp._value <= 20.0) {
				return table._t20;
			}
			else if (cTemp._value <= 200.0) {
				double steps = 200.0 - 20.0;
				double range = table._t20 - table._t200;
				double dTemp = cTemp._value - 20.0;
				return table._t20 - ((range / steps) * dTemp);
			}
			else if (cTemp._value <= 400.0) {
				double steps = 400.0 - 200.0;
				double range = table._t200 - table._t400;
				double dTemp = cTemp._value - 200.0;
				return table._t200 - ((range / steps) * dTemp);
			}
			else if (cTemp._value <= 600.0) {
				double steps = 600.0 - 400.0;
				double range = table._t400 - table._t600;
				double dTemp = cTemp._value - 400.0;
				return table._t400 - ((range / steps) * dTemp);
			}
			else {
				return table._t600;
			}
		}

	} // namespace constants

	

	// Возваращает плотность газа в Килограммах на кубический метр
	static units::density::KgM3 StreamDensity(units::pressure::Pa press, 
		units::molar_mass::KgMol mMass, units::temperature::Kalv kTemp) {
		return { (press._value * mMass._value) / (constants::_R * kTemp._value) };
	}

	// Возваращает плотность газа в Килограммах на кубический метр
	static units::density::KgM3 StreamDensity(units::pressure::Pa press, 
		std::string_view gas, units::temperature::Kalv kTemp) {
		return StreamDensity(press, constants::GetGasMolarMassKgMol(gas), kTemp);
	}

	// Возваращает плотность газа в Килограммах на кубический метр
	static units::density::KgM3 StreamDensity(units::pressure::MPa press, 
		std::string_view gas, units::temperature::Kalv kTemp) {
		return StreamDensity(units::Convert(press), constants::GetGasMolarMassKgMol(gas), kTemp);
	}

	// Возваращает плотность газа в Килограммах на кубический метр
	static units::density::KgM3 StreamDensity(units::pressure::MPa press, 
		std::string_view gas, units::temperature::Cels cTemp) {
		return StreamDensity(units::Convert(press), constants::GetGasMolarMassKgMol(gas), units::Convert(cTemp));
	}

	// Возваращает плотность газа в Килограммах на кубический метр
	static units::density::KgM3 StreamDensity(units::pressure::Pa press, 
		std::string_view gas, units::temperature::Cels cTemp) {
		return StreamDensity(press, constants::GetGasMolarMassKgMol(gas), units::Convert(cTemp));
	}

} // namespace physics