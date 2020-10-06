#include "rebounder.h"

Rebounder::Rebounder(b2World* world, b2Vec2 p1, b2Vec2 p2, b2Vec2 other)
{
    p1_ = p1;
    p2_ = p2;
    other_ = other;

    b2BodyDef bd;
    bd.type = b2_staticBody;
    body_ = world->CreateBody(&bd);

    b2ChainShape shape;
    rebounder_points_ = new b2Vec2[2];
    rebounder_points_[0] = p1;
    rebounder_points_[1] = p2;
    shape.CreateChain(rebounder_points_, 2);

    body_->CreateFixture(&shape, 1.0f);

    int objectType = REBOUNDER;
    body_->SetUserData((void*)objectType);
}

Rebounder::~Rebounder()
{
    delete[] rebounder_points_;
}

void Rebounder::Render()
{
    glPushMatrix();

    //glColor3f(0.2f, 0.5f, 1.0f);
    glBegin(GL_POLYGON);
    {
        glColor3f(0.2f, 0.5f, 1.0f);
        glVertex2f(p1_.x, p1_.y);
        glVertex2f(p2_.x, p2_.y);
        glColor3f(0.1f, 0.0f, 0.0f);
        glVertex2f(other_.x, other_.y);
    }
    glEnd();
    glPopMatrix();
}
