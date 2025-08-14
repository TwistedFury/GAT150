#include "EnginePCH.h"
#include "Engine.h"
#include "Audio/AudioClip.h"
#include "AudioSource.h"

namespace swaws
{
	void swaws::AudioSource::Update(float dt)
	{
		//
	}

	void AudioSource::Play()
	{
		auto audioClip = Resources().Get<AudioClip>(audioClipName, GetEngine().GetAudio());
		if (audioClip) GetEngine().GetAudio().PlaySound(*audioClip);
	}
}
