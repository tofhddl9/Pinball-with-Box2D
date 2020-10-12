#pragma once
#include "Box2D/Box2D.h"
#include "GL/glut.h"
#include "setting.h"

class Wanderer
{
public:
    Wanderer(b2World* world, const b2Vec2 velocity,
        const b2Vec2 head_pos, const b2Vec2 LWH, const b2Vec2 LR);
    void Render();
    void Wander();

private:
    bool IsInsideOfMap();

    body_ptr head_;
    b2Vec2 LWH_, LR_;
};