#pragma once
#include <GL/glut.h>
#include <Box2D/Box2D.h>
#include "setting.h"

class Rebounder
{
public:
    Rebounder(b2World *world, b2Vec2 p1, b2Vec2 p2, b2Vec2 other);
    ~Rebounder();
    void Render();

private:
    body_ptr body_;
    b2Vec2* rebounder_points_;
    b2Vec2 p1_, p2_, other_;
};