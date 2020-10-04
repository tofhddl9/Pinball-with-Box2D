#pragma once

#include <Box2D/Box2D.h>
#include <GL/glut.h>
#include "setting.h"

class Bumper
{
public:
    Bumper(b2World *world, const b2Vec2 pos, const float radius);
    void Render();

private:
    b2Body* body_;
    float radius_;
};