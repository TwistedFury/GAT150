#pragma once
#include "Framework/Component.h"

namespace swaws
{
	class AudioSource : public Component
	{
	public:
		std::string audioClipName;

	public:
		void Update(float dt) override;

		void Play();



	};
}