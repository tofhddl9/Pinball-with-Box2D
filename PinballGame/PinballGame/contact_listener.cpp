#include "contact_listener.h"


void ContactListener::BeginContact(b2Contact* contact) {}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    b2Fixture* fa = contact->GetFixtureA();
    b2Fixture* fb = contact->GetFixtureB();

    b2Body* ba = fa->GetBody();
    b2Body* bb = fb->GetBody();

    if ((int)ba->GetUserData() == 4 && (int)bb->GetUserData() == 1) {
        bb->ApplyLinearImpulse(b2Vec2(100.f, 0.0f), bb->GetPosition(), true);
    }
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}

void ContactListener::EndContact(b2Contact* contact) {}