#include "Physics.h"

namespace swaws {
	float Physics::ms_ppu = 48.0f;

	bool Physics::Initialize() {
		b2WorldDef worldDef = b2DefaultWorldDef();
		worldDef.gravity = b2Vec2{ 0.0f, 10.0f };
		m_worldId = b2CreateWorld(&worldDef);

		return true;
	}

	void Physics::Shutdown() {
		b2DestroyWorld(m_worldId);
	}

	void Physics::Update(float dt) {
		b2World_Step(m_worldId, 1.0f / 60.0f, 4);
		ProcessCollisionEvents();
	}

	void Physics::ProcessCollisionEvents()
	{
		b2ContactEvents contactEvents = b2World_GetContactEvents(m_worldId);

		auto validShape = [](b2ShapeId id){ return b2Shape_IsValid(id); };

		// Start Contacts
		for (int i = 0; i < contactEvents.beginCount; ++i)
		{
			b2ContactBeginTouchEvent* e = contactEvents.beginEvents + i;
			if (!validShape(e->shapeIdA) || !validShape(e->shapeIdB)) continue;

			b2BodyId bodyA = b2Shape_GetBody(e->shapeIdA);
			b2BodyId bodyB = b2Shape_GetBody(e->shapeIdB);
			Actor* actorA = static_cast<Actor*>(b2Body_GetUserData(bodyA));
			Actor* actorB = static_cast<Actor*>(b2Body_GetUserData(bodyB));
			if (!actorA || actorA->destroyed || !actorA->isActive) continue;
			if (!actorB || actorB->destroyed || !actorB->isActive) continue;
			actorA->OnCollision(actorB);
			actorB->OnCollision(actorA);
		}

		// End Contacts (add validity guards)
		for (int i = 0; i < contactEvents.endCount; ++i)
		{
			b2ContactEndTouchEvent* e = contactEvents.endEvents + i;
			if (!validShape(e->shapeIdA) || !validShape(e->shapeIdB)) continue;

			b2BodyId bodyA = b2Shape_GetBody(e->shapeIdA);
			b2BodyId bodyB = b2Shape_GetBody(e->shapeIdB);
			Actor* actorA = static_cast<Actor*>(b2Body_GetUserData(bodyA));
			Actor* actorB = static_cast<Actor*>(b2Body_GetUserData(bodyB));
			if (!actorA || actorA->destroyed || !actorA->isActive) continue;
			if (!actorB || actorB->destroyed || !actorB->isActive) continue;
			actorA->OnCollision(actorB);
			actorB->OnCollision(actorA);
		}

		// Sensors (add validity guards)
		b2SensorEvents sensorEvents = b2World_GetSensorEvents(m_worldId);
		for (int i = 0; i < sensorEvents.beginCount; ++i)
		{
			b2SensorBeginTouchEvent* e = sensorEvents.beginEvents + i;
			if (!validShape(e->sensorShapeId) || !validShape(e->visitorShapeId)) continue;

			b2BodyId bodyA = b2Shape_GetBody(e->sensorShapeId);
			b2BodyId bodyB = b2Shape_GetBody(e->visitorShapeId);
			Actor* actorA = static_cast<Actor*>(b2Body_GetUserData(bodyA));
			Actor* actorB = static_cast<Actor*>(b2Body_GetUserData(bodyB));
			if (!actorA || actorA->destroyed || !actorA->isActive) continue;
			if (!actorB || actorB->destroyed || !actorB->isActive) continue;
			actorA->OnCollision(actorB);
			actorB->OnCollision(actorA);
		}
	}
}