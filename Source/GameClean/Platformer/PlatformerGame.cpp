#include "PlatformerGame.h"

bool PlatformerGame::Initialize()
{
    OBSERVER_ADD(player_dead);
    OBSERVER_ADD(add_points);

    scene = std::make_unique<swaws::Scene>(this);
    if (!scene->Load("scenes/prototypes.json")) {
        swaws::Logger::Error("Scene boot failed: {}", "prototypes.json");
        return false;
    }
    if (!scene->Load("scenes/level.json")) {
        swaws::Logger::Error("Scene boot failed: {}", "level.json");
        return false;
    }

    m_gameState = GameState::StartRound;

    return true;
}

void PlatformerGame::Update(float dt)
{
    switch (m_gameState)
    {
    case PlatformerGame::GameState::Initialize:
        break;
    case PlatformerGame::GameState::Title:
        break;
    case PlatformerGame::GameState::StartGame:
        break;
    case PlatformerGame::GameState::StartRound:
        // Spawn Player
        SpawnPlayer();
        m_gameState = GameState::Game;
        break;
    case PlatformerGame::GameState::Game:
        break;
    case PlatformerGame::GameState::PlayerDead:
        break;
    case PlatformerGame::GameState::GameOver:
        break;
    default:
        break;
    }
    scene->Update(swaws::GetEngine().GetTime().GetDeltaTime());
}

void PlatformerGame::Shutdown()
{
    //
}

void PlatformerGame::Draw(swaws::Renderer& renderer)
{
    scene->Draw(renderer);
    swaws::GetEngine().GetPS().Draw(renderer);
}

void PlatformerGame::OnPlayerDeath()
{
    m_gameState = GameState::PlayerDead;
    m_stateTimer = 2;
}

void PlatformerGame::OnNotify(const swaws::Event& event)
{
}

void PlatformerGame::SpawnEnemy()
{

}

void PlatformerGame::SpawnPlayer()
{
    auto player = swaws::Instantiate("platform_player");
    //player->transform.position = swaws::vec2{ swaws::random::getReal(0.0f, 1080.0f), swaws::random::getReal(0.0f, 100.0f) };
    scene->AddActor(std::move(player), true);
}
