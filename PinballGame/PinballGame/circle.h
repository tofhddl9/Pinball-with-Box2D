#pragma once
#include <Box2D/Box2D.h>
#include <GL/glut.h>
#include "setting.h"

class Circle {
public:
    virtual ~Circle() {}
    virtual void Render() = 0;
    void RenderCircle();

protected:
    body_ptr body_;
    float radius_;
};