#pragma once
#include "circle.h"

class Wormhole : Circle
{
public:
    Wormhole(b2World* world, const b2Vec2 src,
        const b2Vec2 dest, const float radius);
    virtual void Render();

private:
    b2Vec2 dest_;
};