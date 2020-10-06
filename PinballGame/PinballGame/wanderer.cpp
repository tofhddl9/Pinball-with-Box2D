#include "wanderer.h"

Wanderer::Wanderer(b2World* world, const b2Vec2 head_pos,
    const b2Vec2 velocity, const b2Vec2 LWH, const b2Vec2 LR)
{
    LWH_ = LWH;
    LR_ = LR;

    b2BodyDef bd;
    bd.type = b2_kinematicBody;
    bd.position.Set(head_pos.x, head_pos.y);
    head_ = world->CreateBody(&bd);

    b2PolygonShape box;
    box.SetAsBox(LWH.x, LWH.y);
    head_->CreateFixture(&box, 100.0f);

    int objectType = WANDERER;
    head_->SetUserData((void*)objectType);

    head_->SetLinearVelocity(velocity);
}

void Wanderer::Wander()
{
    if (!IsInsideOfMap()) {
        head_->SetLinearVelocity(-head_->GetLinearVelocity());
    }
}

bool Wanderer::IsInsideOfMap()
{
    float32 head_x = head_->GetPosition().x;
    if (LR_.x < head_x and head_x < LR_.y)
        return true;
    return false;
}

void Wanderer::Render()
{
    glPushMatrix();

    glColor3f(0.9f, 0.5f, 0.3f);
    glTranslatef(head_->GetPosition().x, head_->GetPosition().y, 0.0f);
    glRotatef(head_->GetAngle(), 0.0f, 0.0f, 1.0f);

    glBegin(GL_POLYGON);
    {
        glVertex2f(-LWH_.x, -LWH_.y);
        glVertex2f(-LWH_.x, LWH_.y);
        glVertex2f(LWH_.x, LWH_.y);
        glVertex2f(LWH_.x, -LWH_.y);
    }
    glEnd();

    glPopMatrix();
}