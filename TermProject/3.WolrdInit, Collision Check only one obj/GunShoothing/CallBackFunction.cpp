#include "CallBackFunction.h"

void drawScene()
{
	glClearColor( 0.5, 0.5, 0.5, 1);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	TKpoint temp;
	temp.x = GLOBAL.projection_point.x;
	temp.y = GLOBAL.projection_point.y;
	temp.z = GLOBAL.projection_point.z;

	glPushMatrix();

	glTranslatef(temp.x, temp.y, temp.z);
	glutWireCube(10);

	glPopMatrix();

	// Gloval View
	gluLookAt(GLOBAL.g_eye.x, GLOBAL.g_eye.y, GLOBAL.g_eye.z
		, GLOBAL.g_center.x, GLOBAL.g_center.y, GLOBAL.g_center.z
		, 0, 1, 0);

	glTranslatef(GLOBAL.g_camera.x, GLOBAL.g_camera.y, GLOBAL.g_camera.z);
	glRotatef(GLOBAL.g_angle.x, 1, 0, 0);
	glRotatef(GLOBAL.g_angle.y, 0, 1, 0);
	glRotatef(GLOBAL.g_angle.z, 0, 0, 1);	

	WORLD.draw();

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
	WORLD.update();
	glutPostRedisplay();
	glutTimerFunc( 16, timerFunc, 0 );
}