#include "ball.h"

Ball::Ball(float x, float y, float radius) {
    body = nullptr;

    bodyDef.position.Set(x, y);
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;

    shape.m_radius = radius;

    fixture.shape = &shape;
    fixture.density = 1.0f;
}

void Ball::CreateBall(b2World* world) {
    body = world->CreateBody(&bodyDef);
    body->CreateFixture(&fixture);
}

b2Vec2 Ball::GetPosition()
{
    return bodyDef.position;
}
