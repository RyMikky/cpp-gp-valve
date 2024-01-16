#pragma once

namespace math {

	namespace units {

		namespace scale {

			struct Meter {
				double _value = 0.0;
			};

			struct mMeter {
				double _value = 0.0;
			};

		} // namespace scale

		struct Radius {
			Radius() = default;
			explicit Radius(scale::mMeter value)
				: _value{ value } {};

			scale::mMeter _value = {};
		};

		struct Diameter {
			Diameter() = default;
			explicit Diameter(scale::mMeter value)
				: _value{ value } {};
			scale::mMeter _value = {};
		};

		// Возвращает меру длинны в миллиметрах
		static scale::mMeter Convert(scale::Meter scale) {
			return { scale._value * (double)1e6 };
		}

		// Возвращает меру длинны в метрах
		static scale::Meter Convert(scale::mMeter scale) {
			return { scale._value / (double)1e6 };
		}

		// Возвращает радиус от диаметра
		static Radius Convert(Diameter diameter) {
			return Radius({ diameter._value._value / 2 });
		}

		// Возвращает диаметр от радиуса
		static Diameter Convert(Radius radius) {
			return Diameter({ radius._value._value / 2 });
		}

	} // namespace units

	namespace constants {

		static const double _PI = 3.141593;

#pragma warning( push )
#pragma warning( disable : 4305)
		static const double _EPSILON = 1e-5;
#pragma warning( pop )

		static const double _ZERO = 0.0;

	} // namespace constants

	namespace convert {

		static double ConvertMillimeterToMeter(double millimeter) {
			return millimeter * (double)1e-3;
		}

	} // namespace convert
		
} // namespace math
