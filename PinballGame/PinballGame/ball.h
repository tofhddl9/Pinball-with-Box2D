#pragma once
#include <Box2D/Box2D.h>
#include "setting.h"
using b2World_ptr = std::unique_ptr<b2World>;

class Ball {

public:
    Ball(b2World* world, const b2Vec2 pos, const float radius);
    b2Vec2 GetPosition(); 
    b2Vec2 GetVelocity();
    float GetAngle();
    float GetRadius();
    void Render();

private:
    b2Body *body_;
    float radius_;
};