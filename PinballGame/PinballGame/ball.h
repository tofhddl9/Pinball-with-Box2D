#ifndef __BALL_H__
#define __BALL_H__

#include <Box2D/Box2D.h>
#pragma once

class Ball {
public:
    Ball(float x, float y, float radius);
    void CreateBall(b2World *world);
    b2Vec2 GetPosition(); 

private:
    b2Body* body;
    b2BodyDef bodyDef;
    b2CircleShape shape;
    b2FixtureDef fixture;
};

#endif