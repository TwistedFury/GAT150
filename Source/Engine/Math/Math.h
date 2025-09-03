#pragma once
#include <algorithm>

namespace swaws {
	namespace math {
		inline constexpr float pi = 3.14159265f;
		inline constexpr float twoPi = 2 * pi;
		inline constexpr float halfPi = pi / 2;

		/// <summary>
		/// Converts radians to degrees.
		/// </summary>
		/// <param name="rad">The angle in radians</param>
		/// <returns>The angle in degrees</returns>
		constexpr float RadToDeg(float rad) { return rad * (180 / pi); }

		/// <summary>
		/// Converts degrees to radians.
		/// </summary>
		/// <param name="deg">The angle in degrees</param>
		/// <returns>The angle in radians</returns>
		constexpr float DegToRad(float deg) { return deg * (pi / 180); }

		/// <summary>
		/// Wraps an integer value into the range [min, max), cycling around if necessary.
		/// </summary>
		/// <param name="value">The integer value to wrap.</param>
		/// <param name="min">The inclusive lower bound of the range.</param>
		/// <param name="max">The exclusive upper bound of the range.</param>
		/// <returns>The wrapped integer value within the range [min, max).</returns>
		constexpr int wrap(int value, int min, int max)
		{
			int range = max - min;
			int result = (value - min) % range;
			if (result < 0) result += range;

			return min + result;
		}

		/// <summary>
		/// Wraps a floating-point value into the range [min, max).
		/// </summary>
		/// <param name="value">The value to wrap within the specified range.</param>
		/// <param name="min">The inclusive lower bound of the range.</param>
		/// <param name="max">The exclusive upper bound of the range.</param>
		/// <returns>The wrapped value, guaranteed to be within the range [min, max).</returns>
		inline float wrap(float value, float min, float max)
		{
			float range = max - min;
			float result = std::fmodf(value - min, range);
			if (result < 0) result += range;
			
			return min + result;
		}

		/// <summary>
		/// Determines the sign of a number.
		/// </summary>
		/// <typeparam name="T">The type of the number.</typeparam>
		/// <param name="v">The number whose sign is to be determined.</param>
		/// <returns>Returns -1 if the number is negative, 1 if positive, and 0 if zero.</returns>
		template <typename T>
		inline T sign(T v)
		{
			return (v < 0) ? (T)-1 : (v > 0) ? (T)1 : (T)0;
		}

		using std::min;
		using std::max;
		using std::sqrt;
		using std::sqrtf;
		using std::sin;
		using std::sinf;
		using std::asinf;
		using std::cos;
		using std::cosf;
		using std::acosf;
		using std::atan;
		using std::atanf;
		using std::atan2f;
		using std::abs;
		using std::fabs;
	}
}