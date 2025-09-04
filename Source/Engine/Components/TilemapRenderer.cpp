#include "TilemapRenderer.h"
#include "Renderer/Tilemap.h"
#include "Engine.h"

namespace swaws 
{
	FACTORY_REGISTER(TilemapRenderer);

	TilemapRenderer::TilemapRenderer(const TilemapRenderer& other) 
	{
	}

	static constexpr uint32_t FLIP_MASK  = 0xE0000000; // bits 31,30,29
	static constexpr uint32_t GID_MASK   = 0x1FFFFFFF; // lower 29 bits

	void TilemapRenderer::Start() 
	{
		tilemap = Resources().Get<Tilemap>(tilemapName, GetEngine().GetRenderer());
		if (!tilemap) 
		{
			Logger::Error("Could not load tilemap: {}", tilemapName);
			return;
		}

		Transform transform;
		transform.scale = owner->transform.scale;
		transform.rotation = owner->transform.rotation;

		PhysicsBody::PhysicsBodyDef bodyDef;
		bodyDef.isDynamic = false;
		bodyDef.actor = owner;

		for (auto& layer : tilemap->GetLayers()) 
		{
			if (!layer.hasCollision) continue;

			for (int i = 0; i < static_cast<int>(layer.data.size()); i++) 
			{
				uint32_t raw = layer.data[i];
				uint32_t tileId = raw & GID_MASK;
				if (tileId == 0) continue;

				rect source = tilemap->GetTextureRect(layer, static_cast<int>(tileId));
				vec2 position = owner->transform.position + (tilemap->GetPosition(layer, i) * owner->transform.scale);

				transform.position = position;
				vec2 size = vec2{ source.w, source.h };

				auto physicsBody = std::make_unique<PhysicsBody>(transform, size, bodyDef, GetEngine().GetPhysics());
				physicsBodies.push_back(std::move(physicsBody));
			}
		}
	}

	void TilemapRenderer::Update(float dt) 
	{
		//
	}

	void TilemapRenderer::Draw(Renderer& renderer) 
	{
		for (auto& layer : tilemap->GetLayers()) 
		{
			for (int i = 0; i < static_cast<int>(layer.data.size()); i++) 
			{
				uint32_t raw = layer.data[i];
				uint32_t tileId = raw & GID_MASK;
				if (tileId == 0) continue;

				rect source = tilemap->GetTextureRect(layer, static_cast<int>(tileId));
				vec2 position = owner->transform.position + (tilemap->GetPosition(layer, i) * owner->transform.scale);

				// (Future) handle flipping via raw & FLIP_MASK
				renderer.DrawTexture(*layer.texture, source, position.x, position.y, owner->transform.rotation, owner->transform.scale);
			}
		}
	}

	void TilemapRenderer::Read(const json::value_t& value) 
	{
		Object::Read(value);
		JSON_READ(value, tilemapName);
	}
}