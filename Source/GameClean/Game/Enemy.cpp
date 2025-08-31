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
    if (!playerActor) return;
    auto player = playerActor->GetComponent<Player>();
    if (player) {
        swaws::vec2 direction{ 0, 0 };
        direction = player->owner->transform.position - owner->transform.position;

        direction = direction.Normalized();
        swaws::vec2 forward = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(owner->transform.rotation));

        float angle = swaws::math::RadToDeg(swaws::vec2::AngleBetween(forward, direction));
        playerSeen = angle <= 30;

        if (playerSeen) {
            float angle = swaws::vec2::SignedAngleBetween(forward, direction);
            angle = swaws::math::sign(angle);
            owner->transform.rotation += swaws::math::RadToDeg(angle * 5 * dt);
        }
    }

    swaws::vec2 force = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(owner->transform.rotation)) * owner->speed;
    //velocity += force * dt;

    if (rigidBody) {
        rigidBody->velocity += force * dt;

        float velMag = rigidBody->velocity.Length();
        if (velMag > owner->maxSpeed) {
            rigidBody->velocity = rigidBody->velocity.Normalized() * owner->maxSpeed;
        }
    }

    owner->transform.position.x = swaws::math::wrap(owner->transform.position.x, 0.0f, (float)swaws::GetEngine().GetRenderer().GetWindowWidth());
    owner->transform.position.y = swaws::math::wrap(owner->transform.position.y, 0.0f, (float)swaws::GetEngine().GetRenderer().GetWindowHeight());

    // check fire
    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen) {
        fireTimer = fireTime;
        
        swaws::Transform transform{ owner->transform.position, owner->transform.rotation, 1.0f };
        auto rocket = swaws::Instantiate("rocket");

        owner->scene->AddActor(std::move(rocket), true);
        swaws::GetEngine().GetAudio().PlaySound(*swaws::Resources().Get<swaws::AudioClip>("blaster.wav", swaws::GetEngine().GetAudio()));
    }

    owner->Actor::Update(dt);
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

void Enemy::OnNotify(const swaws::Event& event)
{
    if (swaws::compareIgnore(event.id, "player_dead")) owner->destroyed = true;
}
