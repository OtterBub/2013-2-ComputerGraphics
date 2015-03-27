#include "InputFunction.h"

extern TKpoint g_eye;
extern TKpoint g_center;
extern TKpoint g_angle;

TKpoint pre_point = {0, };

void mouseFunc(int button, int state, int x, int y)
{
	pre_point.x = x;
	pre_point.y = y;
}

void mouseMove(int x, int y)
{
	g_angle.y -= (pre_point.x - (float)x) / 2;
	g_angle.x -= (pre_point.y - (float)y) / 2;

	pre_point.x = (float)x;
	pre_point.y = (float)y;

	glutPostRedisplay();
}