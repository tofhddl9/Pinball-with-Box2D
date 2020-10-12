#pragma once

#include "Box2D/Box2D.h"
#include "setting.h"
#include <algorithm>

enum WALL_TYPE {
    LINE_CHAIN,
    LINE_LOOP
};

class Wall
{
public:
    Wall(b2World* world, const WALL_TYPE type,
        b2Vec2* wall_points, const int num_points);
    ~Wall();
    void Render();

private:
    WALL_TYPE type_;
    body_ptr body_;
    b2Vec2* wall_points_;
    int num_points_;
};