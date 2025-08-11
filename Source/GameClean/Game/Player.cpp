#pragma once
#include "Player.h"
#include "Rocket.h"
#include "Laser.h"
#include "GameData.h"
#include "SpaceGame.h"

void Player::Update(float dt)
{
    float angle = transform.rotation + swaws::random::getReal(-60.0f, 60.0f);
    swaws::vec2 pv = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(angle));
    pv *= swaws::random::getReal(80.0f, 150.0f);

    if (velocity.Normalized().x != 0)
    {
        float offsetDistance = -GetRadius() + 10;
        swaws::vec2 offset = swaws::vec2{ 1, 0 }.Rotate(swaws::math::DegToRad(transform.rotation)) * offsetDistance;

        swaws::Particle particle;
        particle.position = transform.position + offset;
        particle.velocity = pv * swaws::vec2{ swaws::random::getReal(-50.0f, 50.0f), swaws::random::getReal(-50.0f, 50.0f) };
        particle.color = swaws::vec3{ 1, 1, 1 };
        particle.lifespan = 0.5f;


        swaws::GetEngine().GetPS().AddParticle(particle);
    }

    // rotation
    float rotate = 0;
    if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

    transform.rotation += (rotate * rotationRate) * dt;

    // thrust
    float thrust = 0;
    if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
    if (swaws::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    swaws::vec2 direction{ 1, 0 };
    swaws::vec2 force = direction.Rotate(swaws::math::DegToRad(transform.rotation)) * thrust * speed;
    velocity += force * dt;

    transform.position.x = swaws::math::wrap((float)transform.position.x, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowWidth());
    transform.position.y = swaws::math::wrap((float)transform.position.y, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowHeight());

    swaws::res_t<swaws::Texture> texture;
    std::unique_ptr<Rocket> rocket;
    std::unique_ptr<Laser> laser;
    swaws::Transform transform(this->transform.position, this->transform.rotation, 5);
    
    // Check for Rocket Fire
    if ((swaws::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_E) || swaws::GetEngine().GetInput().GetMouseButtonPressed(swaws::InputSystem::MouseButton::Left)) && fireTimer <= 0)
    {
        fireTimer = fireTime;
        switch (weapon)
        {
        case Player::Weapon::Rocket:
            // Spawn rocket in direction facing
            texture = swaws::Resources().Get<swaws::Texture>("Placeholder.jpg", swaws::GetEngine().GetRenderer());
            rocket = std::make_unique<Rocket>(transform, texture);
            rocket->speed = 750; // Set Speed
            rocket->lifespan = 1.5f;
            rocket->tag = "player"; // Set Tag
            rocket->name = "rocket";

            scene->AddActor(std::move(rocket));
            swaws::GetEngine().GetAudio().playSound("blaster", 0, false, 0);
            break;
        case Player::Weapon::Laser:
            // Laser time BAYBEE
            texture = swaws::Resources().Get<swaws::Texture>("Placeholder.jpg", swaws::GetEngine().GetRenderer());
            laser = std::make_unique<Laser>(transform, texture);
            laser->lifespan = 2.0f;
            laser->tag = "player";
            laser->name = "laser";

            scene->AddActor(std::move(laser));
            swaws::GetEngine().GetAudio().playSound("laser", 0, false, 0);
            break;
        default:
            break;
        }
    }
    fireTimer--;
    Actor::Update(dt);
}

void Player::OnCollision(Actor* other)
{
    if (tag != other->tag)
    {
        destroyed = true;
        dynamic_cast<SpaceGame*>(scene->GetGame())->OnPlayerDeath();
        swaws::GetEngine().GetAudio().playSound("explosion", 0, false, 0);
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
