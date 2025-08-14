#pragma once
#include "fmod.hpp"
#include <map>
#include <string>

namespace swaws
{
	class AudioSystem
	{
	public:
		AudioSystem() = default;

		FMOD::System* GetAudio() { return audio; }

		void InitializeAudio() { FMOD::System_Create(&audio); }

		void LoadSounds();
		bool PlaySound(class AudioClip& clip);

		void Update();
		void Shutdown();

	private:
		friend class AudioClip;
		FMOD::System* audio = nullptr;
		std::map<std::string, FMOD::Channel*> channels;

		static bool CheckFMODResult(FMOD_RESULT result);
	};
}