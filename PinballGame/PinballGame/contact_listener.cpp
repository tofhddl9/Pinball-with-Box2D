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
        case(WINDMILL):
            break;
        case(BUMPER):
            bodyB->ApplyLinearImpulse(BUMPER_ELASTICITY * wm.normal, bodyB->GetPosition(), true);
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
