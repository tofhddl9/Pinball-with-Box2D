#pragma once
#include <Box2D/Box2D.h>
#include <GL/glut.h>
#include "setting.h"
class Flipper
{
public:
    Flipper(b2World*, const b2Vec2 pivot_pos, const float head_angle,
        const bool is_left, b2Vec2 LWH);
    Flipper(b2World*, const b2Vec2 pivot_pos, const b2Vec2 LWH);
    ~Flipper();

    void Render();
    void SetIsKeyDown(bool isKeyDown);
    bool IsKeyDown();
    void Flip();
    void Unflip();
    bool IsLeft();

private:
    void CreatePivot(b2World* world, const b2Vec2 pivot_pos);
    void CreateHead(b2World* world, const b2Vec2 head_pos,
        const float head_angle, const b2Vec2 LWH);
    void CreateHead(b2World* world, const b2Vec2 head_pos, const b2Vec2 LWH);
    void CreateJoint(b2World* world, const bool is_left);
    void CreateJoint(b2World* world);

    b2RevoluteJoint* joint_;
    body_ptr pivot_;
    body_ptr head_;
    b2Vec2 halfWH_;
    bool isKeyDown_;
    bool isLeft_;
};