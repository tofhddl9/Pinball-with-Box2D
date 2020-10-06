#include "water.h"

Water::Water(b2World* world, b2Vec2 center, b2Vec2 LWH)
{
    LWH_ = LWH;

    b2BodyDef bd;
    bd.type = b2_staticBody;
    bd.position = center;
    body_ = world->CreateBody(&bd);

    b2PolygonShape box;
    box.SetAsBox(LWH.x, LWH.y);
    
    b2FixtureDef fd;
    fd.shape = &box;
    fd.isSensor = true;
    fd.density = 1.0f;
    body_->CreateFixture(&fd);

    int objectType = WATER;
    body_->SetUserData((void*)objectType);
}

void Water::Render()
{
    glPushMatrix();
    glTranslatef(body_->GetPosition().x, body_->GetPosition().y, 0);
    glColor3f(0.2f, 0.4f, 1.0f);
    glBegin(GL_POLYGON);
    {
        glVertex3f(-LWH_.x, -LWH_.y, 0);
        glVertex3f(-LWH_.x, LWH_.y, 0);
        glVertex3f(LWH_.x, LWH_.y, 0);
        glVertex3f(LWH_.x, -LWH_.y, 0);
    }
    glEnd();
    glPopMatrix();
}
