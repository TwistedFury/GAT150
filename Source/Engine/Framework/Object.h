#pragma once

namespace swaws
{
	class Object
	{
	public:
		std::string name;
		bool isActive{ true };

	public:
		Object() = default;
		virtual ~Object() = default;
	};
}