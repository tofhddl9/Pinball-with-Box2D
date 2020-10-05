#pragma once
#include <Box2D/Box2D.h>
#include <GL/glut.h>
#include "setting.h"

class Circle {
public:
    virtual void Render() = 0;
    void RenderCircle();

protected:
    b2Body* body_;
    float radius_;
};