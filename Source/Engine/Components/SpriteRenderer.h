#pragma once
#include "RendererComponent.h"

namespace swaws
{
	class SpriteRenderer : public RendererComponent
	{
	public:
		static const Texture nullTexture;
		std::string textureName;
	public:
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;
	};
}