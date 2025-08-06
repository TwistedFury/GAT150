#pragma once

#include "Framework/Actor.h" 

class Player : public swaws::Actor
{
public:
	float rotationRate = 180;

	float fireTime = 0.2f;
	float fireTimer = 0;

	enum class Weapon
	{
		Rocket,
		Laser,
		Count // Always at end so we know how many exist
	};
public:
	Player() = default;
	
	Player(const swaws::Transform& transform, swaws::res_t<swaws::Texture> texture) :
		swaws::Actor{ transform, texture } { this->damping = 0.2f; }

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

	void SelectWeapon(Weapon weapon);

	Weapon CurWeapon() const { return weapon; }
private:
	Weapon weapon{ Weapon::Rocket };
};