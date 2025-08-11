#pragma once
#include "Framework/Component.h"

namespace swaws
{
	class RendererComponent : public Component
	{
	public:
		virtual void Draw(class Renderer& renderer);
	};
}