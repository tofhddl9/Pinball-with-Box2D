#include "pinball.h"
#include "GL/glut.h"

Pinball::Pinball()
{
    CreateWorld();
    CreateWall();
    CreatePiston();
    CreateFlippers();
    CreateObstacles();

    AddBall();
}

void Pinball::AddBall()
{
    AddBall(b2Vec2(15.8f, -13.0f), 0.55f);
    //AddBall(b2Vec2(0.0f, 23.0f), 0.4f);
}

void Pinball::AddBall(b2Vec2 pos, float radius)
{
    Ball* ball = new Ball(world_.get(), b2Vec2(pos.x, pos.y), radius);
    balls_.emplace_back(ball);
}

void Pinball::RemoveBallToBeDeleted()
{
    auto it_start = balls_.begin();
    auto it_end = balls_.end();
    for (auto it = it_start; it != it_end; ++it) {
        b2Body* body = (*it)->GetBody();
        float32 radius = body->GetFixtureList()->GetShape()->m_radius;
        if ((int)body->GetUserData() == REMOVABLE_BALL) {
            balls_.erase(it);
            delete (*it);
            AddBall(WORMHOLE_DESTINATION , std::max(0.4f, radius * 0.8f));
        }
    }
}

int Pinball::GetScore()
{
    return contactListener_.GetScore();
}

void Pinball::Step()
{
    world_->Step(time_step_, velocity_iterations_, position_iterations_);

    RemoveBallToBeDeleted();

    leftFlipper_->IsKeyDown() ? FlipLeft() : UnflipLeft();
    rightFlipper_->IsKeyDown() ? FlipRight() : UnflipRight();
}

void Pinball::Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluOrtho2D(-26.0f, 25.0f, -35.0f, 30.0f);

    RenderWall();
    RenderPiston();
    RenderFlipper();
    RenderBall();
    RenderObstacles();

    glutSwapBuffers();
}

void Pinball::RenderWall()
{
    for (auto wall : walls_)
        wall->Render();
}

void Pinball::RenderPiston()
{
    piston_->Render();
}

void Pinball::RenderFlipper()
{
    leftFlipper_->Render();
    rightFlipper_->Render();
}

void Pinball::RenderBall()
{
    for (auto ball : balls_)
        ball->Render();
}

void Pinball::RenderObstacles()
{
    for (auto windmill : windmills_)
        windmill->Render();

    for (auto bumper : bumpers_)
        bumper->Render();

    for (auto rebounder : rebounders_)
        rebounder->Render();

    for (auto wormhole : wormholes_)
        wormhole->Render();

}

void Pinball::CreateWorld()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, -9.8f);
    world_ = std::make_unique<b2World>(gravity);

    world_->SetContactListener(&contactListener_);
}

