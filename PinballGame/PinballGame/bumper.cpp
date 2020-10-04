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
    glPushMatrix();
    glTranslated(body_->GetPosition().x, body_->GetPosition().y, 0);

    glColor3f(0.8f, 0.4f, 0.6f);
    glBegin(GL_POLYGON);
    float theta;
    for (int i = 0; i < 360; ++i) {
        theta = i * b2_pi / 180.0f;
        glVertex2f(radius_ * cos(theta), radius_ * sin(theta));
    }
    glEnd();
    glPopMatrix();
}

