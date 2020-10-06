#pragma once
#include "circle.h"

class Wormhole : Circle
{
public:
    Wormhole(b2World* world, const b2Vec2 src, const float radius);
    virtual void Render();
};