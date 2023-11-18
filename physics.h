#pragma once
#include <typeinfo>
#include <exception>
#include <type_traits>

namespace physics {

	namespace domines {

		template <typename T>
		struct IsNumeric {
			static const bool value = std::is_arithmetic<T>::value;
		};
	}

	namespace constants {

		// универсальная газовая постоянная
		static const float _R = 8.314f;
		static const float _F_TEMP_SCALER = 32.0f;
		static const float _K_TEMP_SCALER = 273.15f;
		static const float _METHAN_MOLAR_MASS = 0.01604f;

	} // namespace constants

	
	// Возваращает плотность газа
	static float StreamDensity(float press, float mMass, float kTemp) {
		return (press * mMass) / (constants::_R * kTemp);
	}

	enum TEMP_TRANSMUTE_TYPE
	{
		CELSIUM_TO_KELVIN, CELSIUM_TO_FAHRENHEIT,
		KELVIN_TO_CELSIUM, KELVIN_TO_FAHRENHEIT,
		FAHRENHEIT_TO_CELSIUM, FAHRENHEIT_TO_KELVIN
	};

	namespace convert {

		static float ConvertMPAtoPA(float mpa) {
			return mpa * (float)1e6;
		}

		// Выполняет преобразование температуры
		template <typename T>
		float ConvertTemperature(T temp, TEMP_TRANSMUTE_TYPE op) {

			using namespace constants;

			if (!domines::IsNumeric<T>::value) throw std::bad_cast();

			switch (op)
			{
			case physics::CELSIUM_TO_KELVIN:
				return static_cast<float>(temp) + _K_TEMP_SCALER;

			case physics::CELSIUM_TO_FAHRENHEIT:
				return static_cast<float>(temp) + _F_TEMP_SCALER;

			case physics::KELVIN_TO_CELSIUM:
				return static_cast<float>(temp) - _K_TEMP_SCALER;

			case physics::KELVIN_TO_FAHRENHEIT:
				return static_cast<float>(temp) - _K_TEMP_SCALER + _F_TEMP_SCALER;

			case physics::FAHRENHEIT_TO_CELSIUM:
				return static_cast<float>(temp) - _F_TEMP_SCALER;

			case physics::FAHRENHEIT_TO_KELVIN:
				return static_cast<float>(temp) - _F_TEMP_SCALER + _K_TEMP_SCALER;

			default:
				throw std::exception("unknow_operation_to_temp_transmutation");
			}
		}

	} // namespace convert

} // namespace physics