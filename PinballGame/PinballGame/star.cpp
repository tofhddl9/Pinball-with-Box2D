#include "star.h"

Star::Star(b2World* world, b2Vec2 center,
    const float centerToVertex, const int type)
{
    size_ = centerToVertex;

    b2BodyDef bd;
    bd.type = b2_staticBody;
    bd.position = center;
    body_ = world->CreateBody(&bd);

    b2CircleShape shape;
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.isSensor = true;
    body_->CreateFixture(&fd);

    int objectType = type;
    body_->SetUserData((void*)objectType);
}

void Star::Render()
{
    if ((int)body_->GetUserData() == STAR_LARGE)
        glColor3f(1.0f, 1.0f, 0.0f);
    else
        glColor3f(0.7f, 0.7f, 0.5f);

    glPushMatrix();
    glTranslatef(body_->GetPosition().x, body_->GetPosition().y, 0.0f);

    float theta;
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i += 72) {
        theta = b2_pi * i / 180;
        glVertex2f(size_ * cos(theta), size_ * sin(theta));
        glVertex2f(0, 0);
    }
    glEnd();
    glLineWidth(1);
    glPopMatrix();
}