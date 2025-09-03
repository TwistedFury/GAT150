#pragma once
#include "../GamePCH.h"
#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"

#include "Renderer/Renderer.h"

bool SpaceGame::Initialize()
{
    OBSERVER_ADD(player_dead);
    OBSERVER_ADD(add_points);

    swaws::Factory::Instance().RemoveAll();

    scene = std::make_unique<swaws::Scene>(this);
    if (!scene->Load("scene.json")) {
        swaws::Logger::Error("Scene boot failed: {}", "scene.json");
        return false;
    }

    //m_titleFont = std::make_shared<swaws::Font>();
    //m_titleFont->Load("8bitOperatorPlus8-Regular.ttf", 64);

    //m_uiFont = std::make_shared<swaws::Font>();
    //m_uiFont->Load("8bitOperatorPlus8-Regular.ttf", 48);

    m_titleText = std::make_unique<swaws::Text>(swaws::Resources().GetWithID<swaws::Font>("titleF", "8bitOperatorPlus8-Regular.ttf", 64));
    m_scoreText = std::make_unique<swaws::Text>(swaws::Resources().GetWithID<swaws::Font>("uiF", "8bitOperatorPlus8-Regular.ttf", 48));
    m_livesText = std::make_unique<swaws::Text>(swaws::Resources().GetWithID<swaws::Font>("uiF", "8bitOperatorPlus8-Regular.ttf", 48));
    m_pressSpace = std::make_unique<swaws::Text>(swaws::Resources().GetWithID<swaws::Font>("titleF", "8bitOperatorPlus8-Regular.ttf", 64));

    swaws::GetEngine().GetAudio().PlaySound(*swaws::Resources().Get<swaws::AudioClip>("sndtrack.wav", swaws::GetEngine().GetAudio()));

    return true;
}

