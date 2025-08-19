#pragma once

#include "Framework/Component.h" 

class Enemy : public swaws::Component
{
public:
	float fireTime{ 0 };
	float fireTimer{ fireTime };

public:
	Enemy() = default;

	//Enemy(const swaws::Transform& transform) :
	//	swaws::Actor{ transform } { }

	void Update(float dt) override;

	void OnCollision(class Actor* other);

private:
	

};