#include "Renderer/Mesh.h"
#include "MeshRenderer.h"

namespace swaws
{
	FACTORY_REGISTER(MeshRenderer)

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
