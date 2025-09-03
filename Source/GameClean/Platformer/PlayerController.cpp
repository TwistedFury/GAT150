#include "../GamePCH.h"
#include "PlayerController.h"

FACTORY_REGISTER(PlayerController);

void PlayerController::Read(const swaws::json::value_t& value)
{
	Object::Read(value);
	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
}

void PlayerController::Update(float dt)
{
    float dir = 0;
    if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1;
    if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = +1;

	if (dir != 0)
	{
		rigidBody->ApplyForce(swaws::vec2{ 1, 0 } * dir * 1000);
	}

	if (swaws::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
	{
		rigidBody->ApplyForce(swaws::vec2{ 0, -1 } * 100000);
	}
}

void PlayerController::Start()
{
	rigidBody = owner->GetComponent<swaws::RigidBody>();
}

void PlayerController::OnCollision(swaws::Actor* other)
{
}
