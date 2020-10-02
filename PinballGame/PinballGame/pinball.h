#ifndef __PINBALL_H__
#define __PINBALL_H__

#pragma once
#include "Box2D/Box2D.h"
#include "ball.h"
#include <vector>
#include <functional>

using b2World_ptr = std::unique_ptr<b2World>;

using b2Body_ptr = std::unique_ptr<b2Body, std::function<void(b2Body *)>>;

//using Ball_ptr = std::unique_ptr<Ball, std::function<void(Ball *)>>;

class Pinball 
{
public:
    Pinball();
    b2World* GetWorld();
    b2Body* GetGround();
    void Step();
    void Render();

private:
    std::function<void(b2Body *)> body_deleter_ = [this](b2Body* p) {world_->DestroyBody(p); };

    b2World_ptr world_;

    //TODO : std::vector<Wall *> walls_;
    b2Body_ptr wall_;
    b2Vec2 wall_point[5];

    std::vector<Ball *> balls_;
    //std::vector<b2Body_ptr> balls_;

    const float32 time_step_ = 1.0f / 30.0f;
    const int32 velocity_iterations_ = 6;
    const int32 position_iterations_ = 2;

    void CreateWorld();
    void CreateWall();

    void RenderWall();
    void RenderBall();

    void AddBall(b2Vec2, float);
};

#endif