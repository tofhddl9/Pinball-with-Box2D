#include "wall.h"
#include "GL/glut.h"

Wall::Wall(b2World* world, WALL_TYPE type, b2Vec2* wall_points, int num_points)
{
    b2BodyDef body_def;
    body_def.type = b2_staticBody;
    body_ = world->CreateBody(&body_def);
    type_ = type;
    wall_points_ = wall_points;
    num_points_ = num_points;

    b2ChainShape shape;
    if (type == LINE_CHAIN)
        shape.CreateChain(wall_points, num_points);
    else
        shape.CreateLoop(wall_points, num_points);

    b2FixtureDef fixture_def;
    fixture_def.shape = &shape;
    fixture_def.density = 0.0f;
    body_->CreateFixture(&fixture_def);

}

void Wall::Render()
{
    glPushMatrix();
    glColor3f(0.9f, 0.2f, 0.4f);
    if (type_ == LINE_CHAIN)
        glBegin(GL_LINE_STRIP);
    else if (type_ == LINE_LOOP)
        glBegin(GL_LINE_LOOP);
    
    for (int i = 0; i < num_points_; ++i) {
        printf("%f %f\n", wall_points_[i].x, wall_points_[i].y);
        glVertex2f(wall_points_[i].x, wall_points_[i].y);
    }
    
    glEnd();
}
