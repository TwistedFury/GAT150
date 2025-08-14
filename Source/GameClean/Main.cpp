#pragma once

#include "Game/Player.h"
#include "Game/SpaceGame.h"

float rotate = 0;

int main(int argc, char* argv[]) {
    // Set Directory
    swaws::file::SetCurrentDirectory("Assets");
    swaws::Logger::Info("Current Directory {}", swaws::file::GetCurrentDirectory());

    // load the json data from a file
    std::string buffer;
    swaws::file::ReadTextFile("json.txt", buffer);
    // show the contents of the json file (debug)
    std::cout << buffer << std::endl;

    // create json document from the json file contents
    rapidjson::Document document;
    swaws::json::Load("json.txt", document);

    // read/show the data from the json file
    std::string name;
    int age;
    float speed;
    bool isAwake;
    swaws::vec2 position;
    swaws::vec3 color;

    // read the json data
    swaws::json::Read(document, "name", name);
    swaws::json::Read(document, "age", age);
    swaws::json::Read(document, "speed", speed);
    swaws::json::Read(document, "isAwake", isAwake);
    swaws::json::Read(document, "position", position);
    swaws::json::Read(document, "color", color);

    // show the data
    std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
    std::cout << position.x << " " << position.y << std::endl;
    std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;
    return 0;

    // Initialize Engine Systems
    swaws::GetEngine().Initialize();

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

        rotate += 90 * swaws::GetEngine().GetTime().GetDeltaTime();

        //swaws::GetEngine().GetRenderer().DrawTexture(texture.get(), 30, 30, rotate, 4);

        // Draw Actors
        game->Draw(swaws::GetEngine().GetRenderer());

        swaws::GetEngine().GetRenderer().Present();
    }

    game->Shutdown();
    game.release();
    swaws::GetEngine().Shutdown();

    return 0;
}