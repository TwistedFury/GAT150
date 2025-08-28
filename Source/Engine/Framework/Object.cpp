#include "EnginePCH.h"

namespace swaws
{
	void Object::Read(const json::value_t& value)
	{
		JSON_READ(value, name);
		if (JSON_HAS(value, isActive)) JSON_READ(value, isActive);
	}
}
