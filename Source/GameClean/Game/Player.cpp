#pragma once
#include "../GamePCH.h"
#include "Player.h"
#include "Rocket.h"
#include "Laser.h"
#include "SpaceGame.h"

FACTORY_REGISTER(Player)

void Player::Read(const swaws::json::value_t& value)
{
    Object::Read(value);

    JSON_READ(value, speed);
    JSON_READ(value, rotationRate);
    JSON_READ(value, fireTime);
}

void Player::Update(float dt)
{
    if (!owner) return;

    if (!rigidBody)
    {
        rigidBody = owner->GetComponent<swaws::RigidBody>();
        if (!rigidBody) return;
    }
    float angle = owner->transform.rotation + swaws::random::getReal(-60.0f, 60.0f);
    swaws::vec2 pv = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(angle));
    pv *= swaws::random::getReal(80.0f, 150.0f);

    if (rigidBody && rigidBody->velocity.Normalized().x != 0)
    {
        float offsetDistance = -25;
        swaws::vec2 offset = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(owner->transform.rotation)) * offsetDistance;

        swaws::Particle particle;
        particle.position = owner->transform.position + offset;
        particle.velocity = pv * swaws::vec2{ swaws::random::getReal(-50.0f, 50.0f),
                                              swaws::random::getReal(-50.0f, 50.0f) };
        particle.color = swaws::vec3{ 1, 1, 1 };
        particle.lifespan = 0.5f;
        swaws::GetEngine().GetPS().AddParticle(particle);
    }

    float rotate = 0;
    if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

    rigidBody->ApplyTorque(swaws::math::DegToRad(rotate * rotationRate));

    float thrust = 0;
    if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
    if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    swaws::vec2 direction{ 1, 0 };
    swaws::vec2 force = direction.Rotate(rigidBody->GetBody()->GetAngle()) * thrust * speed;
    rigidBody->ApplyForce(force);

    //owner->transform.position.x = swaws::math::wrap(owner->transform.position.x, 0.0f,
    //    (float)swaws::GetEngine().GetRenderer().GetWindowWidth());
    //owner->transform.position.y = swaws::math::wrap(owner->transform.position.y, 0.0f,
    //    (float)swaws::GetEngine().GetRenderer().GetWindowHeight());

    swaws::Transform transform(owner->transform.position, owner->transform.rotation, 1);

    if (fireTimer <= 0.0f &&
        (swaws::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_E) ||
         swaws::GetEngine().GetInput().GetMouseButtonPressed(swaws::InputSystem::MouseButton::Left)))
    {
        fireTimer = fireTime;
        switch (weapon)
        {
        case Weapon::Rocket:
        {
            auto rocket = swaws::Instantiate("rocket_player", transform);
            owner->scene->AddActor(std::move(rocket), true);
            swaws::GetEngine().GetAudio().PlaySound(*swaws::Resources().Get<swaws::AudioClip>("blaster.wav", swaws::GetEngine().GetAudio()));
            break;
        }
        case Weapon::Laser:
        {
            auto laser = swaws::Instantiate("laser", transform);
            owner->scene->AddActor(std::move(laser), true);
            swaws::GetEngine().GetAudio().PlaySound(*swaws::Resources().Get<swaws::AudioClip>("laser.mp3", swaws::GetEngine().GetAudio()));
            break;
        }
        default:
            break;
        }
    }

    fireTimer -= dt;
}

void Player::Start()
{
    rigidBody = owner->GetComponent<swaws::RigidBody>();
    fireTimer = fireTime;
}

void Player::OnCollision(swaws::Actor* other)
{
    if (owner->tag != other->tag)
    {
        EVENT_NOTIFY(player_dead);
        owner->destroyed = true;
        swaws::GetEngine().GetAudio().PlaySound(*swaws::Resources().Get<swaws::AudioClip>("explosion.wav", swaws::GetEngine().GetAudio()));
    }
}

/// <summary>
/// Sets the player's current weapon to the specified weapon if it is different from the current one.
/// </summary>
/// <param name="weapon">The weapon to select for the player.</param>
void Player::SelectWeapon(Weapon weapon)
{
    if (weapon != this->weapon)
    {
        this->weapon = weapon;
    }
}
