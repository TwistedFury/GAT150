#pragma once

#include "Framework/Component.h" 
#include "Physics/Collidable.h"

class Player : public swaws::Component, public swaws::Collidable
{
public:
	float speed = 200;
	float rotationRate = 180;
	float fireTime = 0.2f;
	float fireTimer = 0;

	enum class Weapon
	{
		Rocket,
		Laser,
		Count // Always at end so we know how many exist
	};

	swaws::RigidBody* rigidBody{ nullptr };
public:
	Player() = default;
	CLASS_PROTOTYPE(Player)

	void Read(const swaws::json::value_t& value) override;

	void Update(float dt) override;

	void Start() override;

	void OnCollision(class swaws::Actor* other) override;

	void SelectWeapon(Weapon weapon);

	Weapon CurWeapon() const { return weapon; }
private:
	Weapon weapon{ Weapon::Rocket };
};