#include "contact_listener.h"

void ContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* fa = contact->GetFixtureA();
    b2Fixture* fb = contact->GetFixtureB();

    b2Body* bodyA = fa->GetBody();
    b2Body* bodyB = fb->GetBody();

    int contactInfo = (int)bodyA->GetUserData() + (int)bodyB->GetUserData();

    // make bodyB Ball
    if ((int)bodyA->GetUserData() == BALL) {
        std::swap(bodyA, bodyB);
        std::swap(fa, fb);
    }

    printf("Contact Begin : %d %d\n", (int)bodyA->GetUserData(), (int)bodyB->GetUserData());

    if (IsContactWithBall(contactInfo)) {
        b2WorldManifold wm;
        contact->GetWorldManifold(&wm);
        int contactObjectWithBall = ContactObjectWithBall(contactInfo);

        switch (contactObjectWithBall) {
        case WATER: {
            break;
        }

        }
    }
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    b2Fixture* fa = contact->GetFixtureA();
    b2Fixture* fb = contact->GetFixtureB();

    b2Body* bodyA = fa->GetBody();
    b2Body* bodyB = fb->GetBody();

    int contactInfo = (int)bodyA->GetUserData() + (int)bodyB->GetUserData();

    // make bodyB Ball
    if ((int)bodyA->GetUserData() == BALL) {
        std::swap(bodyA, bodyB);
    }

    if (IsContactWithBall(contactInfo)) {
        b2WorldManifold wm;
        contact->GetWorldManifold(&wm);
        int contactObjectWithBall = ContactObjectWithBall(contactInfo);

        switch (contactObjectWithBall) {
        case WINDMILL:
            break;
        case BUMPER_SMALL: {}
        case BUMPER_LARGE: {
            b2Vec2 reflection = GetReflection(bodyB->GetLinearVelocity(), wm.normal);
            bodyB->ApplyLinearImpulse(BUMPER_ELASTICITY * reflection, bodyB->GetPosition(), true);
            break;
        }
        case REBOUNDER: {
            b2Vec2 rebound = GetRebound(bodyB->GetLinearVelocity(), wm.normal);
            bodyB->ApplyLinearImpulse(REBOUNDER_ELASTICITY * rebound, bodyB->GetPosition(), true);
            break;
        }
        case WORMHOLE: {
            break;
        }

        }
    }
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}

void ContactListener::EndContact(b2Contact* contact)
{
    b2Fixture* fa = contact->GetFixtureA();
    b2Fixture* fb = contact->GetFixtureB();

    b2Body* bodyA = fa->GetBody();
    b2Body* bodyB = fb->GetBody();

    int contactInfo = (int)bodyA->GetUserData() + (int)bodyB->GetUserData();

    // make bodyB Ball
    if ((int)bodyA->GetUserData() == BALL) {
        std::swap(bodyA, bodyB);
    }

    printf("Contact End : %d %d\n", (int)bodyA->GetUserData(), (int)bodyB->GetUserData());

    if (IsContactWithBall(contactInfo)) {
        b2WorldManifold wm;
        contact->GetWorldManifold(&wm);
        int contactObjectWithBall = ContactObjectWithBall(contactInfo);
        if (contactObjectWithBall < WINDMILL) return;

        Scoring(contactObjectWithBall);
        switch (contactObjectWithBall) {
        case WINDMILL: {
            break;
        }
        case BUMPER_SMALL or BUMPER_LARGE: {
            break;
        }
        case REBOUNDER: {
            break;
        }
        case WORMHOLE: {
            bodyB->SetUserData((void*)REMOVABLE_BALL);
            break;
        }
        case WATER: {
            break;
        }

        }
    }
}

int ContactListener::GetScore()
{
    return score_;
}

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

void ContactListener::Scoring(int objectType)
{
    switch (objectType) {
    case WINDMILL: {
        score_ += SCORE_WINDMILL;
        break;
    }
    case BUMPER_SMALL: {
        score_ += SCORE_BUMPER_SMALL;
        break;
    }
    case BUMPER_LARGE: {
        score_ += SCORE_BUMPER_LARGE;
        break;
    }
    case REBOUNDER: {
        score_ += SCORE_REBOUNDER;
        break;
    }
    case WORMHOLE: {
        score_ += SCORE_WORMHOLE;
        break;
    }
    case STAR_SMALL: {
        score_ += SCORE_STAR_SMALL;
        break;
    }
    case STAR_LARGE: {
        score_ += SCORE_STAR_LARGE;
        break;
    }
    }
}