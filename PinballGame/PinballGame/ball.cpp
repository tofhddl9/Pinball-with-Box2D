#include "ball.h"

Ball::Ball(b2World* world, b2Vec2 pos, float radius) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x, pos.y);
    bodyDef.angle = 0;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;
    
    body = world->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = radius;

    b2FixtureDef fixtureDef;
    fixtureDef.friction = 0.36f;
    fixtureDef.restitution = 0.6f;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;

    body->CreateFixture(&fixtureDef);
}

b2Vec2 Ball::GetPosition()
{
    return body->GetPosition();
}

b2Vec2 Ball::GetVelocity()
{
    return body->GetLinearVelocity();
}

float Ball::GetAngle()
{
    return body->GetAngle();
}
