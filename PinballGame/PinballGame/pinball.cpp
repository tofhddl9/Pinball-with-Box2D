#include "pinball.h"

Pinball::Pinball()
{
    CreateWorld();
    CreateWall();
    //AddBall();
}

void Pinball::AddBall()
{
    //Ball_ptr ball = std::make_unique<Ball>(world_, b2Vec2(0, 10.0f), 1.0f);
    //balls_.emplace_back(ball);
}

void Pinball::Step()
{
    for (int step = 0; step < 120; ++step) {
        world_->Step(time_step_, velocity_iterations_, position_iterations_);
        for (auto&& ball : balls_) {
            b2Vec2 pos = ball->GetPosition();
            float ang = ball->GetAngle();
            printf("x : %f y : %f angle : %f\n", pos.x, pos.y, ang);
        }
    }
}

void Pinball::CreateWorld()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, -9.8f);
    world_ = std::make_unique<b2World>(gravity);
}

void Pinball::CreateWall()
{
    b2BodyDef body_def;
    wall_ = std::make_unique<b2Body, void(*)(b2Body *)>
        (world_->CreateBody(&body_def), [this](b2Body* p){world_->DestroyBody(p); });

    b2Vec2 wall_point[5];
    wall_point[0].Set(-8.0f, 0.0f);
    wall_point[1].Set(-8.0f, 20.0f);
    wall_point[2].Set(8.0f, 20.0f);
    wall_point[3].Set(8.0f, 0.0f);
    wall_point[4].Set(0.0f, -2.0f);

    b2ChainShape loop;
    loop.CreateLoop(wall_point, 5);

    b2FixtureDef fixture_def;
    fixture_def.shape = &loop;
    fixture_def.density = 0.0f;
    //wall_->CreateFixture(&fixture_def);
}