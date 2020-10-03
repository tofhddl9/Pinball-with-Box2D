#include <windows.h>
#include <vector>
#include <gl/glut.h>
#include <Box2D/Box2D.h>

#include "pinball.h"
#include "ball.h"

const int WIDTH = 960;
const int HEIGHT = 1280;

int time = 0;

Pinball* pinball;
bool pause = false;

void PollKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'p':
		pause = !pause;
		break;
	case ' ':
		pinball->PullPiston();
		time++;
		printf("pressed time : %d\n",time);
		break;
	case 'n':
		pinball->AddBall();
	default:
		break;
	}
	glutPostRedisplay();
}

void KeyUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		pinball->PushPiston(time);
		time = 0;
		break;
	default:
		break;
	}
}

void Setup()
{
	pinball = new Pinball();
}

void Render()
{
	pinball->Render();
}

void Update(int value)
{
	if (pause) {
		pinball->Step();
	}
	glutPostRedisplay();
	glutTimerFunc(20, Update, 0);
}

void display(b2World* world)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    b2Body* objects = world->GetBodyList();
}

int main(int argc, char** argv)
{
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInit(&argc, argv);
	glutCreateWindow("Pinball");

	Setup();

	glutDisplayFunc(Render);
	glutTimerFunc(20, Update, 0);
	glutKeyboardFunc(PollKeyboard);
	glutKeyboardUpFunc(KeyUp);
	glutMainLoop();
    return 0;
}