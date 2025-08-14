#pragma once

namespace swaws
{
	class AudioClip : public Resource
	{
	public:
		AudioClip() = default;
		~AudioClip();

		bool Load(const std::string& filename, class AudioSystem& audioSystem);

	private:
		friend class AudioSystem;
		FMOD::Sound* sound{ nullptr };
	};
}