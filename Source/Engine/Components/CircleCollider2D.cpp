#include "CircleCollider2D.h"

namespace swaws
{
    FACTORY_REGISTER(CircleCollider2D)

    void CircleCollider2D::Update(float dt)
    {
        //
    }

    bool CircleCollider2D::CheckCollision(ColliderComponent& other)
    {
        float distance = (owner->transform.position - other.owner->transform.position).Length();
        
        // CIRCLE TO CIRCLE 
        // The fuq you mean nuh uh?
        auto circlecollider = dynamic_cast<CircleCollider2D*>(&other);
        if (circlecollider)
        {
            float radii = radius + circlecollider->radius;
            if (distance <= radii) return true;
        }

        // auto boxcollider = dynamic_cast<BoxCollider2D*>(other);
        return false;
    }
}