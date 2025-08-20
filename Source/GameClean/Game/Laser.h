#pragma once
#include "Framework/Component.h"
#include "Renderer/Renderer.h"
#include "Engine.h"
#include <iostream>

class Laser : public swaws::Component
{
public:
	bool pierce{ false };

public:
	Laser() = default;

	void Update(float dt) override;

	void OnCollision(class swaws::Actor* other);

private:
};