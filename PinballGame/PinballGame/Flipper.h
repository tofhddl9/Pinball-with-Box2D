#ifndef __FLIPPER_H__
#define __FLIPPER_H__
#pragma once
#include <Box2D/Box2D.h>
#include <GL/glut.h>

class Flipper
{
public:
    Flipper(b2World*, const b2Vec2 pivot_pos, const b2Vec2 head_pos, const float head_angle, bool is_left);
    Flipper(b2World*, const b2Vec2 pivot_pos, const b2Vec2 LWH);

    void Render();
    void SetIsKeyDown(bool isKeyDown);
    bool IsKeyDown();
    void Flip();
    void Unflip();

private:
    void CreatePivot(b2World* world, const b2Vec2 pivot_pos);
    void CreateHead(b2World* world, const b2Vec2 head_pos, const float head_angle);
    void CreateHead(b2World* world, const b2Vec2 head_pos, const b2Vec2 LWH);
    void CreateJoint(b2World* world, const bool is_left);
    void CreateJoint(b2World* world);

    b2RevoluteJoint* joint_;
    b2Body* pivot_;
    b2Body* head_;
    b2Vec2 halfWH_;
    bool isKeyDown_;
    bool isLeft_;
};
#endif