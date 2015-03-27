#include "CallBackFunction.h"

TKpoint g_eye = {0, };
TKpoint g_center = {0, };
TKpoint g_angle = {0, };

bool g_init = false;

// -------------- INIT ---------------
void init()
{
	if(g_init)
		return;
	g_init = true;

	g_eye.x;
	g_eye.y = 100;
	g_eye.z = 100;

	g_center.x;
	g_center.y;
	g_center.z;

	glEnable(GL_DEPTH_TEST);
}

void drawScene()
{
	glClearColor( 1, 1, 1, 1);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	init();

	// Gloval View
	gluLookAt(g_eye.x, g_eye.y, g_eye.z
		, g_center.x, g_center.y, g_center.z
		, 0, 1, 0);
	glRotatef(g_angle.x, 1, 0, 0);
	glRotatef(g_angle.y, 0, 1, 0);
	glRotatef(g_angle.z, 0, 0, 1);
	
	World::Instance().draw();

	glLoadIdentity();
	glutSwapBuffers();
}

void reShape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, w/h, 1.0, 2000.0f);

	glMatrixMode(GL_MODELVIEW);	
}

void timerFunc(int value)
{
	World::Instance().update();
	glutPostRedisplay();
	glutTimerFunc( 16, timerFunc, 0 );
}