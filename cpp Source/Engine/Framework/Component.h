#pragma once
#include "Object.h"

namespace swaws
{
	class Component : public Object
	{
	public:
		class Actor* owner{ nullptr };

	public:
		Component() = default;
		virtual ~Component() = default;

		// NOTE:
		// Removed CLASS_PROTOTYPE(Component) because Component is abstract (pure virtual Update).
		// The previous macro expanded to a Clone() that tried to do std::make_unique<Component>(*this)
		// which requires instantiating Component (illegal since it's abstract) -> C2259.
		// Leave Clone() unimplemented here; derived concrete components supply their own
		// CLASS_PROTOTYPE(DerivedComponent) to implement Clone().

		virtual void Update(float dt) = 0;

		virtual void Start() {}
		virtual void Destroy() {}
	};
}