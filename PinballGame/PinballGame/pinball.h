#ifndef __PINBALL_H__
#define __PINBALL_H__

#pragma once
#include "Box2D/Box2D.h"
#include "ball.h"
#include "wall.h"
#include "piston.h"
#include <vector>
#include <functional>

using b2World_ptr = std::unique_ptr<b2World>;

//using b2Body_ptr = std::unique_ptr<b2Body, std::function<void(b2Body *)>>;
//using Ball_ptr = std::unique_ptr<Ball, std::function<void(Ball *)>>;

class Pinball 
{
public:
    Pinball();
    void AddBall();
    void PullPiston();
    void PushPiston(int time);
    void Step();
    void Render();

private:
    //std::function<void(b2Body *)> body_deleter_ = [this](b2Body* p) {world_->DestroyBody(p); };

    b2World_ptr world_;

    std::vector<Wall *> walls_;
    std::vector<Ball *> balls_;
    Piston *piston_;

    const float32 time_step_ = 1.0f / 30.0f;
    const int32 velocity_iterations_ = 6;
    const int32 position_iterations_ = 2;

    void CreateWorld();
    void CreateWall();
    void CreatePiston();

    void RenderWall();
    void RenderPiston();
    void RenderBall();

    void AddBall(b2Vec2, float);
};

#endif