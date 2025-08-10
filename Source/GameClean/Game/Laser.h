#pragma once
#include "Framework/Actor.h"
#include "Renderer/Renderer.h"
#include "Engine.h"
#include <iostream>

class Laser : public swaws::Actor
{
public:
	bool pierce{ false };

public:
	Laser() = default;

	Laser(const swaws::Transform& transform, swaws::res_t<swaws::Texture> texture) :
		swaws::Actor{ transform, texture } 
	{
		length = (float)swaws::GetEngine().GetRenderer().GetWindowWidth();
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

	float GetRadius() override;

private:
};