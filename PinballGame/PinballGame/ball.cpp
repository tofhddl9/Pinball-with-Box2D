#include "ball.h"
#include "GL/glut.h"

Ball::Ball(b2World* world, const b2Vec2 pos,
    const float radius, const int ballType) {

    radius_ = radius;
    ballType_ = ballType;

    b2BodyDef body_def;
    body_def.position.Set(pos.x, pos.y);
    body_def.angle = 0;
    body_def.type = b2_dynamicBody;
    body_def.bullet = true;
    body_ = world->CreateBody(&body_def);

    if (ballType&FLOATING) {
        float theta;
        b2Vec2 vs[4];
        for (int i = 0; i < 4; ++i) {
            vs[i].Set(radius * cos(b2_pi * i / 2.0f), radius * sin(b2_pi * i / 2.0f));
        }
        b2PolygonShape polyShape;
        polyShape.Set(vs, 4);

        b2FixtureDef fixture_def;
        fixture_def.shape = &polyShape;
        fixture_def.density = 1.0f;
        fixture_def.friction = 0.36f;
        fixture_def.restitution = 0.2f;

        body_->CreateFixture(&fixture_def);

        int objectType = (BALL|FLOATING);
        body_->SetUserData((void*)objectType);
    }

    else if (ballType == BALL) {
        b2CircleShape circleShape;
        circleShape.m_radius = radius;

        b2FixtureDef fixture_def;
        fixture_def.shape = &circleShape;
        fixture_def.density = 1.0f;
        fixture_def.friction = 0.36f;
        fixture_def.restitution = 0.2f;

        body_->CreateFixture(&fixture_def);

        int objectType = BALL;
        body_->SetUserData((void*)objectType);
    }
}

Ball::~Ball()
{
    puts("@@");
    body_->GetWorld()->DestroyBody(body_);
}

void Ball::Render()
{
    glColor3f(0.7f, 0.9f, 0.9f);
    RenderCircle();
}

body_ptr Ball::GetBody()
{
    return body_;
}
