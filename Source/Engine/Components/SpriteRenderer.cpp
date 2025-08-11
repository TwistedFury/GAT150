#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
namespace swaws
{
	void SpriteRenderer::Update(float dt)
	{
		//
	}

	void SpriteRenderer::Draw(Renderer& renderer)
	{
		renderer.DrawTexture
		(
			Resources().Get<Texture>(name, renderer).get(), 
			owner->transform.position.x, 
			owner->transform.position.y, 
			owner->transform.rotation, 
			owner->transform.scale
		);
	}
}
