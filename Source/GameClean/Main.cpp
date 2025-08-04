#pragma once
#include <SDL3/SDL.h>
#include <fmod.hpp>

#include "EngineInc.h"

#include "Game/Player.h"
#include "Game/SpaceGame.h"

#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {
    // Set Directory
    swaws::file::SetCurrentDirectory("Assets");

    // Initialize Engine Systems
    swaws::GetEngine().Initialize();

    // Load a Font
    swaws::Font* font = new swaws::Font();
    font->Load("MotionPicture_PersonalUseOnly.ttf", 40);

    // Initialize Game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    SDL_Event e;
    bool quit = false;

    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        swaws::GetEngine().Update();
        game->Update(swaws::GetEngine().GetTime().GetDeltaTime());

        swaws::GetEngine().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        swaws::GetEngine().GetRenderer().Clear(); // Clear the renderer

        // Draw Actors
        game->Draw(swaws::GetEngine().GetRenderer());

        swaws::GetEngine().GetRenderer().Present();
    }

    game->Shutdown();
    game.release();
    swaws::GetEngine().Shutdown();

    return 0;
}