#ifndef __PINBALL_H__
#define __PINBALL_H__

#pragma once
#include "Box2D/Box2D.h"
#include "ball.h"
#include <vector>

using b2World_ptr = std::unique_ptr<b2World>;

using b2Body_ptr = std::unique_ptr<b2Body, void(*)(b2Body *)>;

using Ball_ptr = std::unique_ptr<Ball>;

class Pinball 
{
public:
    Pinball() : wall_(nullptr, body_deletor) {};
    void AddBall();
    void Step();

private:
    b2World_ptr world_;
    b2Body_ptr wall_;

    //void(*body_deletor)(b2Body*) = [this](b2Body* p) {world_->DestroyBody(p); };

    std::vector<Ball_ptr> balls_;

    const float32 time_step_ = 1.0f / 60.0f;
    const int32 velocity_iterations_ = 6;
    const int32 position_iterations_ = 2;

    void CreateWorld();
    void CreateWall();
};

#endif