void Pinball::CreateWall()
{
    Wall* wall;
    b2Vec2* wall_point;

    //wall_1
    wall_point = new b2Vec2[63];
    {
        wall_point[0].Set(16.5f, -23.5f); //F1
        wall_point[1].Set(16.5f, -26.5f); //E1
        wall_point[2].Set(-15.5f, -26.0f);//D1
        wall_point[3].Set(-15.5f, -23.5f);//C1
        wall_point[4].Set(-2.0f, -23.5f);//B1
        wall_point[5].Set(-2.0f, -20.3f);//G3
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
        wall_point[21].Set(-12.55f, 22.4f);//D2
        wall_point[22].Set(-12.6f, 24.0f);//C2
        wall_point[23].Set(-12.2f, 25.0f);//B2
        wall_point[24].Set(-11.7f, 25.5f);//A2
        wall_point[25].Set(-11.0f, 25.9f);//N
        wall_point[26].Set(-9.9f, 26.15f);//M
        wall_point[27].Set(-8.5f, 26.0);//L
        wall_point[28].Set(-7.4f, 25.5f);//K
        wall_point[29].Set(-6.7f, 24.8f);//J

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
        wall_point[58].Set(2.8f, 22.2f);//C4
        wall_point[59].Set(5.0f, 21.9f);//D4

        wall_point[60].Set(7.0f, 21.4f);//E4
        wall_point[61].Set(8.6f, 20.5f);//F4
        wall_point[62].Set(9.8f, 19.4f);//G4

    }
    wall = new Wall(world_.get(), LINE_CHAIN, wall_point, 63);
    walls_.push_back(wall);

    //wall_2
    wall_point = new b2Vec2[13];
    {
        wall_point[0].Set(15.0f, -23.6f);//S3
        wall_point[1].Set(2.0f, -23.5f);//G1
        wall_point[2].Set(2.0f, -20.3f);//D3
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

    //wall_3
    wall_point = new b2Vec2[3];
    {
        wall_point[0].Set(-5.0f, -17.0f);//A1
        wall_point[1].Set(-13.0f, -13.0f);//F3
        wall_point[2].Set(-12.0f, -8.0f);//E3
    }
    wall = new Wall(world_.get(), LINE_CHAIN, wall_point, 3);
    walls_.push_back(wall);

    //wall_4
    wall_point = new b2Vec2[3];
    {
        wall_point[0].Set(5.0f, -17.0f);//H1
        wall_point[1].Set(13.0f, -13.0f);//B3
        wall_point[2].Set(12.0f, -8.0f);//A
    }
    wall = new Wall(world_.get(), LINE_CHAIN, wall_point, 3);
    walls_.push_back(wall);

    //wall_5
    wall_point = new b2Vec2[3];
    {
        wall_point[0].Set(-6.0f, 23.65f);//O
        wall_point[1].Set(-4.6f, 24.0f);//I
        wall_point[2].Set(-2.6f, 24.2f);//Z1
    }
    wall = new Wall(world_.get(), LINE_CHAIN, wall_point, 3);
    walls_.push_back(wall);

    //wall_6
    wall_point = new b2Vec2[2];
    {
        wall_point[0].Set(-2.0f, 4.0f);//H2
        wall_point[1].Set(-1.5f, 12.0f);//G2
    }
    wall = new Wall(world_.get(), LINE_CHAIN, wall_point, 2);
    walls_.push_back(wall);

    //wall_7
    wall_point = new b2Vec2[2];
    {
        wall_point[0].Set(0.0f, 4.0f);//P3
        wall_point[1].Set(0.5f, 12.0f);//Q3
    }
    wall = new Wall(world_.get(), LINE_CHAIN, wall_point, 2);
    walls_.push_back(wall);

    //wall_8
    wall_point = new b2Vec2[2];
    {
        wall_point[0].Set(16.1f, -16.0f);//I4
        wall_point[1].Set(16.5f, -16.0f);//K4
    }
    wall = new Wall(world_.get(), LINE_CHAIN, wall_point, 2);
    walls_.push_back(wall);

    //wall_9
    wall_point = new b2Vec2[2];
    {
        wall_point[0].Set(15.0f, -16.0f);//J4
        wall_point[1].Set(15.4f, -16.0f);//H4
    }
    wall = new Wall(world_.get(), LINE_CHAIN, wall_point, 2);
    walls_.push_back(wall);

    //wall_10
    wall_point = new b2Vec2[3];
    {
        wall_point[0].Set(-9.9f, -8.2f);//K3
        wall_point[1].Set(-10.9f, -12.0f);//L3
        wall_point[2].Set(-8.1f, -13.6f);//M3
    }
    wall = new Wall(world_.get(), LINE_CHAIN, wall_point, 3);
    walls_.push_back(wall);

    //wall_11
    wall_point = new b2Vec2[3];
    {
        wall_point[0].Set(9.9f, -8.2f);//N3
        wall_point[1].Set(10.9f, -12.0f);//O3
        wall_point[2].Set(8.1f, -13.6f);//P3
    }
    wall = new Wall(world_.get(), LINE_CHAIN, wall_point, 3);
    walls_.push_back(wall);

    //wall_12
    wall_point = new b2Vec2[6];
    {
        wall_point[0].Set(-13.3f, 14.0f);//D5
        wall_point[1].Set(-13.1f, 16.4f);//E5
        wall_point[2].Set(-13.0f, 18.0f);//F5
        wall_point[3].Set(-12.45f, 19.0f);//G5
        wall_point[4].Set(-11.8f, 19.9f);//M4
        wall_point[5].Set(-10.9f, 20.7f);//O4
    }
    wall = new Wall(world_.get(), LINE_CHAIN, wall_point, 6);
    walls_.push_back(wall);

    //nail_1
    wall_point = new b2Vec2[3];
    {
        wall_point[0].Set(-2.55f, 22.5f);//B4
        wall_point[1].Set(-2.7f, 22.0f);//L4
        wall_point[2].Set(-2.4f, 22.0f);//N4
    }
    wall = new Wall(world_.get(), LINE_LOOP, wall_point, 3);
    walls_.push_back(wall);

    //nail_2
    wall_point = new b2Vec2[3];
    {
        wall_point[0].Set(-1.0f, 22.5f);//P4
        wall_point[1].Set(-1.15f, 22.0f);//Q4
        wall_point[2].Set(-0.85f, 22.0f);//R4
    }
    wall = new Wall(world_.get(), LINE_LOOP, wall_point, 3);
    walls_.push_back(wall);

    //nail_3
    wall_point = new b2Vec2[3];
    {
        wall_point[0].Set(0.65f, 22.5f);//A5
        wall_point[1].Set(0.5f, 22.0f);//B5
        wall_point[2].Set(0.8f, 22.0f);//C5
    }
    wall = new Wall(world_.get(), LINE_LOOP, wall_point, 3);
    walls_.push_back(wall);

}

void Pinball::CreatePiston()
{
    piston_ = new Piston(world_.get(), b2Vec2(15.0f, -23.0f),
        b2Vec2(15.75f, -20.0f), 0.6f);
}

void Pinball::CreateFlippers()
{
    leftFlipper_ = CreateFlipper(b2Vec2(-5.0f, -17.1f), b2Vec2(-5.0f, -17.1f), -25.0f * b2_pi / 180.0f, true); //left
    rightFlipper_ = CreateFlipper(b2Vec2(5.0f, -17.1f), b2Vec2(5.0f, -17.1f), 25.0f * b2_pi / 180.0f, false); //right
}

Flipper* Pinball::CreateFlipper(const b2Vec2 pivot_pos, const b2Vec2 head_pos, const float head_angle, bool is_left)
{
    return new Flipper(world_.get(), pivot_pos, head_pos, head_angle, is_left);
}

void Pinball::CreateObstacles()
{
    CreateWindmill(b2Vec2(6.0f, 15.0f), b2Vec2(1.0f, 0.1f));

    CreateBumper(b2Vec2(-2.0f, 20.0f), 0.7f, BUMPER_SMALL);
    CreateBumper(b2Vec2(0.5f, 20.5f), 0.7f, BUMPER_SMALL);
    CreateBumper(b2Vec2(-1.0f, 18.0f), 0.7f, BUMPER_SMALL);
    CreateBumper(b2Vec2(-9.2f, 23.0f), 2.0f, BUMPER_LARGE);

    CreateRebounder(b2Vec2(-10.0f, -8.0f), b2Vec2(-8.0f, -13.7f), b2Vec2(-11.0f, -12.0f));
    CreateRebounder(b2Vec2(10.0f, -8.0f), b2Vec2(8.0f, -13.7f), b2Vec2(11.0f, -12.0f));

    CreateWormhole(b2Vec2(3.0f, 23.0f), 0.4f);
}

void Pinball::CreateWindmill(const b2Vec2 pos, const b2Vec2 LWH)
{
    windmills_.push_back(new Flipper(world_.get(), pos, LWH));
}

void Pinball::CreateBumper(const b2Vec2 pos, const float radius, const int type)
{
    bumpers_.push_back(new Bumper(world_.get(), pos, radius, type));
}

void Pinball::CreateRebounder(const b2Vec2 p1, const b2Vec2 p2, const b2Vec2 other)
{
    rebounders_.push_back(new Rebounder(world_.get(), p1, p2, other));
}

void Pinball::CreateWormhole(const b2Vec2 src, const float radius)
{
    wormholes_.push_back(new Wormhole(world_.get(), src, radius));
}

void Pinball::PullPiston()
{
    piston_->Pull();
}

void Pinball::PushPiston(int power)
{
    piston_->Push(power);
}

void Pinball::FlipLeft()
{
    leftFlipper_->SetIsKeyDown(true);
    leftFlipper_->Flip();
}

void Pinball::UnflipLeft()
{
    leftFlipper_->SetIsKeyDown(false);
    leftFlipper_->Unflip();
}

void Pinball::FlipRight()
{
    rightFlipper_->SetIsKeyDown(true);
    rightFlipper_->Flip();
}

void Pinball::UnflipRight()
{
    rightFlipper_->SetIsKeyDown(false);
    rightFlipper_->Unflip();
}