#pragma once

#include <cmath>
#include "EnginePCH.h"

namespace swaws
{
	template <typename T>
	struct Vector3
	{
		T r, g, b;

		Vector3() = default;
		Vector3(T r, T g, T b) : r{ r }, g{ g }, b{ b } {}

		// Operators added by GitHub Copilot

		/// <summary>
		/// Adds two Vector3 objects component-wise.
		/// </summary>
		/// <param name="rhs">The right-hand side Vector3 to add to this Vector3.</param>
		/// <returns>A new Vector3 whose components are the sum of the corresponding components of this Vector3 and rhs.</returns>
		Vector3 operator+(const Vector3& rhs) const {
			return Vector3(r + rhs.r, g + rhs.g, b + rhs.b);
		}

		/// <summary>
		/// Adds the components of another Vector3 to this vector and assigns the result to this vector.
		/// </summary>
		/// <param name="rhs">The Vector3 whose components will be added to this vector.</param>
		/// <returns>A reference to this Vector3 after addition.</returns>
		Vector3& operator+=(const Vector3& rhs) {
			r += rhs.r;
			g += rhs.g;
			b += rhs.b;
			return *this;
		}

		/// <summary>
		/// Subtracts the components of another Vector3 from this Vector3 and returns the result.
		/// </summary>
		/// <param name="rhs">The Vector3 to subtract from this Vector3.</param>
		/// <returns>A new Vector3 representing the component-wise difference between this Vector3 and rhs.</returns>
		Vector3 operator-(const Vector3& rhs) const {
			return Vector3(r - rhs.r, g - rhs.g, b - rhs.b);
		}

		/// <summary>
		/// Subtracts the components of another Vector3 from this Vector3 and assigns the result to this object.
		/// </summary>
		/// <param name="rhs">The Vector3 whose components will be subtracted from this Vector3.</param>
		/// <returns>A reference to this Vector3 after subtraction.</returns>
		Vector3& operator-=(const Vector3& rhs) {
			r -= rhs.r;
			g -= rhs.g;
			b -= rhs.b;
			return *this;
		}

		/// <summary>
		/// Performs component-wise multiplication of two Vector3 objects.
		/// </summary>
		/// <param name="rhs">The right-hand side Vector3 to multiply with this Vector3.</param>
		/// <returns>A new Vector3 where each component is the product of the corresponding components of this Vector3 and rhs.</returns>
		Vector3 operator*(const Vector3& rhs) const {
			return Vector3(r * rhs.r, g * rhs.g, b * rhs.b);
		}

		/// <summary>
		/// Divides each component of this Vector3 by the corresponding component of another Vector3.
		/// </summary>
		/// <param name="rhs">The Vector3 whose components are used as divisors.</param>
		/// <returns>A new Vector3 where each component is the result of dividing the corresponding components of this Vector3 by those of rhs.</returns>
		Vector3 operator/(const Vector3& rhs) const {
			return Vector3(r / rhs.r, g / rhs.g, b / rhs.b);
		}

		/// <summary>
		/// Calculates the Euclidean distance between this Vector3 and another Vector3 instance.
		/// </summary>
		/// <param name="other">The Vector3 instance to which the distance is calculated.</param>
		/// <returns>The Euclidean distance between this Vector3 and the specified Vector3.</returns>
		float length(const Vector3& other) const {
			float dx = static_cast<float>(r - other.r);
			float dy = static_cast<float>(g - other.g);
			float dz = static_cast<float>(b - other.b);
			return std::sqrt(dx * dx + dy * dy + dz * dz);
		}
	};

	template <typename T>
	std::ostream& operator << (std::ostream& ostream, Vector3<T>& v)
	{
		ostream << "{" << v.r << ", " << v.g << ", " << v.b << "}";
		return ostream;
	}

	template <typename T>
	std::istream& operator >> (std::istream& istream, Vector3<T>& v)
	{
		char ch = '\0';

		// { r, g, b }

		if (!(istream >> std::ws >> ch) || ch != '{')
		{
			istream.setstate(std::ios::failbit);
			return istream; // {
		}

		if (!(istream >> std::ws >> v.r))
		{
			istream.setstate(std::ios::failbit);
			return istream; // -1
		}

		if (!(istream >> std::ws >> ch) || ch != ',')
		{
			istream.setstate(std::ios::failbit);
			return istream; // ,
		}

		if (!(istream >> std::ws >> v.g))
		{
			istream.setstate(std::ios::failbit);
			return istream; // -1
		}

		if (!(istream >> std::ws >> ch) || ch != ',')
		{
			istream.setstate(std::ios::failbit);
			return istream; // ,
		}

		if (!(istream >> std::ws >> v.b))
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

	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
}