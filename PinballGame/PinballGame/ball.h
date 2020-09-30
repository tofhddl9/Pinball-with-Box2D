#ifndef __BALL_H__
#define __BALL_H__

#pragma once
#include <Box2D/Box2D.h>
using b2World_ptr = std::unique_ptr<b2World>;

class Ball {

public:
    Ball(b2World_ptr world, b2Vec2 pos, float radius);
    b2Vec2 GetPosition(); 
    b2Vec2 GetVelocity();
    float GetAngle();

private:
    //b2Body_ptr body_;
};

#endif