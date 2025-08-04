#pragma once
#include "EngineInc.h"

class UIModel : public swaws::Actor
{
public:
	// Inherited via Actor
	void OnCollision(Actor* other) override
	{
	}

	UIModel(const swaws::Transform& transform, std::shared_ptr<swaws::Model> model) :
		swaws::Actor{ transform, model } { speed = 0; }

	swaws::vec3 GetColor() { return swaws::Actor::GetColor(); }

	void SetColor(swaws::vec3 color) { swaws::Actor::SetColor(color); }
};