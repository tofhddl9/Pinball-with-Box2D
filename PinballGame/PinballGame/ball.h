/*
#ifndef __BALL_H__
#define __BALL_H__

#pragma once
#include <Box2D/Box2D.h>
#include <functional>
using b2World_ptr = std::unique_ptr<b2World>;
using b2Body_ptr = std::unique_ptr<Ball, std::function<void(b2Body*)>>;

class Ball {

public:
    Ball(b2World_ptr world, b2Vec2 pos, float radius);
    b2Vec2 GetPosition(); 
    b2Vec2 GetVelocity();
    float GetAngle();

private:
    std::function<void(b2Body*)> body_deleter_ = [this](b2Body* p) {p->GetWorld()->DestroyBody(p); };

    std::function<void(Ball *)> ball_deleter_ =
        [this](Ball *b) {body_deleter_, delete b;};
    b2Body_ptr body_;
};

#endif
*/