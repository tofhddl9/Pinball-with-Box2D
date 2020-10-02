#include <windows.h>
#include <vector>
//#include <gl/gl.h>
//#include <gl/glu.h>
#include <gl/glut.h>
#include <Box2D/Box2D.h>

#include "pinball.h"
#include "ball.h"

int WIDTH = 640;
int HEIGHT = 480;

Pinball* pinball;
bool pause = false;

void PollKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		pause = !pause;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void Setup()
{
	pinball = new Pinball();
}

void Render()
{
	pinball->Render();
	
	// get position and angle by body(ground)
	b2Vec2 position = pinball->GetGround()->GetPosition();
	float32 angle = pinball->GetGround()->GetAngle();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position.x, position.y, 0.0f);	// Translation
	glRotatef(angle, 0.0f, 0.0f, 1.0f);			// Rotation
	glColor3f(0.8f, 0.8f, 0.8f);				// Set color

	glutSwapBuffers();
}

void Update(int value)
{
	if (pause) {
		pinball->Step();
	}
	glutPostRedisplay();
	glutTimerFunc(20, Update, 0);	//Recursive function
}

void Reshape(int _width, int _height)
{
	WIDTH = _width;
	HEIGHT = _height;
	glViewport(0, 0, _width, _height);
}

void display(b2World* world)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    b2Body* objects = world->GetBodyList();
}

int main(int argc, char** argv)
{
	// Initialize glut
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInit(&argc, argv);
	glutCreateWindow("Pinball");

	// Setting Box2D elements
	Setup();

	glutDisplayFunc(Render);		//If you want to render, Use it.
	glutReshapeFunc(Reshape);		//Reshape by window size
	glutTimerFunc(20, Update, 0);	//Update physics simulation

	glutKeyboardFunc(PollKeyboard);	//If you want to use keyborad event,
									//Activate this!
	glutMainLoop();
    return 0;
}