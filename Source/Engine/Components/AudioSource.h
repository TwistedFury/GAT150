#pragma once
#include "Framework/Component.h"

namespace swaws
{
	class AudioSource : public Component
	{
	public:
		std::string audioClipName;

	public:
		CLASS_PROTOTYPE(AudioSource)

		void Update(float dt) override;
		void Play();
	};
}