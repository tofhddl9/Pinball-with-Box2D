#pragma once
#include "circle.h"

using b2World_ptr = std::unique_ptr<b2World>;

class Ball : Circle{

public:
    Ball(b2World *world, const b2Vec2 pos,
        const float radius, const int ballType);
    virtual ~Ball();
    virtual void Render();

    body_ptr GetBody();

private:
    int ballType_;
};