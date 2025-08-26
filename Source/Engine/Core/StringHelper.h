#pragma once
#include <string>
#include <cctype>

namespace swaws
{
	/// <summary>
	/// Converts all characters in a string to lowercase.
	/// </summary>
	/// <param name="str">The input string to be converted.</param>
	/// <returns>A new string with all characters converted to lowercase.</returns>
	inline std::string tolower(const std::string& str)
	{
		std::string result = str;

		// Convert to Lowercase
		for (char& c : result)
		{
			c = std::tolower(c);
		}

		return result;
	}

	/// <summary>
	/// Converts all characters in a string to uppercase.
	/// </summary>
	/// <param name="str">The input string to convert.</param>
	/// <returns>A new string with all characters converted to uppercase.</returns>
	inline std::string toupper(const std::string& str)
	{
		std::string result = str;

		// Convert to Uppercase
		for (char& c : result)
		{
			c = std::toupper(c);
		}

		return result;
	}

	inline bool compareIgnore(const std::string& a, const std::string& b)
	{
		if (a.length() != b.length()) return false;

		return std::equal(a.begin(), a.end(), b.begin(), [](char a, char b) {
			return (std::tolower(a) == std::tolower(b));
			});
	}
}