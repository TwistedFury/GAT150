#pragma once

#include "Framework/Component.h"
#include "Physics/Collidable.h"
#include "Engine.h"
#include "Audio/AudioSystem.h"

class Rocket : public swaws::Component, public swaws::Collidable
{
public:
	Rocket() = default;
	CLASS_PROTOTYPE(Rocket)

	void Update(float dt) override;

	void OnCollision(class swaws::Actor* other) override;

};