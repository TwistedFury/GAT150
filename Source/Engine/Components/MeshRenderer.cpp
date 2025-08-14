#include "Renderer/Mesh.h"
#include "MeshRenderer.h"

namespace swaws
{
	void swaws::MeshRenderer::Update(float dt)
	{
		//
	}

	void swaws::MeshRenderer::Draw(Renderer& renderer)
	{
		auto mesh = Resources().Get<Mesh>(meshName);

		if (mesh) mesh->Draw(renderer, owner->transform);
	}
}
