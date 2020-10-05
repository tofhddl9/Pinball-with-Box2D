#include "wormhole.h"

Wormhole::Wormhole(b2World* world, const b2Vec2 src, const float radius)
{
    b2BodyDef bd;
    bd.position = src;
    bd.type = b2_staticBody;
    body_ = world->CreateBody(&bd);

    b2CircleShape shape;
    radius_ = radius;
    shape.m_radius = radius;
    body_->CreateFixture(&shape, 1.0f);

    int objectType = WORMHOLE;
    body_->SetUserData((void*)objectType);
}

void Wormhole::Render()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    RenderCircle();
}