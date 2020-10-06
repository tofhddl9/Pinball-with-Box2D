#pragma once
#include "Box2D/Box2D.h"
#include "GL/glut.h"
#include "contact_listener.h"
#include "setting.h"
#include "ball.h"
#include "star.h"
#include "water.h"
#include "wall.h"
#include "piston.h"
#include "flipper.h"
#include "wanderer.h"
#include "bumper.h"
#include "rebounder.h"
#include "wormhole.h"

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
    int GetScore();

private:
    b2World_ptr world_;
    ContactListener contactListener_;

    Water* water_;
    std::vector<Wall *> walls_;
    std::vector<Ball *> balls_;
    std::vector<Star*> stars_;

    Piston *piston_;
    std::vector<Flipper* > left_flippers_, right_flippers_;
    
    std::vector<Flipper*> windmills_;
    std::vector<Wanderer*> wanderers_;
    std::vector<Bumper*> bumpers_;
    std::vector<Rebounder*> rebounders_;
    std::vector<Wormhole*> wormholes_;

    const float32 time_step_ = 1.0f / 30.0f;
    const int32 velocity_iterations_ = 20;
    const int32 position_iterations_ = 16;

    void CreateWorld();
    void CreateWall();
    void CreateWater();
    void CreateStars();
    void CreateStar(b2Vec2 pos, const float centerToVertex, const int type);

    void CreatePiston();
    void CreateFlippers();
    Flipper *CreateFlipper(b2Vec2 pivot_pos, const float head_angle,
        const bool is_left, const b2Vec2 LWH);
    void CreateObstacles();
    void CreateWindmill(const b2Vec2 pos, const b2Vec2 LWH);
    void CreateWanderer(const b2Vec2 head_pos, const b2Vec2 velocity,
        const b2Vec2 LWH, const b2Vec2 LR);
    void CreateBumper(const b2Vec2 pos, const float raius, const int type);
    void CreateRebounder(const b2Vec2 p1, const b2Vec2 p2, const b2Vec2 other);
    void CreateWormhole(const b2Vec2 src, const float radius);

    void RenderWall();
    void RenderWater();
    void RenderStar();
    void RenderPiston();
    void RenderFlipper();
    void RenderBall();
    void RenderObstacles();

    void AddBall(const b2Vec2 pos, const float radius);
    void MovingWanderer();
    void ProcessFlipperInput();
    void RemoveBallToBeDeleted();
};