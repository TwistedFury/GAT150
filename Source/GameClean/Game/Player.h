#pragma once

#include "Framework/Component.h" 

class Player : public swaws::Component
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
	
	//Player(const swaws::Transform& transform) :
	//	swaws::Actor{ transform } { }

	void Update(float dt) override;

	void OnCollision(class Actor* other);

	void SelectWeapon(Weapon weapon);

	Weapon CurWeapon() const { return weapon; }
private:
	Weapon weapon{ Weapon::Rocket };
};