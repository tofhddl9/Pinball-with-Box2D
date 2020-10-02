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
        //printf("x : %f y : %f angle : %f\n", pos.x, pos.y, ang);
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
    
    gluOrtho2D(-25.0f, 25.0f, -35.0f, 30.0f);

    RenderWall();

    RenderBall();

    glutSwapBuffers();
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

void Pinball::CreateWorld()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, -9.8f);
    world_ = std::make_unique<b2World>(gravity);
}

void Pinball::CreateWall()
{
    Wall* wall;
    b2Vec2* wall_point;

    //wall_1
    wall_point = new b2Vec2[58];
    {
        wall_point[0].Set(16.5f, -23.5f); //F1
        wall_point[1].Set(16.5f, -25.3f); //E1
        wall_point[2].Set(-15.5f, -25.0f);//D1
        wall_point[3].Set(-15.5f, -23.5f);//C1
        wall_point[4].Set(-2.0f, -23.5f);//B1
        wall_point[5].Set(-2.0f, -20.0f);//G3
        wall_point[6].Set(-15.0f, -14.0f);//H3
        wall_point[7].Set(-14.0f, -8.0f);//W
        wall_point[8].Set(-13.5f, -4.5f);//V
        wall_point[9].Set(-13.0f, -3.0f);//A4

        wall_point[10].Set(-12.5f, -1.5f);//U
        wall_point[11].Set(-12.6f, 0.4f);//T
        wall_point[12].Set(-13.6f, 2.6f);//S
        wall_point[13].Set(-14.8f, 6.0f);//R
        wall_point[14].Set(-14.6f, 11.0f);//Q
        wall_point[15].Set(-14.4f, 14.0f);//P
        wall_point[16].Set(-14.2f, 16.6f);//Z2
        wall_point[17].Set(-14.0f, 18.0f);//W2
        wall_point[18].Set(-13.6f, 19.0f);//V2
        wall_point[19].Set(-13.0f, 20.0f);//U2

        wall_point[20].Set(-11.8f, 21.2f);//E2
        wall_point[21].Set(-12.6f, 22.4f);//D2
        wall_point[22].Set(-12.6f, 24.0f);//C2
        wall_point[23].Set(-12.4f, 25.0f);//B2
        wall_point[24].Set(-11.8f, 25.6f);//A2
        wall_point[25].Set(-11.0f, 26.0f);//N
        wall_point[26].Set(-10.0f, 26.2f);//M
        wall_point[27].Set(-8.4f, 26.1f);//L
        wall_point[28].Set(-7.4f, 25.8f);//K
        wall_point[29].Set(-6.4f, 25.0f);//J

        wall_point[30].Set(-3.4f, 25.4f);//H
        wall_point[31].Set(-0.4f, 25.6f);//G
        wall_point[32].Set(3.4f, 25.2f);//F
        wall_point[33].Set(7.0f, 24.6f);//E
        wall_point[34].Set(9.2f, 24.0f);//D
        wall_point[35].Set(11.0f, 23.0f);//C
        wall_point[36].Set(12.2f, 21.8f);//S1
        wall_point[37].Set(13.4f, 20.4f);//Q1
        wall_point[38].Set(14.4f, 18.4f);//F2
        wall_point[39].Set(15.0f, 16.0f);//T1

        wall_point[40].Set(15.5f, 12.0f);//U1
        wall_point[41].Set(16.5f, 2.0f);//V1
        wall_point[42].Set(16.5f, -7.5f);//I2
        wall_point[43].Set(16.5f, -22.0f);//R1
        wall_point[44].Set(15.0f, -22.0f);//B
        wall_point[45].Set(15.0f, -7.4f);//J2
        wall_point[46].Set(15.0f, -2.0f);//K1
        wall_point[47].Set(15.0f, 2.0f);//K2
        wall_point[48].Set(14.0f, 12.0f);//L2
        wall_point[49].Set(13.4f, 15.4f);//M2

        wall_point[50].Set(13.0f, 17.4f);//N2
        wall_point[51].Set(11.8f, 19.6f);//O2
        wall_point[52].Set(10.6f, 21.0f);//P2
        wall_point[53].Set(9.4f, 22.0f);//Q2
        wall_point[54].Set(8.0f, 22.6f);//R2
        wall_point[55].Set(5.8f, 23.2f);//S2
        wall_point[56].Set(3.0f, 23.6f);//T2
        wall_point[57].Set(1.0f, 23.8f);//W1
    }
    wall = new Wall(world_.get(), LINE_CHAIN, wall_point, 58);
    walls_.push_back(wall);

    //wall_2
    wall_point = new b2Vec2[13];
    {
        wall_point[0].Set(15.0f, -23.6f);//S3
        wall_point[1].Set(2.0f, -23.5f);//G1
        wall_point[2].Set(2.0f, -20.0f);//D3
        wall_point[3].Set(15.0f, -14.0f);//C3
        wall_point[4].Set(15.0f, -13.0f);//I1
        wall_point[5].Set(14.0f, -8.0f);//J1
        wall_point[6].Set(13.5f, -4.5f);//L1
        wall_point[7].Set(13.0f, -3.0f);//M1
        wall_point[8].Set(12.5f, -1.5f);//N1
        wall_point[9].Set(12.6f, 0.4f);//O1

        wall_point[10].Set(13.4f, 2.2f);//P1
        wall_point[11].Set(14.0f, 4.0f);//Z
        wall_point[12].Set(14.6f, 6.0f);//Z3
    }
    wall = new Wall(world_.get(), LINE_CHAIN, wall_point, 13);
    walls_.push_back(wall);
}