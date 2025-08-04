#pragma once
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include <vector>

namespace swaws
{
	struct Particle
	{
		bool active{ false };
		vec2 position;
		vec2 velocity;
		vec3 color;

		float lifespan{ 1 };
	};

	class ParticleSystem
	{
	public:
		ParticleSystem() = default;

		bool Initialize(int poolSize = 1000);
		void Shutdown();

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddParticle(const Particle& particle);

	private:
		int poolSize{ 1000 };

		std::vector<Particle> m_particles;

		Particle* GetFreeParticle();
	};
}