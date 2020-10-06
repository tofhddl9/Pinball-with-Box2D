#pragma once
#include "circle.h"

class Bumper : Circle
{
public:
    Bumper(b2World *world, const b2Vec2 pos,
        const float radius, const int type);
    virtual void Render();
};