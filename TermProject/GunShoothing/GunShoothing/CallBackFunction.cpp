#include "CallBackFunction.h"

void drawScene()
{
	glClearColor( 0.5, 0.5, 0.5, 1);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	UI.draw();

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
	if(GLOBAL.camera_debug){
		WORLD.debugDraw();

		glPushMatrix();
		glLoadIdentity();
		TKpoint temp;
		temp.x = GLOBAL.realMousePoint.x;
		temp.y = GLOBAL.realMousePoint.y;
		temp.z = GLOBAL.realMousePoint.z;

		glTranslatef(temp.x, temp.y, temp.z);
		glutWireCube(10);

		glPopMatrix();
	}

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
	SOUND.pSystem->update();
	WORLD.update();
	glutPostRedisplay();
	glutTimerFunc( 16, timerFunc, 0 );
}