#pragma once

namespace math {

	namespace constants {

		static const float _PI = 3.141593f;

#pragma warning( push )
#pragma warning( disable : 4305)
		static const float _EPSILON = 1e-5;
#pragma warning( pop )

		static const float _ZERO = 0;

	} // namespace constants

	namespace convert {

		static float ConvertMillimeterToMeter(float millimeter) {
			return millimeter * (float)1e-3;
		}

	} // namespace convert
		
} // namespace math
