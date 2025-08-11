#pragma once

#include "Framework/Actor.h"
#include "Engine.h"
#include "Audio/AudioSystem.h"

class Rocket : public swaws::Actor
{
public:
	Rocket() = default;

	Rocket(const swaws::Transform& transform) :
		swaws::Actor{ transform } {}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

};