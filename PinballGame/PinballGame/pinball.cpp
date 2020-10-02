#include "pinball.h"
#include "GL/glut.h"

Pinball::Pinball() : wall_(nullptr, body_deleter_)
{
    CreateWorld();
    CreateWall();
    AddBall(b2Vec2(0.0f, 10.0f), 1.0f);
    AddBall(b2Vec2(2.0f, 9.0f), 0.5f);
}

b2World* Pinball::GetWorld()
{
    return world_.get();
}

b2Body* Pinball::GetGround()
{
    return wall_.get();
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
    
    gluOrtho2D(-25.0f, 25.0f, -10.0f, 30.0f);

    RenderWall();
    //RenderObstacle();
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
    b2BodyDef body_def;
    wall_ = std::unique_ptr<b2Body, decltype(body_deleter_)> (world_->CreateBody(&body_def), body_deleter_);

    //b2Vec2 wall_point[5];
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

void Pinball::RenderWall()
{
    glPushMatrix();
    glColor3f(0.9f, 0.2f, 0.4f);
    glBegin(GL_LINE_LOOP);
    {
        for (int i = 0; i < 5; ++i) {
            printf("%f %f\n", wall_point[i].x, wall_point[i].y);
            glVertex2f(wall_point[i].x, wall_point[i].y);
        }
    }
    glEnd();
    glutSwapBuffers();
}

void Pinball::RenderBall()
{
    for (auto ball : balls_) {
        b2Vec2 position = ball->GetPosition();
        float angle = ball->GetAngle();
        float radius = ball->GetRadius();

        glPushMatrix();
        glTranslatef(position.x, position.y, 0.0f);
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        glColor3f(0.9f, 0.2f, 0.4f);

        float theta;
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
            theta = 3.142 * i / 180;
            glVertex2f(radius * cos(theta), radius * sin(theta));
        }
        glEnd();
        glPopMatrix();
    }
    // get position and angle by body(box)
    
}