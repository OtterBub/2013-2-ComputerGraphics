#include <iostream>
#include <vector>

#include <gl/glut.h>
#include <list>

float g_x;
float g_y;
float g_z;

float g_view = 200;

void drawScene();
void Reshape(int w, int h);
void mouseFunc(int button, int state, int x, int y);
GLvoid mouseMove(int x, int y);
void keyFunc(unsigned const char key, int x, int y);

typedef struct _TKPoint {
	float x;
	float y;
	float z;
} TKPoint;

void fractalTriangle(TKPoint p1, TKPoint p2, TKPoint p3) {

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

	glEnd();

	TKPoint midPoint[3];
	midPoint[0].x = (p1.x + p2.x) / 2;
	midPoint[0].y = (p1.y + p2.y) / 2;
	midPoint[0].z = (p1.z + p2.z) / 2;

	midPoint[1].x = (p2.x + p3.x) / 2;
	midPoint[1].y = (p2.y + p3.y) / 2;
	midPoint[1].z = (p2.z + p3.z) / 2;

	midPoint[2].x = (p3.x + p1.x) / 2;
	midPoint[2].y = (p3.y + p1.y) / 2;
	midPoint[2].z = (p3.z + p1.z) / 2;
	
	fractalTriangle(p1, midPoint[0], midPoint[2]);
	fractalTriangle(midPoint[0], p2, midPoint[1]);
	fractalTriangle(midPoint[2], midPoint[1], p3);

}

void fractalPyamid(TKPoint p1, TKPoint p2, TKPoint p3, TKPoint p4) {

	float maxLength = 0;

	float length = abs(p2.x - p1.x);
	maxLength = length;

	length = abs(p2.y - p1.y);
	if(maxLength < length)
		maxLength = length;

	length = abs(p2.z - p1.z);
	if(maxLength < length)
		maxLength = length;

	if(maxLength < 40)
		return;

	glColor4f(1, 0, 0, 1);
	
	glBegin(GL_LINES);

	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p3.x, p3.y, p3.z);
	
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p4.x, p4.y, p4.z);

	glEnd();

	glBegin(GL_LINE_LOOP);

	glVertex3f(p2.x, p2.y, p2.z);
	
	glVertex3f(p3.x, p3.y, p3.z);
	
	glVertex3f(p4.x, p4.y, p4.z);

	glEnd();

	TKPoint midPoint[6];

	midPoint[0].x = (p1.x + p2.x) / 2;
	midPoint[0].y = (p1.y + p2.y) / 2;
	midPoint[0].z = (p1.z + p2.z) / 2;
	
	midPoint[1].x = (p1.x + p3.x) / 2;
	midPoint[1].y = (p1.y + p3.y) / 2;
	midPoint[1].z = (p1.z + p3.z) / 2;

	midPoint[2].x = (p1.x + p4.x) / 2;
	midPoint[2].y = (p1.y + p4.y) / 2;
	midPoint[2].z = (p1.z + p4.z) / 2;

	midPoint[3].x = (p2.x + p3.x) / 2;
	midPoint[3].y = (p2.y + p3.y) / 2;
	midPoint[3].z = (p2.z + p3.z) / 2;

	midPoint[4].x = (p3.x + p4.x) / 2;
	midPoint[4].y = (p3.y + p4.y) / 2;
	midPoint[4].z = (p3.z + p4.z) / 2;

	midPoint[5].x = (p4.x + p2.x) / 2;
	midPoint[5].y = (p4.y + p2.y) / 2;
	midPoint[5].z = (p4.z + p2.z) / 2;

	fractalPyamid(p1, midPoint[0], midPoint[1], midPoint[2]);

	fractalPyamid(midPoint[0], p2, midPoint[3], midPoint[5]);
	fractalPyamid(midPoint[1], p3, midPoint[3], midPoint[4]);
	fractalPyamid(midPoint[2], p4, midPoint[4], midPoint[5]);

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

	glutKeyboardFunc( keyFunc );

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

	float m_groundSize = 80;

	static float TRIANGLE = 100;

	TKPoint setTri[4];
	setTri[0].x = 0;
	setTri[0].y = TRIANGLE;
	setTri[0].z = 0;

	setTri[1].x = -TRIANGLE;
	setTri[1].y = -TRIANGLE;
	setTri[1].z = TRIANGLE;

	setTri[2].x = +TRIANGLE;
	setTri[2].y = -TRIANGLE;
	setTri[2].z = TRIANGLE;

	setTri[3].x = 0;
	setTri[3].y = -TRIANGLE;
	setTri[3].z = -TRIANGLE;

	fractalPyamid(setTri[0], setTri[1], setTri[2], setTri[3]);


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

void keyFunc(unsigned const char key, int x, int y)
{
	switch(key) {
	case 'w':
		g_view --;
		break;
	case 's':
		g_view ++;
		break;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-g_view, g_view, -g_view, g_view, -500, 500);

	glMatrixMode(GL_MODELVIEW);
}