#include "ball.h"
#include "GL/glut.h"

Ball::Ball(b2World* world, b2Vec2 pos, float radius) {

    b2BodyDef body_def;
    body_def.position.Set(pos.x, pos.y);
    body_def.angle = 0;
    body_def.type = b2_dynamicBody;
    body_def.bullet = true;
    body_ = world->CreateBody(&body_def);

    b2CircleShape shape;
    shape.m_radius = radius;

    b2FixtureDef fixture_def;
    fixture_def.density = 1.0f;
    fixture_def.friction = 0.36f;
    fixture_def.restitution = 0.6f;
    fixture_def.shape = &shape;

    body_->CreateFixture(&fixture_def);
    radius_ = radius;
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

float Ball::GetRadius()
{
    return radius_;
}

void Ball::Render()
{
    glPushMatrix();
    glTranslatef(body_->GetPosition().x, body_->GetPosition().y, 0.0f);
    glRotatef(body_->GetAngle(), 0.0f, 0.0f, 1.0f);
    glColor3f(0.9f, 0.2f, 0.4f);

    float theta;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        theta = 3.142 * i / 180;
        glVertex2f(radius_ * cos(theta), radius_ * sin(theta));
    }
    glEnd();
    glPopMatrix();
}
