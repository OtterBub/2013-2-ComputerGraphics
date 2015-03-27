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
	if(GLOBAL.camera_debug){
		gluLookAt(GLOBAL.g_eye.x, GLOBAL.g_eye.y, GLOBAL.g_eye.z
			, GLOBAL.g_center.x, GLOBAL.g_center.y, GLOBAL.g_center.z
			, 0, 1, 0);

		glRotatef(GLOBAL.g_angle.x, 1, 0, 0);
		glRotatef(GLOBAL.g_angle.y, 0, 1, 0);
		glRotatef(GLOBAL.g_angle.z, 0, 0, 1);

	} else {
		GLOBAL.g_angle.x = 0;
		GLOBAL.g_angle.y = 0;
		GLOBAL.g_angle.z = 0;

		GLOBAL.g_eye = CAMERA.getEyePos();
		GLOBAL.g_center = CAMERA.getCenterPos();

		gluLookAt(GLOBAL.g_eye.x, GLOBAL.g_eye.y, GLOBAL.g_eye.z
			, GLOBAL.g_center.x, GLOBAL.g_center.y, GLOBAL.g_center.z
			, 0, 1, 0);
	}

	

	WORLD.draw();
	WORLD.debugDraw();

	glLoadIdentity();
	glutSwapBuffers();
}

void reShape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)w/(float)h, 1.0, 2000.0f);

	glMatrixMode(GL_MODELVIEW);	
}

void timerFunc(int value)
{
	WORLD.update();
	glutPostRedisplay();
	glutTimerFunc( 16, timerFunc, 0 );
}