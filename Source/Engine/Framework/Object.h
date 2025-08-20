#pragma once

#include "Core/Serializable.h"
#include <string>

namespace swaws
{
	class Object : public Serializable
	{
	public:
		std::string name;
		bool isActive{ true };

	public:
		Object() = default;
		virtual ~Object() = default;

		void Read(const json::value_t& value) override;
	};
}