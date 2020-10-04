#pragma once

#include <Box2D/Box2D.h>
#include "setting.h"
class ContactListener : public b2ContactListener
{
public:
    void BeginContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    void EndContact(b2Contact* contact);

private:
    bool IsContactWithBall(int contactInfo);
    int ContactObjectWithBall(int contactInfo);
};