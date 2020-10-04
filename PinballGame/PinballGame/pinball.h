#pragma once
#include "Box2D/Box2D.h"
#include "contact_listener.h"
#include "setting.h"
#include "ball.h"
#include "wall.h"
#include "piston.h"
#include "Flipper.h"
#include "bumper.h"
#include "rebounder.h"
#include <vector>

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
    ContactListener contactListener_;

    std::vector<Wall *> walls_;
    std::vector<Ball *> balls_;
    Piston *piston_;
    Flipper *leftFlipper_, *rightFlipper_;
    
    Flipper* windmill_;
    std::vector<Bumper*> bumpers_;
    std::vector<Rebounder*> rebounders_;

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
    void CreateBumper(const b2Vec2 pos, const float raius);
    void CreateRebounder(const b2Vec2 p1, const b2Vec2 p2, const b2Vec2 other);

    void RenderWall();
    void RenderPiston();
    void RenderFlipper();
    void RenderBall();
    void RenderObstacles();

    void AddBall(b2Vec2, float);
};