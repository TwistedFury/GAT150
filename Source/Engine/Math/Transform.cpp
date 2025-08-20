#include "EnginePCH.h"

namespace swaws
{
	void Transform::Read(const json::value_t& value)
	{
		JSON_READ(value, position);
		JSON_READ(value, rotation);
		JSON_READ(value, scale);
	}
}
