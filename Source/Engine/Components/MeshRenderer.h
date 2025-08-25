#pragma once
#include "RendererComponent.h"

namespace swaws
{
	class MeshRenderer : public RendererComponent
	{
		// Variables
	public:
		std::string meshName;
		res_t<Mesh> mesh;
		// Methods
	public:
		CLASS_PROTOTYPE(MeshRenderer)

		void Update(float dt) override;
		void Draw(Renderer& renderer) override;
		void Start() override;
	};
}