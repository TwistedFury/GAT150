#pragma once

#include <box2d/box2d.h>
#include <memory>

namespace swaws
{
	inline b2Vec2 to_b2(const vec2& v) { return b2Vec2{ v.x, v.y }; }
	inline vec2 to_vec2(const b2Vec2& v) { return vec2{ v.x, v.y }; }

	class Physics
	{
	public:
		static float ms_ppu; // Pixels Per Unit

	public:
		Physics() = default;

		bool Initialize();
		void Shutdown();

		void Update(float dt);

		static vec2 WorldToPixel(const vec2& world) { return world * ms_ppu; }
		static vec2 PixelToWorld(const vec2& pixel) { return pixel * (1/ms_ppu); }

		static void SetPPU(float ppu) { ms_ppu = ppu; }

		void ProcessCollisionEvents();
	private:
		friend class PhysicsBody;
		b2WorldId m_worldId;
	};
}