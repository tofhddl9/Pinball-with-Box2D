#include <windows.h>
#include <vector>
//#include <gl/gl.h>
//#include <gl/glu.h>
#include <gl/glut.h>
#include <Box2D/Box2D.h>

#include "pinball.h"
#include "ball.h"

const int WIDTH = 640;
const int HEIGHT = 480;

void init()
{
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW); 
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

}

int main(int argc, char** argv)
{
    Pinball* pinball_game = new Pinball();
    pinball_game->Step();
    return 0;
}