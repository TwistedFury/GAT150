#pragma once
#include "EngineInc.h"

class UIModel : public swaws::Actor
{
public:
	// Inherited via Actor
	void OnCollision(Actor* other) override
	{
	}

	UIModel(const swaws::Transform& transform, std::shared_ptr<swaws::Texture> texture) :
		swaws::Actor{ transform, texture } { speed = 0; }
};