#pragma once
#include "../GamePCH.h"
#include "Enemy.h"
#include "Player.h"
#include "GameData.h"
#include "Rocket.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt)
{
    bool playerSeen = false;

    auto playerActor = owner->scene->GetActorByName("player");

    float rocketOffset{ 0 };
    if (!playerActor) return;
    auto player = playerActor->GetComponent<Player>();
    if (player && rigidBody) {
        swaws::vec2 direction{ 0, 0 };
        direction = player->rigidBody->GetBody()->GetPosition() - rigidBody->GetBody()->GetPosition();

        direction = direction.Normalized();
        swaws::vec2 forward = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(rigidBody->GetBody()->GetAngle()));

        float angle = swaws::math::RadToDeg(swaws::vec2::AngleBetween(forward, direction));
        playerSeen = angle <= 30;

        if (playerSeen) {
            float angle = swaws::vec2::SignedAngleBetween(forward, direction);
            angle = swaws::math::sign(angle);
            rigidBody->ApplyTorque(swaws::math::DegToRad(angle));
        }

        swaws::vec2 force = swaws::vec2{ 1, 0 }.Rotate(rigidBody->GetBody()->GetAngle()) * owner->speed;
        rigidBody->ApplyForce(force);

        // Set Rocket Offset (In here because direction is needed)
        rocketOffset = direction.x * 10;
    }

    // check fire
    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen) {
        fireTimer = fireTime;
        
        swaws::Transform transform{ rigidBody->GetBody()->GetPosition(), swaws::math::RadToDeg(rigidBody->GetBody()->GetAngle()), 1.0f};
        transform.position += { rocketOffset, rocketOffset };
        auto rocket = swaws::Instantiate("rocket_enemy", transform);

        owner->scene->AddActor(std::move(rocket), true);
        swaws::GetEngine().GetAudio().PlaySound(*swaws::Resources().Get<swaws::AudioClip>("blaster.wav", swaws::GetEngine().GetAudio()));
    }
}


void Enemy::OnCollision(swaws::Actor* other)
{
    if (owner->tag != other->tag)
    {
        owner->destroyed = true;
        EVENT_NOTIFY_DATA(add_points, 100);
        // Explosion Particles
        for (int i = 0; i < 100; i++)
        {
            swaws::Particle particle;
            particle.position = owner->transform.position;
            particle.velocity = swaws::vec2{ swaws::random::getReal(-200.0f, 200.0f), swaws::random::getReal(-200.0f, 200.0f) };
            particle.color = swaws::vec3{ 1, 1, 1 };
            particle.lifespan = 2;

            swaws::GetEngine().GetPS().AddParticle(particle);
        }
        swaws::GetEngine().GetAudio().PlaySound(*swaws::Resources().Get<swaws::AudioClip>("explosion.wav", swaws::GetEngine().GetAudio()));
    }
}

void Enemy::Start()
{
    swaws::EventManager::Instance().AddObserver("player_dead", *this);
    rigidBody = owner->GetComponent<swaws::RigidBody>();
}

void Enemy::Read(const swaws::json::value_t& value)
{
    Object::Read(value);

    JSON_READ(value, speed);
    JSON_READ(value, fireTime);
}

void Enemy::OnNotify(const swaws::Event& event)
{
    if (swaws::compareIgnore(event.id, "player_dead")) owner->destroyed = true;
}
