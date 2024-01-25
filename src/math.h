#pragma once

namespace math {

	namespace units {

		struct Radius {
			Radius() = default;
			explicit Radius(double value)
				: _value{ value } {};

			double _value = NAN;

			inline double operator()() const {
				return _value;
			}

			inline bool is_nan() const {
				return std::isnan(_value);
			}
		};

		struct Diameter {
			Diameter() = default;
			explicit Diameter(double value)
				: _value{ value } {};

			double _value = NAN;

			inline double operator()() const {
				return _value;
			}

			inline bool is_nan() const {
				return std::isnan(_value);
			}
		};

		// Возвращает радиус от диаметра
		static Radius Convert(Diameter diameter) {
			return !diameter.is_nan() ? Radius(diameter() / 2) : Radius();
		}

		// Возвращает диаметр от радиуса
		static Diameter Convert(Radius radius) {
			return !radius.is_nan() ? Diameter(radius() * 2) : Diameter();
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
