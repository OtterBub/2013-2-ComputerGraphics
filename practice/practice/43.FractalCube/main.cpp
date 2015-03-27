#include <iostream>
#include <vector>

#include <gl/glut.h>
#include <list>

float g_x;
float g_y;
float g_z;

void drawScene();
void Reshape(int w, int h);
void mouseFunc(int button, int state, int x, int y);
GLvoid mouseMove(int x, int y);

typedef struct _TKPoint {
	float x;
	float y;
	float z;
} TKPoint;

void drawCubeFractal(TKPoint p1, TKPoint p2, TKPoint p3, TKPoint p4) 
{
	float maxLength = 0;

	float length = abs(p2.x - p1.x);
	maxLength = length;

	length = abs(p2.y - p1.y);
	if(maxLength < length)
		maxLength = length;

	length = abs(p2.z - p1.z);
	if(maxLength < length)
		maxLength = length;

	if(maxLength < 2)
		return;


	glColor4f(1, 0, 0, 1);
	glBegin(GL_LINE_LOOP);
	
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glVertex3f(p4.x, p4.y, p4.z);

	glEnd();

	TKPoint midPoint[4];

	midPoint[0].x = (p1.x + p2.x) / 2;
	midPoint[0].y = (p1.y + p2.y) / 2;
	midPoint[0].z = (p1.z + p2.z) / 2;

	midPoint[1].x = (p2.x + p3.x) / 2;
	midPoint[1].y = (p2.y + p3.y) / 2;
	midPoint[1].z = (p2.z + p3.z) / 2;

	midPoint[2].x = (p3.x + p4.x) / 2;
	midPoint[2].y = (p3.y + p4.y) / 2;
	midPoint[2].z = (p3.z + p4.z) / 2;

	midPoint[3].x = (p4.x + p1.x) / 2;
	midPoint[3].y = (p4.y + p1.y) / 2;
	midPoint[3].z = (p4.z + p1.z) / 2;

	drawCubeFractal(midPoint[0], midPoint[1], midPoint[2], midPoint[3]);
}

int main()
{
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize(800, 600);
	glutCreateWindow("Fractal");

	glutMouseFunc( mouseFunc );
	glutMotionFunc( mouseMove );

	glutDisplayFunc( drawScene );
	glutReshapeFunc( Reshape );

	glutMainLoop();

	return 0;
}

void drawScene()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor( 1, 1, 1, 1);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glRotatef(g_x, 1.0, 0.0, 0.0);
	glRotatef(g_y, 0.0, 1.0, 0.0);
	glRotatef(g_z, 0.0, 0.0, 1.0);

	static const float CUBESIZE = 100;

	for(int i = 0; i < 6; i++){

		switch(i){
		case 0:
			break;
		case 1:
		case 2:
		case 3:
			glRotatef(90, 0, 1, 0);
			break;
		case 4:
			glRotatef(90, 1, 0, 0);
			break;
		case 5:
			glRotatef(180, 1, 0, 0);
			break;
		default:
			break;
		}

		glPushMatrix();

		glTranslatef(0, 0, 100);

		TKPoint setPoint[4];

		setPoint[0].x = -CUBESIZE;
		setPoint[0].y = -CUBESIZE;
		setPoint[0].z = 0;

		setPoint[1].x = CUBESIZE;
		setPoint[1].y = -CUBESIZE;
		setPoint[1].z = 0;

		setPoint[2].x = CUBESIZE;
		setPoint[2].y = CUBESIZE;
		setPoint[2].z = 0;

		setPoint[3].x = -CUBESIZE;
		setPoint[3].y = CUBESIZE;
		setPoint[3].z = 0;

		drawCubeFractal(setPoint[0], setPoint[1], setPoint[2], setPoint[3]);

		glPopMatrix();
	}

	glLoadIdentity();
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-200, 200, -200, 200, -500, 500);

	glMatrixMode(GL_MODELVIEW);
}

double pre_x, pre_y;

void mouseFunc(int button, int state, int x, int y)
{

	pre_x = x;
	pre_y = y;
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN) {
			
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if(state == GLUT_DOWN) {
		}
			
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

GLvoid mouseMove(int x, int y)
{

	//printf("%f, %f \n", x - pre_x, y - pre_y);

	g_y += (float)(x - pre_x) / 10.0f;
	g_x += (float)(y - pre_y) / 10.0f;

	pre_x = x;
	pre_y = y;
	glutPostRedisplay();
}