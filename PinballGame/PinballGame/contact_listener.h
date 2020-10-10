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

    ContactListener(SoundManager *soundManager);
    ~ContactListener();
    void BeginContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    void EndContact(b2Contact* contact);

    int GetScore();
    void FloatBall();
    
private:
    int score_;
    SoundManager *soundManager_;
    std::set<std::pair<b2Fixture*, b2Fixture *>> waterAndBall;

    bool IsContactWithBall(int contactInfo);
    int ContactObjectWithBall(int contactInfo);

    float32 InnerProduct(b2Vec2 va, b2Vec2 vb);
    b2Vec2 GetRebound(b2Vec2 velocity, b2Vec2 normal);
    b2Vec2 GetReflection(b2Vec2 velocity, b2Vec2 normal);
    
    void Scoring(int objectType);

    bool IsInside(const b2Vec2 cp1, const b2Vec2 cp2, const b2Vec2 p);
    b2Vec2 GetIntersection(const b2Vec2 cp1, const b2Vec2 cp2,
        const b2Vec2 s, const b2Vec2 e);
    b2Vec2 ComputeCentroid(std::vector<b2Vec2> vs, float& area);
    bool FindIntersectionOfWaterAndBall(b2Fixture* water, b2Fixture* ball,
        std::vector<b2Vec2>& vertices);
    void ApplyBuoyancy(b2Fixture* water, b2Fixture* ball,
        const float area, const b2Vec2 graivty, const b2Vec2 centroid);
};