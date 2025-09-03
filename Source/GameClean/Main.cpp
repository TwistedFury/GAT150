#pragma once

#include "Game/Player.h"
#include "Game/SpaceGame.h"
#include "Platformer/PlatformerGame.h"

int main(int argc, char* argv[]) {
    // Set Directory
    swaws::file::SetCurrentDirectory("Assets/Platformer");
    swaws::Logger::Info("Current Directory {}", swaws::file::GetCurrentDirectory());

    // Initialize Engine Systems
    swaws::GetEngine().Initialize();

    // Initialize Game
    bool quit = false;
    std::unique_ptr<swaws::Game> game = std::make_unique<PlatformerGame>();
    if (!game->Initialize()) quit = true;

    SDL_Event e;
    
    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        // LOOP = INPUT, UPDATE, DRAW

        swaws::GetEngine().Update();
        game->Update(swaws::GetEngine().GetTime().GetDeltaTime());

        swaws::GetEngine().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        swaws::GetEngine().GetRenderer().Clear(); // Clear the renderer

        // Draw Actors
        game->Draw(swaws::GetEngine().GetRenderer());

        swaws::GetEngine().GetRenderer().Present();

        // Check quit
        if (swaws::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

    }

    game->Shutdown();
    game.release();
    swaws::GetEngine().Shutdown();

    return 0;
}