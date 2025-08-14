#pragma once
#include "Resources/Resource.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include <vector>

namespace swaws
{
	class Mesh : public Resource
	{
	public:
		Mesh() = default;

		Mesh(const std::vector<vec2>& verts, const vec3& color) : m_verts{ verts }, color{ color } 
		{
			CalculateRadius();
		}

		bool Load(const std::string filename);

		void Draw(class Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(class Renderer& renderer, Transform& transform);

		float GetRadius() const { return m_radius; }

		vec3 GetColor() const { return color; }
		void SetColor(vec3 color) { this->color = color; }

	private:
		void CalculateRadius();

	private:
		float m_radius{ 0 };
		std::vector<vec2> m_verts;
		vec3 color{ 1, 1, 1 };
	};
}
