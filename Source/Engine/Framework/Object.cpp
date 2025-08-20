#include "EnginePCH.h"

namespace swaws
{
	void Object::Read(const json::value_t& value)
	{
		JSON_READ(value, name);
		JSON_READ(value, isActive);
	}
}
