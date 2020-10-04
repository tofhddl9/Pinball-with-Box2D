#include "contact_listener.h"

void ContactListener::BeginContact(b2Contact* contact) {}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    b2Fixture* fa = contact->GetFixtureA();
    b2Fixture* fb = contact->GetFixtureB();

    b2Body* bodyA = fa->GetBody();
    b2Body* bodyB = fb->GetBody();

    int contactInfo = (int)bodyA->GetUserData() + (int)bodyB->GetUserData();
    if (IsContactWithBall(contactInfo)) {
        b2WorldManifold wm;
        contact->GetWorldManifold(&wm);
        int contactObjectWithBall = ContactObjectWithBall(contactInfo);

        // todo : give score
        switch (contactObjectWithBall) {
        case WINDMILL:
            break;
        case BUMPER: {
            b2Vec2 reflection = GetReflection(bodyB->GetLinearVelocity(), wm.normal);
            bodyB->ApplyLinearImpulse(BUMPER_ELASTICITY * reflection, bodyB->GetPosition(), true);
            break;
        }
        case REBOUNDER:
            b2Vec2 rebound = GetRebound(bodyB->GetLinearVelocity(), wm.normal);
            bodyB->ApplyLinearImpulse(REBOUNDER_ELASTICITY * rebound, bodyB->GetPosition(), true);
            break;
        }
    }
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}

void ContactListener::EndContact(b2Contact* contact) {}

bool ContactListener::IsContactWithBall(int contactInfo)
{
    return (contactInfo & BALL) > 0;
}

int ContactListener::ContactObjectWithBall(int contactInfo)
{
    return (contactInfo ^ BALL);
}

float32 ContactListener::InnerProduct(b2Vec2 va, b2Vec2 vb)
{
    return va.x * vb.x + va.y * vb.y;
}

b2Vec2 ContactListener::GetRebound(b2Vec2 velocity, b2Vec2 normal)
{
    b2Vec2 reflection = GetReflection(velocity, normal);
    float32 reflectionLength = reflection.Length();
    reflection.Normalize();

    b2Vec2 rebound = reflection + REBOUNDER_CORRECTION;
    return reflectionLength * rebound;
}

b2Vec2 ContactListener::GetReflection(b2Vec2 velocity, b2Vec2 normal)
{
    return velocity + 2 * InnerProduct(-velocity, normal) * normal;
}