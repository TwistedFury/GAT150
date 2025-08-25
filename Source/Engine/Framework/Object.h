#pragma once

#include "Core/Serializable.h"
#include <string>

// Align macro with (now) correct pure virtual signature (no parameters)
#define CLASS_PROTOTYPE(classname) std::unique_ptr<Object> Clone() override { return std::make_unique<classname>(*this); }

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

		// FIX: Signature changed to match usage everywhere (Prototype pattern uses no-arg Clone())
		virtual std::unique_ptr<Object> Clone() = 0;

		void Read(const json::value_t& value) override;
	};
}