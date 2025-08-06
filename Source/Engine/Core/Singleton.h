#pragma once

namespace swaws
{
	template <typename T>
	class Singleton
	{
	public:
		Singleton(const Singleton&) = delete; // Copy Constructor
		Singleton& operator = (const Singleton&) = delete; // Assignment Constructor

		static T& Instance()
		{
			static T instance;
			return instance;
		}
	protected:
		Singleton() = default;
	};
}