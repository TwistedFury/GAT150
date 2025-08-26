#pragma once
#include "Event/Observer.h"
#include "Event/Event.h"
#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

class SpaceGame : public swaws::Game, public swaws::IObserver
{
public:
	enum class GameState
	{
		Initialize,
		Title,
		StartGame,
		StartRound,
		Game,
		PlayerDead,
		GameOver
	};

public:
	SpaceGame() = default;

	bool Initialize() override;
	void Update(float dt) override;
	void Shutdown() override;
	void Draw(swaws::Renderer& renderer) override;

	void OnPlayerDeath();
	void OnNotify(const swaws::Event& event) override;
	
private:
	GameState m_gameState{ GameState::Initialize };
	float m_enemySpawnTimer{ 0 };

	float m_stateTimer{ 0 };

	std::shared_ptr<swaws::Font> m_titleFont;
	std::shared_ptr<swaws::Font> m_uiFont;

	std::unique_ptr<swaws::Text> m_titleText;
	std::unique_ptr<swaws::Text> m_scoreText;
	std::unique_ptr<swaws::Text> m_livesText;
	std::unique_ptr<swaws::Text> m_pressSpace;

	void SpawnEnemy();
};