#pragma once

#include <Box2D/Box2D.h>
#include <vector>
#include <set>
#include "setting.h"
#include "sound_manager.h"

typedef std::pair<b2Fixture*, b2Fixture*> fixturePair;

class ContactListener : public b2ContactListener
{
public:
    ContactListener();
    ContactListener(SoundManager *soundManager);
    void BeginContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    void EndContact(b2Contact* contact);
    int GetScore();

private:
    int score_;
    SoundManager *soundManager_;

    bool IsContactWithBall(int contactInfo);
    int ContactObjectWithBall(int contactInfo);

    float32 InnerProduct(b2Vec2 va, b2Vec2 vb);
    b2Vec2 GetRebound(b2Vec2 velocity, b2Vec2 normal);
    b2Vec2 GetReflection(b2Vec2 velocity, b2Vec2 normal);
    void Scoring(int objectType);
};