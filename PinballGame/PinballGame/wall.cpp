#include "wall.h"

Wall::Wall(b2World* world, WALL_TYPE type, b2Vec2* wall_point, int num_points)
{
    b2BodyDef body_def;
    body_ = world->CreateBody(&body_def);
    type_ = type;
    wall_points_ = wall_point;
    num_points_ = num_points;

    if (type == LINES) {

    }
    else if (type == LINE_STRIP) {

    }
    else if (type == LINE_LOOP) {

        b2ChainShape shape;
        shape.CreateLoop(wall_point, 5);
        b2FixtureDef fixture_def;
        fixture_def.shape = &shape;
        fixture_def.density = 0.0f;
        body_->CreateFixture(&fixture_def);
    }
}

void Wall::Render()
{

}
