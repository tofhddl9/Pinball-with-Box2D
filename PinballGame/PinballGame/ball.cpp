/*
#include "ball.h"

Ball::Ball(b2World_ptr world, b2Vec2 pos, float radius) {

    b2BodyDef body_def;
    body_def.position.Set(pos.x, pos.y);
    body_def.angle = 0;
    body_def.type = b2_dynamicBody;
    body_def.bullet = true;
    body_ = std::make_unique<b2Body, decltype(body_deleter_)>(world->CreateBody(&body_def), body_deleter_);

    b2CircleShape shape;
    shape.m_radius = radius;

    b2FixtureDef fixture_def;
    fixture_def.density = 1.0f;
    fixture_def.friction = 0.36f;
    fixture_def.restitution = 0.6f;
    fixture_def.shape = &shape;

    body_->CreateFixture(&fixture_def);
}

b2Vec2 Ball::GetPosition()
{
    return body_->GetPosition();
}

b2Vec2 Ball::GetVelocity()
{
    return body_->GetLinearVelocity();
}

float Ball::GetAngle()
{
    return body_->GetAngle();
}
*/