#ifndef __WALL_H__
#define __WALL_H__
#pragma once

#include "Box2D/Box2D.h"

enum WALL_TYPE {
    LINE_CHAIN,
    LINE_LOOP
};

class Wall
{
public:
    Wall(b2World* world, WALL_TYPE type, b2Vec2* wall_points, int num_points);
    void Render();

private:
    WALL_TYPE type_;
    b2Body* body_;
    b2Vec2* wall_points_;
    int num_points_;
};

#endif