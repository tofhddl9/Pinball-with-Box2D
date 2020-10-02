#ifndef __WALL_H__
#define __WALL_H__
#pragma once

#include "Box2D/Box2D.h"

enum WALL_TYPE {
    LINES,
    LINE_STRIP,
    LINE_LOOP
};

class Wall
{
public:
    Wall(b2World* world, WALL_TYPE type, b2Vec2* wall_point, int num_points);
    void Render();

private:
    WALL_TYPE type_;
    b2Body* body_;
    b2Vec2* wall_points_;
    int num_points_;
};

#endif