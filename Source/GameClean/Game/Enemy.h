#pragma once

#include "Framework/Actor.h" 

class Enemy : public swaws::Actor
{
public:
	float fireTime{ 0 };
	float fireTimer{ fireTime };

public:
	Enemy() = default;

	Enemy(const swaws::Transform& transform) :
		swaws::Actor{ transform } { }

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

private:
	

};