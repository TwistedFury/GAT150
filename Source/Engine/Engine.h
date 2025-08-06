#pragma once
#include <memory>
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Renderer/ParticleSystem.h"
#include "Core/Singleton.h"

namespace swaws
{
	class Engine : public Singleton<Engine>
	{
	public:

		bool Initialize();
		void Update();

		void Shutdown();
		void Draw();

		Renderer& GetRenderer() { return *renderer; }
		ParticleSystem& GetPS() { return *particle; }
		AudioSystem& GetAudio() { return *audio; }
		InputSystem& GetInput() { return *input; }

		Time& GetTime() { return *time; }

	private:
		std::unique_ptr<Time> time;
		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<AudioSystem> audio;
		std::unique_ptr<InputSystem> input;
		std::unique_ptr<ParticleSystem> particle;

	private:
		friend class Singleton<Engine>;
		Engine() = default;
	};

	inline Engine& GetEngine() { return Engine::Instance(); }
}