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
		void playSound(const std::string& refName, FMOD::ChannelGroup* channelGroup, bool paused, FMOD::Channel** channel) 
		{
			auto soundIt = sounds.find(refName);
			if (soundIt == sounds.end() || !soundIt->second) {
				// Handle error: sound not found or not loaded
				return;
			}

			FMOD::Channel* myChannel = nullptr;
			FMOD_RESULT result = audio->playSound(soundIt->second, channelGroup, paused, &myChannel);
			if (result != FMOD_OK) {
				// Handle FMOD error
				return;
			}

			if (channel) {
				*channel = myChannel;
			}
			channels[refName] = myChannel;
		}
		void AddSound(const char* name_or_data, std::string refName, FMOD_MODE mode = FMOD_LOOP_OFF);

		void Update();
		void Shutdown();

	private:
		FMOD::System* audio = nullptr;
		std::map<std::string, FMOD::Sound*> sounds;
		std::map<std::string, FMOD::Channel*> channels;
	};
}