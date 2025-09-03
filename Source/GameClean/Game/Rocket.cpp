#include "../GamePCH.h"
#include "Rocket.h"
#include "Enemy.h"
#include "Player.h"

#include "Core/Json.h"

FACTORY_REGISTER(Rocket)

void Rocket::Update(float dt)
{
    auto rb = owner->GetComponent<swaws::RigidBody>();
    if (rb)
    {
        swaws::vec2 direction{ 1, 0 };
        swaws::vec2 force = direction.Rotate(rb->GetBody()->GetAngle()) * owner->speed;

        rb->GetBody()->SetVelocity(force);

        swaws::Particle particle;
        particle.position = owner->transform.position;
        particle.velocity = swaws::vec2{ swaws::random::getReal(-50.0f, 50.0f), swaws::random::getReal(-50.0f, 50.0f) };
        particle.color = swaws::vec3{ 1, 1, 1 };
        particle.lifespan = 0.25f;

        swaws::GetEngine().GetPS().AddParticle(particle);
    }
}

void Rocket::OnCollision(swaws::Actor* other)
{
    if (other->tag != owner->tag)
    {
        owner->destroyed = true;
    }
}

