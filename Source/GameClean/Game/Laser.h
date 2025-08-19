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

	//Laser(const swaws::Transform& transform) :
	//	swaws::Actor{ transform } 
	//{
	//	length = (float)swaws::GetEngine().GetRenderer().GetWindowWidth();
	//}

	void Update(float dt) override;

	void OnCollision(class Actor* other);

	//float GetRadius() override;

private:
};