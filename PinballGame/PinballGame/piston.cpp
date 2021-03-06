#include "piston.h"

Piston::Piston(b2World *world, const b2Vec2 pivot_pos,
    const b2Vec2 head_pos, const float radius)
{
    b2BodyDef body_def;
    b2FixtureDef fixture;

    body_def.type = b2_staticBody;
    body_def.position.Set(pivot_pos.x, pivot_pos.y);
    pivot_ = world->CreateBody(&body_def);

    body_def.type = b2_dynamicBody;
    body_def.position.Set(head_pos.x, head_pos.y);
    head_ = world->CreateBody(&body_def);
    b2CircleShape circle;
    circle.m_radius = head_radius_ = radius;
    head_->CreateFixture(&circle, 100.0f);

    int objectType = PISTON;
    head_->SetUserData((void*)objectType);

    CreateJoint(world, pivot_, head_);
}

void Piston::CreateJoint(b2World* world, body_ptr pivot, body_ptr head)
{
    b2PrismaticJointDef prismaticJoint;
    prismaticJoint.bodyA = pivot_;
    prismaticJoint.bodyB = head_;
    prismaticJoint.collideConnected = true;

    prismaticJoint.localAnchorA.Set(1, 0);
    prismaticJoint.localAnchorB.Set(0, -1);
    prismaticJoint.localAxisA.Set(0, 1);
    prismaticJoint.enableLimit = true;

    prismaticJoint.enableMotor = false;
    prismaticJoint.motorSpeed = 100;
    joint_ = (b2PrismaticJoint*)world->CreateJoint(&prismaticJoint);
}


void Piston::Pull()
{
    joint_->EnableLimit(true);
    joint_->EnableMotor(false);
}

void Piston::Push(int time)
{
    printf("Power :%f\n", joint_->GetMaxMotorForce());
    joint_->SetMaxMotorForce(FORCE_PER_PRESSED_TIME * time);
    joint_->EnableLimit(false);
    joint_->EnableMotor(true);
}

void Piston::Render()
{
    glPushMatrix();

    glColor3f(0.9f, 0.2f, 0.4f);
    glTranslatef(head_->GetPosition().x, head_->GetPosition().y, 0.0f);
    glRotatef(head_->GetAngle(), 0.0f, 0.0f, 1.0f);

    float theta;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        theta = b2_pi * i / 180;
        glVertex2f(head_radius_ * cos(theta), head_radius_ * sin(theta));
    }
    glEnd();

    glPopMatrix();
}