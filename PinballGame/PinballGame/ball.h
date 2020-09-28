#ifndef __BALL_H__
#define __BALL_H__

#include <Box2D/Box2D.h>
#pragma once

class Ball{
public:
    Ball(b2World* world, b2Vec2 pos, float radius);
    b2Vec2 GetPosition(); 
    b2Vec2 GetVelocity();
    float GetAngle();

private:
    b2Body* body;
};

#endif