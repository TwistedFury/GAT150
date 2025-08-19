#include "Rocket.h"
#include "Enemy.h"
#include "Player.h"

FACTORY_REGISTER(Rocket)

void Rocket::Update(float dt)
{
    //swaws::vec2 direction{ 1, 0 };
    //swaws::vec2 force = direction.Rotate(swaws::math::DegToRad(transform.rotation)) * speed;

    //auto rb = GetComponent<swaws::RigidBody>();
    //if (rb) {
    //    rb->velocity = force;
    //}

    //transform.position.x = swaws::math::wrap((float)transform.position.x, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowWidth());
    //transform.position.y = swaws::math::wrap((float)transform.position.y, (float)0, (float)swaws::GetEngine().GetRenderer().GetWindowHeight());

    //swaws::Particle particle;
    //particle.position = transform.position;
    //particle.velocity = swaws::vec2{ swaws::random::getReal(-50.0f, 50.0f), swaws::random::getReal(-50.0f, 50.0f) };
    //particle.color = swaws::vec3{ 1, 1, 1 };
    //particle.lifespan = 0.25f;

    //swaws::GetEngine().GetPS().AddParticle(particle);

    //Actor::Update(dt);
}

void Rocket::OnCollision(Actor* other)
{
    //if (other->tag != tag)
    //{
    //    destroyed = true;
    //}
}

