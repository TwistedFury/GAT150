#pragma once

#include "Core/Serializable.h"
#include <string>

#define CLASS_PROTOTYPE(classname) virtual std::unique_ptr<Object> Clone() { return std::make_unique<classname>(*this); }

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

		virtual std::unique_ptr<Object> Clone(const Object& other) = 0;

		void Read(const json::value_t& value) override;
	};
}