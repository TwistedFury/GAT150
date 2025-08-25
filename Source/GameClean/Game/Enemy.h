#pragma once

#include "Framework/Component.h" 
#include "Physics/Collidable.h"

class Enemy : public swaws::Component, public swaws::Collidable
{
public:
	float fireTime{ 0 };
	float fireTimer{ fireTime };

	swaws::RigidBody* rigidBody{ nullptr };

public:
	Enemy() = default;
	CLASS_PROTOTYPE(Enemy)

	void Update(float dt) override;
	void OnCollision(class swaws::Actor* other) override;

	void Start() override;

private:
	

};