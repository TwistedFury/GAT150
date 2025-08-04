#pragma once

#include "Engine.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Renderer/ParticleSystem.h"

namespace swaws
{
	/// <summary>
	/// Initializes the core subsystems of the Engine, including rendering, audio, input, and timing.
	/// </summary>
	/// <returns>Returns true if all subsystems are successfully initialized.</returns>
	bool Engine::Initialize()
	{
		renderer = std::make_unique<Renderer>();
		renderer->Initialize();
		renderer->CreateWindow("SWAWS Engine", 1280, 1024);

		audio = std::make_unique<AudioSystem>();
		audio->InitializeAudio();
		audio->LoadSounds();

		input = std::make_unique<InputSystem>();
		input->Initialize();

		time = std::make_unique<Time>();

		particle = std::make_unique<ParticleSystem>();
		particle->Initialize(5000);

		return true;
	}

	/// <summary>
	/// Updates the engine's subsystems for the current frame.
	/// </summary>
	void Engine::Update()
	{
		time->Tick();
		audio->Update();
		input->Update();
		particle->Update(time->GetDeltaTime());
	}

	/// <summary>
	/// Shuts down the engine and its subsystems in reverse initialization order.
	/// </summary>
	void Engine::Shutdown()
	{
		// Typically reverse order of Initialize
		particle->Shutdown();
		input->Shutdown();
		audio->Shutdown();
		renderer->ShutDown();
	}

	/// <summary>
	/// Renders the current frame or scene using the engine.
	/// </summary>
	void Engine::Draw()
	{
		//
	}

	/// <summary>
	/// Returns a reference to a static Engine instance.
	/// </summary>
	/// <returns>A reference to the static Engine object.</returns>
	Engine& GetEngine()
	{
		static Engine engine;
		return engine;
	}
}
