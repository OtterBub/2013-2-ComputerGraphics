#include "InputFunction.h"
#include "WorldInit.h"

void mouseFunc(int button, int state, int x, int y)
{
	if((button == GLUT_RIGHT_BUTTON)){
		int viewport[4];
		double modelview[16];
		double projection[16];
		float winX, winY;

		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);

		float z_cursor;
		winX = (float)x;
		winY = (float)viewport[3] - (float)y;
		glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z_cursor);

		double temp_x, temp_y, temp_z;

		gluUnProject(winX, winY, z_cursor, modelview, projection, viewport, &temp_x, &temp_y, &temp_z);

		GLOBAL.projection_point.x = temp_x;
		GLOBAL.projection_point.y = temp_y;
		GLOBAL.projection_point.z = temp_z;

		std::cout << GLOBAL.projection_point.x << ", " 
			<< GLOBAL.projection_point.y << ", "
			<< GLOBAL.projection_point.z << std::endl;

		WORLD.pickingCheck(GLOBAL.projection_point);
	}

	GLOBAL.pre_point.x = x;
	GLOBAL.pre_point.y = y;
}

void mouseMove(int x, int y)
{
	GLOBAL.g_angle.y -= (GLOBAL.pre_point.x - (float)x) / 5;
	GLOBAL.g_angle.x -= (GLOBAL.pre_point.y - (float)y) / 5;

	GLOBAL.pre_point.x = x;
	GLOBAL.pre_point.y = y;

	glutPostRedisplay();
}

void keyBoardFunc(unsigned char key, int x, int y)
{
	GLOBAL.keyDown[key] = true;

	switch(key) {
	case 'a':
		GLOBAL.g_camera.x += 5;
		break;
	case 'd':
		GLOBAL.g_camera.x -= 5;
		break;
	case 'w':
		GLOBAL.g_camera.z += 5;
		break;
	case 's':
		GLOBAL.g_camera.z -= 5;
		break;

	case 'r':
		GLOBAL.g_camera.y -= 5;
		break;
	case 'f':
		GLOBAL.g_camera.y += 5;
		break;
	case ' ':
		WORLD.removeAllObject();
		GLOBAL.g_init = false;
		break;
	case '1':
		init();
		break;
	case '2':
		initTest();
		break;
	case '3':
		initStage1();
		break;
	case '4':
		initStage2();
		break;
	default:
		break;
	}
}

void keyBoardUpFunc(unsigned char key, int x, int y)
{
	GLOBAL.keyDown[key] = false;
	
	switch(key) {
	default:
		break;
	}
}