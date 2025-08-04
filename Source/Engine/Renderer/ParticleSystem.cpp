#pragma once
#include "ParticleSystem.h"
#include "Renderer.h"

namespace swaws
{
	bool ParticleSystem::Initialize(int poolSize)
	{
		// Reserve Particle Space
		m_particles.resize(poolSize);

		return true;
	}

	void ParticleSystem::Shutdown()
	{

	}

	void ParticleSystem::Update(float dt)
	{
		for (auto& particle : m_particles)
		{
			if (particle.active)
			{
				particle.lifespan -= dt;
				particle.active = particle.lifespan > 0;
				particle.position += particle.velocity * dt;

			}
		}
	}

	void ParticleSystem::Draw(Renderer& renderer)
	{
		for (auto& particle : m_particles)
		{
			if (particle.active)
			{
				renderer.SetColor(particle.color.r, particle.color.g, particle.color.b);
				renderer.DrawPoint(particle.position.x, particle.position.y);
			}
		}
	}

	void ParticleSystem::AddParticle(const Particle& particle)
	{
		Particle* pParticle = GetFreeParticle();
		if (pParticle)
		{
			*pParticle = particle;
			pParticle->active = true;
		}
	}

	Particle* ParticleSystem::GetFreeParticle()
	{
		for (auto& particle : m_particles)
		{
			if (!particle.active) return &particle;
		}
		return nullptr;
	}
}