void SpaceGame::Update(float dt)
{
    switch (m_gameState)
    {
    case SpaceGame::GameState::Initialize:
        m_gameState = GameState::Title;
        break;
    case SpaceGame::GameState::Title:
        if (swaws::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) m_gameState = GameState::StartGame;
        break;
    case SpaceGame::GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_gameState = GameState::StartRound;
        break;
    case SpaceGame::GameState::StartRound:
    {
        scene->RemoveAllActors();
        auto player = swaws::Instantiate("player");
        scene->AddActor(std::move(player), true);

        /*
        //std::shared_ptr<swaws::Model> model = std::make_shared <swaws::Model>(GameData::playerPoints, swaws::vec3{ 0.0f, 1.0f, 0.8f });
        swaws::Transform transform(swaws::vec2{ swaws::GetEngine().GetRenderer().GetWindowWidth() * 0.5f, swaws::GetEngine().GetRenderer().GetWindowHeight() * 0.5f }, 0, 1);
        std::unique_ptr<Player> player = std::make_unique<Player>(transform);

        player->speed = 1500; // Set player Speed
        player->maxSpeed = 2000;
        player->rotationRate = 180; // Set Rotation Rate
        player->tag = "player";
        player->name = "player";

        auto mr = std::make_unique<swaws::MeshRenderer>();
        mr->meshName = "spaceship-sprites/blue_01.png";

        auto sr = std::make_unique<swaws::SpriteRenderer>();
        sr->textureName = "spaceship-sprites/blue_01.png";

        auto rb = std::make_unique<swaws::RigidBody>();
        rb->damping = 0.5f; // Set Damping for player

        auto collider = std::make_unique<swaws::CircleCollider2D>();
        collider->radius = 60;

        // Add Components to Player
        player->AddComponent(std::move(sr));
        player->AddComponent(std::move(rb));
        player->AddComponent(std::move(collider));

        scene->AddActor(std::move(player));
        m_gameState = GameState::Game;

        // Set up UI Icons
        float scale = 5;
        std::shared_ptr<swaws::Model> rocketIcon = std::make_shared<swaws::Model>(GameData::rocketIconPoints, swaws::vec3{ 0.0f, 1.0f, 0.0f });
        std::shared_ptr<swaws::Model> laserIcon = std::make_shared<swaws::Model>(GameData::laserIconPoints, swaws::vec3{ 1.0f, 0.0f, 0.0f });

        swaws::Transform rITransform(swaws::vec2{ swaws::GetEngine().GetRenderer().GetWindowWidth() - (10 * scale), (20 * scale) }, 0, scale);
        swaws::Transform lITransform(swaws::vec2{ swaws::GetEngine().GetRenderer().GetWindowWidth() - (10 * scale), (40 * scale) }, 0, scale);
        std::unique_ptr<UIModel> rocketIconModel = std::make_unique<UIModel>(rITransform, rocketIcon);
        std::unique_ptr<UIModel> laserIconModel = std::make_unique<UIModel>(lITransform, laserIcon);

        rocketIconModel->speed = 0;
        laserIconModel->speed = 0;

        rocketIconModel->tag = "ui";
        laserIconModel->tag = "ui";

        rocketIconModel->name = "rocketIc";
        laserIconModel->name = "laserIc";

        scene->AddActor(std::move(rocketIconModel));
        scene->AddActor(std::move(laserIconModel));
        */
    }
        break;
    case SpaceGame::GameState::Game:
        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0)
        {
            m_enemySpawnTimer = 4;
            SpawnEnemy();
        }
        break;
    case SpaceGame::GameState::PlayerDead:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_lives--;
            if (m_lives == 0)
            {
                m_stateTimer = 3;
                swaws::GetEngine().GetAudio().PlaySound(*swaws::Resources().Get<swaws::AudioClip>("gameOver_pacman.wav", swaws::GetEngine().GetAudio()));
                m_gameState = GameState::GameOver;
            }
            else m_gameState = GameState::StartRound;
        }
        break;
    case SpaceGame::GameState::GameOver:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) m_gameState = GameState::Title;
        break;
    default:
        break;
    }

    // WE CHECK KEYS HERE
    // Q = SUPER HOT
    if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Q)) swaws::GetEngine().GetTime().SetTimeScale(0.2f); // SUPER HOT SUPER HOT SUPER HOT
    else swaws::GetEngine().GetTime().SetTimeScale(1.0f);

    // F = CHANGE WEAPON, IMPLEMENT AS MOVE TO NEXT
    if (swaws::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_F))
    {
        Player* player = dynamic_cast<Player*>(scene->GetActorByName("player"));
        if (player)
        {
            
            int weaponAmount = static_cast<int>(Player::Weapon::Count);
            int curWeapon = static_cast<int>(player->CurWeapon());
            player->SelectWeapon(static_cast<Player::Weapon>((curWeapon + 1) % weaponAmount));

            // With more weapons, this'll be longer
            switch (curWeapon)
            {
            case 0: // ROCKET -> LASER
                player->fireTime = 5;
                break;
            case 1: // LASER -> ROCKET
                player->fireTime = 0.2f;
                break;
            default:
                break;
            }
        }
    }
    scene->Update(swaws::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Shutdown()
{
    //
}

void SpaceGame::Draw(swaws::Renderer& renderer)
{
    if (m_gameState == GameState::Title)
    {
        m_titleText->Create(renderer, "OUI WUZ SPACE", swaws::vec3{ 1, 0, 0 });
        m_titleText->Draw(renderer, 400, 400);

        m_pressSpace->Create(renderer, "PRESS SPACE TO PLAY", { 1, 0, 0 });
        m_pressSpace->Draw(renderer, 300, 600);
    }
    if (m_gameState == GameState::GameOver)
    {
        m_titleText->Create(renderer, "GAME OVER", swaws::vec3{ 1, 0, 0 });
        m_titleText->Draw(renderer, 400, 400);
    }

    // Score and "Other Stuff"
    m_scoreText->Create(renderer, "SCORE    " + std::to_string(m_score), {1, 1, 1});
    m_scoreText->Draw(renderer, 20, 20);

    m_livesText->Create(renderer, "LIVES    " + std::to_string(m_lives), {1, 1, 1});
    m_livesText->Draw(renderer, (float)renderer.GetWindowWidth() - 300.0f, 20);

    scene->Draw(renderer);
    swaws::GetEngine().GetPS().Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
    m_gameState = GameState::PlayerDead;
    m_stateTimer = 2;
}

void SpaceGame::OnNotify(const swaws::Event& event)
{
    if (swaws::compareIgnore(event.id, "player_dead")) { 
        OnPlayerDeath(); 
    }
    else if (swaws::compareIgnore(event.id, "add_points"))
    {
        AddPoints(std::get<int>(event.data));
    }
    std::cout << event.id << std::endl;
}


void SpaceGame::SpawnEnemy()
{   
    auto playerActor = scene->GetActorByName<Player>("player");
    if (!playerActor) return; // Player does not exist
    auto player = playerActor->owner;
    if (player) // Check if the player (component) has an owner
    {
        // Spawn @ Random Position away from Player
        swaws::vec2 position = player->transform.position + swaws::random::onUnitCircle() * swaws::random::getReal(200.0f, 500.0f);
        swaws::Transform transform{ position, swaws::random::getReal(0.0f, 360.0f), 1 };
        auto enemy = swaws::Instantiate("enemy", transform);
        scene->AddActor(std::move(enemy), true);
    }
}