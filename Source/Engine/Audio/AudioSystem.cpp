#pragma once
#include "AudioSystem.h"
#include "AudioClip.h"
#include "fmod_errors.h"

namespace swaws
{
    /// <summary>
    /// Loads a set of predefined sound files into the audio system.
    /// </summary>
    void AudioSystem::LoadSounds()
    {
        void* extradriverdata = nullptr;
        audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

        Resources().Get<AudioClip>("blaster.wav", "blaster", this);
        Resources().Get<AudioClip>("laser.mp3", "laser", this);
        Resources().Get<AudioClip>("gameOver_pacman.wav", "gameOver", this);
        Resources().Get<AudioClip>("explosion.wav", "explosion", this);
        /*
        * 80s Space Mission Music by Tomentum+ -- https://freesound.org/s/723496/ -- License: Attribution 4.0

        greetings.wav by oae888 -- https://freesound.org/s/541590/ -- License: Creative Commons 0

        ISS2.mp3 by oae888 -- https://freesound.org/s/541584/ -- License: Creative Commons 0
        */
        Resources().Get<AudioClip>("sndtrack.wav", "soundtrack", this);
    }

    bool AudioSystem::PlaySound(AudioClip& clip)
    {
        FMOD_RESULT result = audio->playSound(clip.sound, 0, false, nullptr);
        if (!CheckFMODResult(result)) return false;
        return true;
    }

    /// <summary>
    /// Updates the state of the audio system.
    /// </summary>
    void AudioSystem::Update()
    {
        //
    }

    /// <summary>
    /// Shuts down the audio system and releases associated resources.
    /// </summary>
    void AudioSystem::Shutdown()
    {
        //
    }

    bool AudioSystem::CheckFMODResult(FMOD_RESULT result)
    {
        if (result != FMOD_OK)
        {
            Logger::Error("FMOD Error: {}", FMOD_ErrorString(result));
            return false;
        }
        return true;
    }
}
