#pragma once

#include "Framework/Component.h" 
#include "Physics/Collidable.h"

class PlayerController : public swaws::Component, public swaws::Collidable
{
public:
	float speed{ 0 };
	float maxSpeed{ 0 };
	float jump{ 0 };

	swaws::RigidBody* rigidBody{ nullptr };
public:
	PlayerController() = default;
	CLASS_PROTOTYPE(PlayerController)

	void Read(const swaws::json::value_t& value) override;

	void Update(float dt) override;

	void Start() override;

	void OnCollision(class swaws::Actor* other) override;
};