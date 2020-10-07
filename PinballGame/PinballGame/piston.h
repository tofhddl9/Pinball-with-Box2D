#pragma once
#include "Box2D/Box2D.h"
#include "GL/glut.h"
#include "setting.h"

class Piston
{
public:
    Piston(b2World *world, const b2Vec2 pivot_pos,
        const b2Vec2 head_pos, const float radius);
    void Pull();
    void Push(int time);
    void Render();

private:
    void CreateJoint(b2World* world, body_ptr pivot, body_ptr head);

    const float FORCE_PER_PRESSED_TIME = 250.0;
    float head_radius_;
    body_ptr head_;
    body_ptr pivot_;
    b2PrismaticJoint* joint_;
};