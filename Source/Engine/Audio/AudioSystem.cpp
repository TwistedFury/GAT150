#pragma once
#include "AudioSystem.h"

namespace swaws
{
    /// <summary>
    /// Loads a set of predefined sound files into the audio system.
    /// </summary>
    void AudioSystem::LoadSounds()
    {
        void* extradriverdata = nullptr;
        audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

        AddSound("blaster.wav", "blaster");
        AddSound("laser.mp3", "laser");
        AddSound("gameOver_pacman.wav", "gameOver");
        AddSound("explosion.wav", "explosion");
        /*
        * 80s Space Mission Music by Tomentum+ -- https://freesound.org/s/723496/ -- License: Attribution 4.0

        greetings.wav by oae888 -- https://freesound.org/s/541590/ -- License: Creative Commons 0

        ISS2.mp3 by oae888 -- https://freesound.org/s/541584/ -- License: Creative Commons 0
        */
        AddSound("sndtrack.wav", "soundtrack", FMOD_LOOP_NORMAL);
    }

    void AudioSystem::AddSound(const char* name_or_data, std::string refName, FMOD_MODE mode)
    {
        FMOD::Sound* sound = nullptr;
        audio->createSound(name_or_data, mode, 0, &sound);
        sounds[refName] = sound;
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
}
