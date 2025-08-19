#pragma once

#include "Framework/Component.h"
#include "Engine.h"
#include "Audio/AudioSystem.h"

class Rocket : public swaws::Component
{
public:
	Rocket() = default;

	//Rocket(const swaws::Transform& transform) :
	//	swaws::Actor{ transform } {}

	void Update(float dt) override;

	void OnCollision(class Actor* other);

};