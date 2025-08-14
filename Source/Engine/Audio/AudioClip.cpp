#include "AudioSystem.h"
#include "AudioClip.h"

namespace swaws
{
	AudioClip::~AudioClip()
	{
		if (sound) sound->release();
	}

	bool AudioClip::Load(const std::string& filename, const std::string& refName, AudioSystem& audioSystem)
	{
		FMOD_RESULT result = audioSystem.audio->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
		if (!AudioSystem::CheckFMODResult(result)) return false;
		this->refName = refName;
		return true;
	}
}
