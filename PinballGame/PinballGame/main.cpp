#include <windows.h>
#include <vector>
#include <gl/glut.h>
#include <Box2D/Box2D.h>

#include "pinball.h"
#include "ball.h"

#include <string>

const int WIDTH = 960;
const int HEIGHT = 1280;

int time = 0;

const int font = (int)GLUT_BITMAP_9_BY_15;
char s[30];

Pinball* pinball;
bool pause = false;

void PollKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'p':
		pause = !pause;
		break;
	case 'n':
		pinball->AddBall();
		break;
	case ' ':
		time++;
		pinball->PullPiston();
		break;
	case 'z':
		pinball->FlipLeft();
		break;
	case '/':
		pinball->FlipRight();
		break;
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
	case 'z':
		pinball->UnflipLeft();
		break;
	case '/':
		pinball->UnflipRight();
		break;
	default:
		break;
	}
}

void GameStart()
{
	pinball = new Pinball();
}

void ProjectionToModelView() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void ModelViewToProjection() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);
	glScalef(1, -1, 1);
	glTranslatef(0, -HEIGHT, 0);
	glMatrixMode(GL_MODELVIEW);
}

void renderBitmapString(float x, float y, void* font, const char* string) {
	const char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void RenderScore()
{
	glColor3d(1.0, 1.0, 1.0);
	ModelViewToProjection();
	glPushMatrix();
	glLoadIdentity();
	int score = pinball->GetScore();
	renderBitmapString(830, 800, (void*)font, "Your Score");
	renderBitmapString(830, 830, (void*)font, std::to_string(score).c_str());
	glPopMatrix();
	ProjectionToModelView();
	glutSwapBuffers();
}

void Render()
{
	pinball->Render();
	RenderScore();
}


void Update(int value)
{
	if (pause)
		pinball->Step();
	glutPostRedisplay();
	glutTimerFunc(20, Update, 0);
}

int main(int argc, char** argv)
{
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInit(&argc, argv);
	glutCreateWindow("Pinball");

	GameStart();

	glutDisplayFunc(Render);
	glutTimerFunc(20, Update, 0);
	glutKeyboardUpFunc(KeyUp);
	glutKeyboardFunc(PollKeyboard);
	glutMainLoop();
    return 0;
}