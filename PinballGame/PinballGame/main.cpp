#include <windows.h>
//#include <gl/gl.h>
//#include <gl/glu.h>
#include <gl/glut.h>
#include <Box2D/Box2D.h>

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_TRIANGLES);
    {
        glColor3f(0.666, 0.255, 0.255);
        glVertex2f(0.0f, 0.93f);
        glColor3f(0.255, 0.666, 0.255);
        glVertex2f(-0.80f, 0.70f);
        glColor3f(0.255, 0.255, 0.666);
        glVertex2f(0.80f, 0.70f);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);

    glutInitWindowSize(640, 480);
    glutCreateWindow("Test Window");

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}