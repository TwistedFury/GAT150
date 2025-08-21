#pragma once
#include "RendererComponent.h"

namespace swaws
{
	class SpriteRenderer : public RendererComponent
	{
	public:
		std::string textureName;
	public:
		CLASS_PROTOTYPE(SpriteRenderer)

		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;
		void Read(const json::value_t& value) override;
	};
}