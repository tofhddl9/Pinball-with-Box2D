#pragma once
#include "Box2D/Box2D.h"
#include "GL/glut.h"
#include "setting.h"

class Water
{
public:
    Water(b2World* world, b2Vec2 center, b2Vec2 LWH);
    void Render();

private:
    b2Body *body_;
    b2Vec2 LWH_;
};