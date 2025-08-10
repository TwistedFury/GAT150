#pragma once
#include "EngineInc.h"
#include "Enemy.h"
#include "Player.h"
#include "GameData.h"
#include "Rocket.h"

void Enemy::Update(float dt)
{
    bool playerSeen = false;

    Player* player = scene->GetActorByName<Player>("player");
    if (player) {
        swaws::vec2 direction{ 0, 0 };
        direction = player->transform.position - transform.position;

        direction = direction.Normalized();
        swaws::vec2 forward = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(transform.rotation));

        float angle = swaws::math::RadToDeg(swaws::vec2::AngleBetween(forward, direction));
        playerSeen = angle <= 30;

        if (playerSeen) {
            float angle = swaws::vec2::SignedAngleBetween(forward, direction);
            angle = swaws::math::sign(angle);
            transform.rotation += swaws::math::RadToDeg(angle * 5 * dt);
        }
    }

    swaws::vec2 force = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(transform.rotation)) * speed;
    velocity += force * dt;

    float velMag = velocity.Length();
    if (velMag > maxSpeed) {
        velocity = velocity.Normalized() * maxSpeed;
    }

    transform.position.x = swaws::math::wrap(transform.position.x, 0.0f, (float)swaws::GetEngine().GetRenderer().GetWindowWidth());
    transform.position.y = swaws::math::wrap(transform.position.y, 0.0f, (float)swaws::GetEngine().GetRenderer().GetWindowHeight());

    // check fire
    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen) {
        fireTimer = fireTime;

        //std::shared_ptr<swaws::Model> model = std::make_shared<swaws::Model>(GameData::playerPoints, swaws::vec3{ 0.0f, 1.0f, 0.0f });
        // spawn rocket at player position and rotation
        //swaws::Transform transform{ this->transform.position, this->transform.rotation, 2.0f };
        //auto rocket = std::make_unique<Rocket>(transform, texture);
        //rocket->speed = 500.0f;
        //rocket->lifespan = 1.5f;
        //rocket->name = "rocket";
        //rocket->tag = "enemy";

        //scene->AddActor(std::move(rocket));
        //swaws::GetEngine().GetAudio().playSound("blaster", 0, false, 0);
    }

    Actor::Update(dt);
}


void Enemy::OnCollision(Actor* other)
{
    if (tag != other->tag)
    {
        destroyed = true;
        scene->GetGame()->AddPoints(100);
        // Explosion Particles
        for (int i = 0; i < 100; i++)
        {
            swaws::Particle particle;
            particle.position = transform.position;
            particle.velocity = swaws::vec2{ swaws::random::getReal(-200.0f, 200.0f), swaws::random::getReal(-200.0f, 200.0f) };
            particle.color = swaws::vec3{ 1, 1, 1 };
            particle.lifespan = 2;

            swaws::GetEngine().GetPS().AddParticle(particle);
        }
        swaws::GetEngine().GetAudio().playSound("explosion", 0, false, 0);
    }
}
