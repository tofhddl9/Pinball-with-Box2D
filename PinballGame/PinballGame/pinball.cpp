#include "pinball.h"
#include "GL/glut.h"

Pinball::Pinball()// : wall_(nullptr, body_deleter_)
{
    CreateWorld();
    CreateWall();
    AddBall(b2Vec2(0.0f, 10.0f), 1.0f);
    AddBall(b2Vec2(2.0f, 9.0f), 0.5f);
}

void Pinball::AddBall(b2Vec2 pos, float radius)
{
    Ball* ball = new Ball(world_.get(), b2Vec2(pos.x, pos.y), radius);
    balls_.emplace_back(ball);
}

void Pinball::Step()
{
    world_->Step(time_step_, velocity_iterations_, position_iterations_);
    for (auto&& ball : balls_) {
        b2Vec2 pos = ball->GetPosition();
        float ang = ball->GetAngle();
        printf("x : %f y : %f angle : %f\n", pos.x, pos.y, ang);
    }
    
}

void Pinball::Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluOrtho2D(-25.0f, 25.0f, -20.0f, 40.0f);

    //RenderWall();
    RenderBall();

    glutSwapBuffers();
}

void Pinball::CreateWorld()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, -9.8f);
    world_ = std::make_unique<b2World>(gravity);
}

void Pinball::CreateWall()
{
    
}

void Pinball::RenderWall()
{
    for (auto wall : walls_) {
        wall->Render();
    }
    
}

void Pinball::RenderBall()
{
    for (auto ball : balls_) {
        ball->Render();
    }
}