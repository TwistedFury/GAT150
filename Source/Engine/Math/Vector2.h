#pragma once

#include <cmath>
#include "Math.h"

namespace swaws {
	template <typename T>
	struct Vector2
	{
		T x, y;

		Vector2() = default;
		Vector2(T x, T y) : x{ x }, y{ y } {}

		// Operators added by GitHub Copilot

		/// <summary>
		/// Returns the result of adding two Vector2 objects component-wise.
		/// </summary>
		/// <param name="rhs">The Vector2 object to add to this Vector2.</param>
		/// <returns>A new Vector2 object whose x and y components are the sums of the corresponding components of this Vector2 and rhs.</returns>
		Vector2 operator+(const Vector2& rhs) const {
			return Vector2(x + rhs.x, y + rhs.y);
		}

		/// <summary>
		/// Adds the components of another Vector2 to this vector and assigns the result to this vector.
		/// </summary>
		/// <param name="rhs">The Vector2 whose components will be added to this vector.</param>
		/// <returns>A reference to this Vector2 after addition.</returns>
		Vector2& operator+=(const Vector2& rhs) {
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		/// <summary>
		/// Adds a value to both components of the vector and assigns the result to this vector.
		/// </summary>
		/// <param name="valueToAdd">The value to add to both the x and y components.</param>
		/// <returns>A reference to this vector after the addition.</returns>
		Vector2& operator+=(T valueToAdd) {
			x += valueToAdd;
			y += valueToAdd;
			return *this;
		}

		/// <summary>
		/// Subtracts the components of another Vector2 from this Vector2.
		/// </summary>
		/// <param name="rhs">The Vector2 to subtract from this Vector2.</param>
		/// <returns>A new Vector2 representing the component-wise difference.</returns>
		Vector2 operator-(const Vector2& rhs) const {
			return Vector2(x - rhs.x, y - rhs.y);
		}

		/// <summary>
		/// Subtracts the components of another Vector2 from this vector and assigns the result to this vector.
		/// </summary>
		/// <param name="rhs">The Vector2 whose components will be subtracted from this vector.</param>
		/// <returns>A reference to this Vector2 after subtraction.</returns>
		Vector2& operator-=(const Vector2& rhs) {
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		/// <summary>
		/// Multiplies two Vector2 objects component-wise.
		/// </summary>
		/// <param name="rhs">The right-hand side Vector2 to multiply with this Vector2.</param>
		/// <returns>A new Vector2 whose x and y components are the products of the corresponding components of the two Vector2 objects.</returns>
		Vector2 operator*(const Vector2& rhs) const {
			return Vector2(x * rhs.x, y * rhs.y);
		}

		/// <summary>
		/// Divides the components of this Vector2 by the corresponding components of another Vector2.
		/// </summary>
		/// <param name="rhs">The Vector2 whose components are used as divisors.</param>
		/// <returns>A new Vector2 containing the result of component-wise division.</returns>
		Vector2 operator/(const Vector2& rhs) const {
			return Vector2(x / rhs.x, y / rhs.y);
		}

		/// <summary>
		/// Calculates the squared length of a vector using its x and y components.
		/// </summary>
		/// <returns>The sum of the squares of the x and y components.</returns>
		float LengthSqr() const { return (x * x) + (y * y); }

		/// <summary>
		/// Calculates the length (magnitude) of the 2D vector.
		/// </summary>
		/// <returns>The length of the vector as a floating-point value.</returns>
		float Length() const {
			return swaws::math::sqrtf(LengthSqr());
		}

		/// <summary>
		/// Multiplies the vector by a scalar value, returning a new scaled vector.
		/// </summary>
		/// <param name="scalar">The scalar value to multiply the vector by.</param>
		/// <returns>A new Vector2 instance with both components multiplied by the scalar.</returns>
		Vector2 operator*(T scalar) const {
			Vector2<float> m_scalar{ scalar, scalar };
			return (*this) * m_scalar;
		}

		/// <summary>
		/// Returns a new Vector2 that is the result of multiplying this vector by a scalar value.
		/// </summary>
		/// <param name="scalar">The scalar value to multiply the vector by.</param>
		/// <returns>A new Vector2 representing the product of this vector and the scalar.</returns>
		Vector2 operator*= (const T scalar) const {
			return (*this) * scalar;
		}

		/// <summary>
		/// Returns a normalized (unit length) version of the vector.
		/// </summary>
		/// <returns>A Vector2 representing the direction of the original vector with a length of 1.</returns>
		Vector2 Normalized() const { return *this * (1 / Length()); }

		/// <summary>
		/// Calculates the angle in radians from the origin to the point (x, y).
		/// </summary>
		/// <returns>The angle in radians, measured from the positive x-axis to the point (x, y).</returns>
		float Angle() const { return math::atan2f(y, x); }

		/// <summary>
		/// Returns a new Vector2 that is the result of rotating this vector by the specified angle in radians.
		/// </summary>
		/// <param name="radians">The angle to rotate the vector, in radians.</param>
		/// <returns>A new Vector2 representing the rotated vector.</returns>
		Vector2 Rotate(float radians) const
		{
			Vector2 v;

			v.x = x * math::cosf(radians) - y * math::sinf(radians);
			v.y = x * math::sinf(radians) + y * math::cosf(radians);

			return v;
		}

		/// <summary>
		/// Calculates the dot product of two 2D vectors.
		/// </summary>
		/// <param name="a">The first 2D vector.</param>
		/// <param name="b">The second 2D vector.</param>
		/// <returns>The dot product of the two vectors as a float.</returns>
		static float Dot(const Vector2& a, const Vector2& b)
		{
			return a.x * b.x + a.y * b.y;
		}

		/// <summary>
		/// Calculates the angle in radians between two 2D vectors.
		/// </summary>
		/// <param name="a">The first 2D vector.</param>
		/// <param name="b">The second 2D vector.</param>
		/// <returns>The angle in radians between the two vectors.</returns>
		static float AngleBetween(const Vector2& a, const Vector2& b)
		{
			return math::acosf(Dot(a, b));
		}

		/// <summary>
		/// Calculates the 2D cross product of two vectors.
		/// </summary>
		/// <param name="a">The first 2D vector.</param>
		/// <param name="b">The second 2D vector.</param>
		/// <returns>The scalar value of the cross product of the two vectors.</returns>
		static float Cross(const Vector2& a, const Vector2& b)
		{
			return a.x * b.y - a.y * b.x;
		}

		/// <summary>
		/// Calculates the signed angle in radians between two 2D vectors.
		/// </summary>
		/// <param name="a">The first 2D vector.</param>
		/// <param name="b">The second 2D vector.</param>
		/// <returns>The signed angle in radians between vector a and vector b. The sign indicates the direction from a to b.</returns>
		static float SignedAngleBetween(const Vector2& a, const Vector2& b)
		{
			float x = Dot(a, b);
			float y = Cross(a, b);

			return math::atan2f(y, x);
		}
	};

	template <typename T>
	std::ostream& operator << (std::ostream& ostream, const Vector2<T>& v)
	{
		ostream << "{" << v.x << ", " << v.y << "}";
		return ostream;
	}

	template <typename T>
	std::istream& operator >> (std::istream& istream, Vector2<T>& v)
	{
		char ch = '\0';

		if (!(istream >> std::ws >> ch) || ch != '{')
		{
			istream.setstate(std::ios::failbit);
			return istream; // {
		}

		if (!(istream >> std::ws >> v.x))
		{
			istream.setstate(std::ios::failbit);
			return istream; // -1
		}

		if (!(istream >> std::ws >> ch) || ch != ',')
		{
			istream.setstate(std::ios::failbit);
			return istream; // ,
		}

		if (!(istream >> std::ws >> v.y))
		{
			istream.setstate(std::ios::failbit);
			return istream; // -1
		}

		if (!(istream >> std::ws >> ch) || ch != '}')
		{
			istream.setstate(std::ios::failbit);
			return istream; // }
		}

		return istream;
	}

	using ivec2 = Vector2<int>;
	using vec2 = Vector2<float>;
}
