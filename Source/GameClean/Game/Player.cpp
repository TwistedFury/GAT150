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
    //float angle = transform.rotation + swaws::random::getReal(-60.0f, 60.0f);
    //swaws::vec2 pv = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(angle));
    //pv *= swaws::random::getReal(80.0f, 150.0f);

    //auto rb = GetComponent<swaws::RigidBody>();
    //if (rb)
    //{
    //    if (rb->velocity.Normalized().x != 0)
    //    {
    //        float offsetDistance = -25;
    //        swaws::vec2 offset = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(transform.rotation)) * offsetDistance;

    //        swaws::Particle particle;
    //        particle.position = transform.position + offset;
    //        particle.velocity = pv * swaws::vec2{ swaws::random::getReal(-50.0f, 50.0f), swaws::random::getReal(-50.0f, 50.0f) };
    //        particle.color = swaws::vec3{ 1, 1, 1 };
    //        particle.lifespan = 0.5f;

    //        swaws::GetEngine().GetPS().AddParticle(particle);
    //    }
    //}

    //// rotation
    //float rotate = 0;
    //if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    //if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

    //transform.rotation += (rotate * rotationRate) * dt;

    //// thrust
    //float thrust = 0;
    //if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
    //if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    //swaws::vec2 direction{ 1, 0 };
    //swaws::vec2 force = direction.Rotate(swaws::math::DegToRad(transform.rotation)) * thrust * speed;
    //rb->velocity += force * dt;
    //// Max Speed Verification
    //if (rb)
    //{
    //    float velMag = rb->velocity.Length();
    //    if (velMag > maxSpeed) {
    //        rb->velocity = rb->velocity.Normalized() * maxSpeed;
    //    }
    //}

    //transform.position.x = swaws::math::wrap((float)transform.position.x, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowWidth());
    //transform.position.y = swaws::math::wrap((float)transform.position.y, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowHeight());

    //std::unique_ptr<Rocket> rocket;
    //std::unique_ptr<Laser> laser;
    //swaws::Transform transform(this->transform.position, this->transform.rotation, 1);
    //
    //// Check for Rocket Fire
    //if ((swaws::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_E) || swaws::GetEngine().GetInput().GetMouseButtonPressed(swaws::InputSystem::MouseButton::Left)) && fireTimer <= 0)
    //{
    //    fireTimer = fireTime;
    //    switch (weapon)
    //    {
    //    case Player::Weapon::Rocket:
    //    {
    //        // Spawn rocket in direction facing
    //        rocket = std::make_unique<Rocket>(transform);
    //        rocket->speed = 300; // Set Speed
    //        rocket->lifespan = 1.5f;
    //        rocket->tag = "player"; // Set Tag
    //        rocket->name = "rocket";

    //        auto sr = std::make_unique<swaws::SpriteRenderer>();
    //        sr->textureName = "spaceship-sprites/Projectiles/missile-1.png";

    //        auto rb = std::make_unique<swaws::RigidBody>();
    //        rb->damping = 0.0f; // Set Damping for rocket

    //        auto collider = std::make_unique<swaws::CircleCollider2D>();
    //        collider->radius = 20;

    //        rocket->AddComponent(std::move(sr));
    //        rocket->AddComponent(std::move(rb));
    //        rocket->AddComponent(std::move(collider));

    //        scene->AddActor(std::move(rocket));
    //        swaws::GetEngine().GetAudio().PlaySound(*swaws::Resources().Get<swaws::AudioClip>("blaster.wav", swaws::GetEngine().GetAudio()));
    //        break;
    //    }
    //    case Player::Weapon::Laser:
    //    {
    //        // Laser time BAYBEE
    //        laser = std::make_unique<Laser>(transform);
    //        laser->lifespan = 2.0f;
    //        laser->tag = "player";
    //        laser->name = "laser";

    //        auto sr = std::make_unique<swaws::SpriteRenderer>();
    //        sr->textureName = "spaceship-sprites/projectiles/projectile03-1.png";

    //        auto rb = std::make_unique<swaws::RigidBody>();
    //        rb->damping = 0.0f; // Set Damping for laser

    //        auto collider = std::make_unique<swaws::CircleCollider2D>();
    //        //collider->radius = swaws::GetEngine().GetRenderer().GetWindowWidth();
    //        collider->radius = 20;

    //        laser->AddComponent(std::move(sr));
    //        laser->AddComponent(std::move(rb));
    //        laser->AddComponent(std::move(collider));

    //        scene->AddActor(std::move(laser));
    //        swaws::GetEngine().GetAudio().PlaySound(*swaws::Resources().Get<swaws::AudioClip>("laser.mp3", swaws::GetEngine().GetAudio()));
    //        break;
    //    }
    //    default:
    //        break;
    //    }
    //}
    //fireTimer--;
    //Actor::Update(dt);
}

void Player::Start()
{
    rigidBody = owner->GetComponent<swaws::RigidBody>();
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
