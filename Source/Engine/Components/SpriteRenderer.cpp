#include "Engine.h"
#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"

namespace swaws
{
	FACTORY_REGISTER(SpriteRenderer)


	void SpriteRenderer::Start()
	{
		texture = Resources().Get<Texture>(textureName, GetEngine().GetRenderer());
	}

	void SpriteRenderer::Update(float dt)
	{
		//
	}

	void SpriteRenderer::Draw(Renderer& renderer)
	{
		if (texture)
		{
			renderer.DrawTexture
			(
				*texture,
				owner->transform.position.x,
				owner->transform.position.y,
				owner->transform.rotation,
				owner->transform.scale,
				flipH
			);
		}
	}

	void SpriteRenderer::Read(const json::value_t& value)
	{
		Object::Read(value);
		JSON_READ(value, textureName);
		JSON_READ(value, flipH);
	}
}
