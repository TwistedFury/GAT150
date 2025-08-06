#pragma once
#include <SDL3/SDL.h>
#include <fmod.hpp>

#include "EngineInc.h"

#include "Game/Player.h"
#include "Game/SpaceGame.h"

#include <iostream>
#include <memory>

float rotate = 0;

int main(int argc, char* argv[]) {
    // Set Directory
    swaws::file::SetCurrentDirectory("Assets");

    // Initialize Engine Systems
    swaws::GetEngine().Initialize();

    // Initialize Game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    SDL_Event e;
    bool quit = false;

    // create texture, using shared_ptr so texture can be shared
    //std::shared_ptr<swaws::Texture> texture = std::make_shared<swaws::Texture>();
    //texture->Load("Placeholder.jpg", swaws::GetEngine().GetRenderer());

    auto texture = swaws::Resources().Get<swaws::Texture>("spaceship-sprites/blue_01.png", swaws::GetEngine().GetRenderer());
    
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

        rotate += 90 * swaws::GetEngine().GetTime().GetDeltaTime();

        swaws::GetEngine().GetRenderer().DrawTexture(texture.get(), 30, 30, rotate, 4);

        // Draw Actors
        game->Draw(swaws::GetEngine().GetRenderer());

        swaws::GetEngine().GetRenderer().Present();
    }

    game->Shutdown();
    game.release();
    swaws::GetEngine().Shutdown();

    return 0;
}