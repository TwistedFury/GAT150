#pragma once
#include "../GamePCH.h"
#include "Laser.h"
#include "Player.h"

FACTORY_REGISTER(Laser)

void Laser::Update(float dt)
{
    //Player* player = dynamic_cast<Player*>(scene->GetActorByName("player"));
    //if (player)
    //{
    //    transform = player->transform;
    //    lifespan -= dt;
    //    if (lifespan <= 0) destroyed = true;
    //}
}

void Laser::OnCollision(swaws::Actor* other)
{
    if (pierce)
    {

    }
    else
    {

    }
}
