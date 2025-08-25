#pragma once
#include "Framework/Component.h"
#include "Physics/Collidable.h"
#include "Renderer/Renderer.h"
#include "Engine.h"
#include <iostream>

class Laser : public swaws::Component, public swaws::Collidable
{
public:
	bool pierce{ false };

public:
	Laser() = default;
	CLASS_PROTOTYPE(Laser)

	void Update(float dt) override;

	void OnCollision(class swaws::Actor* other) override;

private:
};