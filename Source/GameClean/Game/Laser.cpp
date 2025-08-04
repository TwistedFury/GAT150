#pragma once

#include "Laser.h"
#include "Engine.h"
#include "EngineInc.h"
#include "Player.h"

void Laser::Update(float dt)
{
    Player* player = dynamic_cast<Player*>(scene->GetActorByName("player"));
    if (player)
    {
        transform = player->transform;
        lifespan -= dt;
        if (lifespan <= 0) destroyed = true;
    }
}

void Laser::OnCollision(Actor* other)
{
    if (pierce)
    {

    }
    else
    {

    }
}

float Laser::GetRadius()
{
    return 2 * transform.scale * 0.9f;
}
