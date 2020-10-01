#include "pinball.h"

Pinball::Pinball() : wall_(nullptr, body_deleter_)
{
    CreateWorld();
    CreateWall();
    AddBall(b2Vec2(0.0f, 10.0f), 1.0f);
}

void Pinball::AddBall(b2Vec2 pos, float radius)
{
    //Ball_ptr ball = std::unique_ptr<Ball, decltype(ball_deleter_)> (Ball(world_, b2Vec2(0, 10.0f), 1.0f), ball_deleter_);
    b2BodyDef body_def;
    body_def.position.Set(pos.x, pos.y);
    body_def.angle = 0;
    body_def.type = b2_dynamicBody;
    body_def.bullet = true;
    
    //body_ = std::make_unique<b2Body, decltype(body_deleter_)>(world->CreateBody(&body_def), body_deleter_);
    b2Body_ptr ball = std::unique_ptr<b2Body, decltype(body_deleter_)> (world_->CreateBody(&body_def), body_deleter_);

    b2CircleShape shape;
    shape.m_radius = radius;

    b2FixtureDef fixture_def;
    fixture_def.density = 1.0f;
    fixture_def.friction = 0.36f;
    fixture_def.restitution = 0.6f;
    fixture_def.shape = &shape;

    ball->CreateFixture(&fixture_def);

    balls_.emplace_back(std::move(ball));
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
    wall_ = std::unique_ptr<b2Body, decltype(body_deleter_)> (world_->CreateBody(&body_def), body_deleter_);

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
    wall_->CreateFixture(&fixture_def);
}