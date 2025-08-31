#pragma once

#include "Game/Player.h"
#include "Game/SpaceGame.h"

int main(int argc, char* argv[]) {
    // Set Directory
    swaws::file::SetCurrentDirectory("Assets");
    swaws::Logger::Info("Current Directory {}", swaws::file::GetCurrentDirectory());

    // Initialize Engine Systems
    swaws::GetEngine().Initialize();

    // Initialize Game
    bool quit = false;
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    if (!game->Initialize()) quit = true;

    // Load Background
    swaws::Texture background = *swaws::Resources().Get<swaws::Texture>("new_background.png", swaws::GetEngine().GetRenderer());

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

        // Draw Background
        swaws::vec2 center = {
            (float)swaws::GetEngine().GetRenderer().GetWindowWidth() / 2,
            (float)swaws::GetEngine().GetRenderer().GetWindowHeight() / 2
        };
        swaws::GetEngine().GetRenderer().DrawTexture(background, center.x, center.y, 0, 1);

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