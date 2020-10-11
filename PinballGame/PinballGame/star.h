#pragma once

#include <GL/glut.h>
#include <Box2D/Box2D.h>
#include "setting.h"

class Star
{
public:
    Star(b2World* world, b2Vec2 center,
        const float centerToVertex, const int type);
    void Render();

private:
    body_ptr body_;
    float size_;
};