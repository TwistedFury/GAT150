#pragma once
#include "../GamePCH.h"
#include "Enemy.h"
#include "Player.h"
#include "GameData.h"
#include "Rocket.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt)
{
//    bool playerSeen = false;
//
//    Player* player = scene->GetActorByName<Player>("player");
//    if (player) {
//        swaws::vec2 direction{ 0, 0 };
//        direction = player->transform.position - transform.position;
//
//        direction = direction.Normalized();
//        swaws::vec2 forward = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(transform.rotation));
//
//        float angle = swaws::math::RadToDeg(swaws::vec2::AngleBetween(forward, direction));
//        playerSeen = angle <= 30;
//
//        if (playerSeen) {
//            float angle = swaws::vec2::SignedAngleBetween(forward, direction);
//            angle = swaws::math::sign(angle);
//            transform.rotation += swaws::math::RadToDeg(angle * 5 * dt);
//        }
//    }
//
//    swaws::vec2 force = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(transform.rotation)) * speed;
//    //velocity += force * dt;
//
//    if (rigidBody) {
//        rigidBody->velocity += force * dt;
//
//        float velMag = rb->velocity.Length();
//        if (velMag > maxSpeed) {
//            rigidBody->velocity = rigidBody->velocity.Normalized() * maxSpeed;
//        }
//    }
//
//    transform.position.x = swaws::math::wrap(transform.position.x, 0.0f, (float)swaws::GetEngine().GetRenderer().GetWindowWidth());
//    transform.position.y = swaws::math::wrap(transform.position.y, 0.0f, (float)swaws::GetEngine().GetRenderer().GetWindowHeight());
//
//    // check fire
//    fireTimer -= dt;
//    if (fireTimer <= 0 && playerSeen) {
//        fireTimer = fireTime;
//        
//        swaws::Transform transform{ this->transform.position, this->transform.rotation, 1.0f };
//        auto rocket = std::make_unique<Rocket>(transform);
//        rocket->speed = 200;
//        rocket->lifespan = 1.5f;
//        rocket->name = "rocket";
//        rocket->tag = "enemy";
//
//        // Components
//        auto sr = std::make_unique<swaws::SpriteRenderer>();
//        sr->textureName = "spaceship-sprites/projectiles/projectile05-1.png";
//        
//        auto rb = std::make_unique<swaws::RigidBody>();
//        rb->damping = 0.0f; // Set Damping for rocket
//
//        auto collider = std::make_unique<swaws::CircleCollider2D>();
//        collider->radius = 20;
//
//        rocket->AddComponent(std::move(sr));
//        rocket->AddComponent(std::move(rb));
//        rocket->AddComponent(std::move(collider));
//
//        scene->AddActor(std::move(rocket));
//        swaws::GetEngine().GetAudio().PlaySound(*swaws::Resources().Get<swaws::AudioClip>("blaster.wav", swaws::GetEngine().GetAudio()));
//    }
//
//    Actor::Update(dt);
}


void Enemy::OnCollision(swaws::Actor* other)
{
    if (owner->tag != other->tag)
    {
        owner->destroyed = true;
        owner->scene->GetGame()->AddPoints(100);
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
    rigidBody = owner->GetComponent<swaws::RigidBody>();
}
