#pragma once

#include "Framework/Component.h" 

class Enemy : public swaws::Component
{
public:
	float fireTime{ 0 };
	float fireTimer{ fireTime };

public:
	Enemy() = default;

	void Update(float dt) override;
	void OnCollision(class swaws::Actor* other);

private:
	

};