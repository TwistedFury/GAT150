#pragma once

#include "Framework/Component.h" 
#include "Physics/Collidable.h"
#include "Event/Observer.h"

class Enemy : public swaws::Component, public swaws::Collidable, public swaws::IObserver
{
public:
	float fireTime{ 0 };
	float fireTimer{ fireTime };
	float speed{ 0 };

	swaws::RigidBody* rigidBody{ nullptr };

public:
	Enemy() = default;
	CLASS_PROTOTYPE(Enemy)

	void Update(float dt) override;
	void OnCollision(class swaws::Actor* other) override;

	void Start() override;
	void Read(const swaws::json::value_t& value) override;

	// Inherited via IObserver
	void OnNotify(const swaws::Event& event) override;
};