#ifndef __PISTON_H__
#define __PISTON_H__

#pragma once
#include "Box2D/Box2D.h"
#include "GL/glut.h"

class Piston
{
public:
    Piston(b2World *world, const b2Vec2 pivot_pos,
        const b2Vec2 head_pos, const float radius);
    void Pull();
    void Push(int time);
    void Render();

private:
    void CreateJoint(b2World* world, b2Body* pivot, b2Body* head);

    const float FORCE_PER_PRESSED_TIME = 250.0;
    float head_radius_;
    b2Body* head_;
    b2Body* pivot_;
    b2PrismaticJoint* joint_;
};


#endif