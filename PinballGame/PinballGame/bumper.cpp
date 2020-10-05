#include "bumper.h"

Bumper::Bumper(b2World *world, const b2Vec2 pos, const float radius)
{
    b2BodyDef bd;
    bd.position = pos;
    bd.type = b2_staticBody;
    body_ = world->CreateBody(&bd);

    b2CircleShape circle;
    radius_ = circle.m_radius = radius;
    body_->CreateFixture(&circle, 1.0f);

    int objectType = BUMPER;
    body_->SetUserData((void*)objectType);
}

void Bumper::Render()
{
    glColor3f(0.8f, 0.4f, 0.6f);
    RenderCircle();
}

