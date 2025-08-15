#include "AudioSystem.h"
#include "AudioClip.h"

namespace swaws
{
	AudioClip::~AudioClip()
	{
		if (sound) sound->release();
	}

	bool AudioClip::Load(const std::string& filename,  AudioSystem& audioSystem)
	{
		bool loop = false;
		if (filename == "sndtrack.wav") loop = true;
		FMOD_MODE mode = loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
		FMOD_RESULT result = audioSystem.audio->createSound(filename.c_str(), mode, 0, &sound);
		if (!AudioSystem::CheckFMODResult(result)) return false;
		return true;
	}
}
