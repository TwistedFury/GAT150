#pragma once

#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "UIModel.h"
#include "GameData.h"
#include "EngineInc.h"

#include <vector>

bool SpaceGame::Initialize()
{
    scene = std::make_unique<swaws::Scene>(this);

    //m_titleFont = std::make_shared<swaws::Font>();
    //m_titleFont->Load("8bitOperatorPlus8-Regular.ttf", 64);

    //m_uiFont = std::make_shared<swaws::Font>();
    //m_uiFont->Load("8bitOperatorPlus8-Regular.ttf", 48);

    m_titleText = std::make_unique<swaws::Text>(swaws::Resources().GetWithID<swaws::Font>("titleF", "8bitOperatorPlus8-Regular.ttf", 64));
    m_scoreText = std::make_unique<swaws::Text>(swaws::Resources().GetWithID<swaws::Font>("uiF", "8bitOperatorPlus8-Regular.ttf", 48));
    m_livesText = std::make_unique<swaws::Text>(swaws::Resources().GetWithID<swaws::Font>("uiF", "8bitOperatorPlus8-Regular.ttf", 48));
    m_pressSpace = std::make_unique<swaws::Text>(swaws::Resources().GetWithID<swaws::Font>("titleF", "8bitOperatorPlus8-Regular.ttf", 64));

    // Initialize Laser Points
    GameData::laserPoints = std::vector<swaws::vec2>{
    { 0, 0 },
    { (float)swaws::GetEngine().GetRenderer().GetWindowWidth(), 0}
    };

    swaws::GetEngine().GetAudio().playSound("soundtrack", 0, false, 0);

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
        //std::shared_ptr<swaws::Model> model = std::make_shared <swaws::Model>(GameData::playerPoints, swaws::vec3{ 0.0f, 1.0f, 0.8f });
        swaws::Transform transform(swaws::vec2{ swaws::GetEngine().GetRenderer().GetWindowWidth() * 0.5f, swaws::GetEngine().GetRenderer().GetWindowHeight() * 0.5f }, 0, 5);
        std::unique_ptr<Player> player = std::make_unique<Player>(transform, swaws::Resources().Get<swaws::Texture>("spaceship-sprites/blue_01.png", swaws::GetEngine().GetRenderer()));
        player->damping = 0.5f; // Set Damping for player
        player->speed = 1500; // Set player Speed
        player->rotationRate = 180; // Set Rotation Rate

        // Give player name
        player->tag = "player";
        player->name = "player";
        scene->AddActor(std::move(player));
        m_gameState = GameState::Game;

        // Set up UI Icons
        float scale = 5;
        //std::shared_ptr<swaws::Model> rocketIcon = std::make_shared<swaws::Model>(GameData::rocketIconPoints, swaws::vec3{ 0.0f, 1.0f, 0.0f });
        //std::shared_ptr<swaws::Model> laserIcon = std::make_shared<swaws::Model>(GameData::laserIconPoints, swaws::vec3{ 1.0f, 0.0f, 0.0f });

        swaws::Transform rITransform(swaws::vec2{ swaws::GetEngine().GetRenderer().GetWindowWidth() - (10 * scale), (20 * scale) }, 0, scale);
        swaws::Transform lITransform(swaws::vec2{ swaws::GetEngine().GetRenderer().GetWindowWidth() - (10 * scale), (40 * scale) }, 0, scale);
        //std::unique_ptr<UIModel> rocketIconModel = std::make_unique<UIModel>(rITransform, rocketIcon);
        //std::unique_ptr<UIModel> laserIconModel = std::make_unique<UIModel>(lITransform, laserIcon);

        //rocketIconModel->speed = 0;
        //laserIconModel->speed = 0;

        //rocketIconModel->tag = "ui";
        //laserIconModel->tag = "ui";

        //rocketIconModel->name = "rocketIc";
        //laserIconModel->name = "laserIc";

        //scene->AddActor(std::move(rocketIconModel));
        //scene->AddActor(std::move(laserIconModel));
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
                swaws::GetEngine().GetAudio().playSound("gameOver", 0, false, 0);
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

            //// With more weapons, this'll be longer
            //switch (curWeapon)
            //{
            //case 0: // ROCKET -> LASER
            //    scene->GetActorByName("rocketIc")->SetColor({ 1.0f, 0.0f, 0.0f });
            //    scene->GetActorByName("laserIc")->SetColor({ 0.0f, 1.0f, 0.0f });
            //    player->fireTime = 5;
            //    break;
            //case 1: // LASER -> ROCKET
            //    scene->GetActorByName("laserIc")->SetColor({ 1.0f, 0.0f, 0.0f });
            //    scene->GetActorByName("rocketIc")->SetColor({ 0.0f, 1.0f, 0.0f });
            //    player->fireTime = 0.2f;
            //    break;
            //default:
            //    break;
            //}
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

void SpaceGame::SpawnEnemy()
{   
    Player* player = scene->GetActorByName<Player>("player");
    if (player)
    {
        // Spawn @ Random Position away from Player
        swaws::vec2 position = player->transform.position + swaws::random::onUnitCircle() * swaws::random::getReal(200.0f, 500.0f);
        swaws::Transform transform{ position, swaws::random::getReal(0.0f, 360.0f), 5};
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, swaws::Resources().Get<swaws::Texture>("spaceship-sprites/large-blue-02.png", swaws::GetEngine().GetRenderer()));

        enemy->damping = 0.7f;
        enemy->speed = (swaws::random::getReal() * 200) + 100;
        enemy->tag = "enemy";
        enemy->fireTime = 2;
        enemy->fireTimer = 5;
        scene->AddActor(std::move(enemy));
    }
}
