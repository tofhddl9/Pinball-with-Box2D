#ifndef __PINBALL_H__
#define __PINBALL_H__

#pragma once
#include "Box2D/Box2D.h"
#include "ball.h"
#include "wall.h"
#include "piston.h"
#include "Flipper.h"
#include <vector>
#include <functional>

using b2World_ptr = std::unique_ptr<b2World>;

class Pinball 
{
public:
    Pinball();
    void AddBall();
    void PullPiston();
    void PushPiston(int time);
   
    void FlipLeft();
    void UnflipLeft();
    void FlipRight();
    void UnflipRight();

    void Step();
    void Render();

private:
    b2World_ptr world_;

    std::vector<Wall *> walls_;
    std::vector<Ball *> balls_;
    Piston *piston_;
    Flipper *leftFlipper_, *rightFlipper_;
    Flipper* windmill_;

    const float32 time_step_ = 1.0f / 30.0f;
    const int32 velocity_iterations_ = 6;
    const int32 position_iterations_ = 2;

    void CreateWorld();
    void CreateWall();
    void CreatePiston();
    void CreateFlippers();
    Flipper *CreateFlipper(b2Vec2 pivot_pos, b2Vec2 head_pos, const float head_angle, bool is_left);
    void CreateObstacles();
    void CreateWindmill(const b2Vec2 pos, const b2Vec2 LWH);

    void RenderWall();
    void RenderPiston();
    void RenderFlipper();
    void RenderBall();

    void AddBall(b2Vec2, float);
};

#endif