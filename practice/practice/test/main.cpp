#include <gl/glut.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
float world_x, world_y, world_z;
float per_z = 800.0;   //원근투영
int i;
struct snowinfo
{
	float x;
	float y;
	float z;
};
struct snowinfo snow[50];

void main(int argc, char *argv[])
{
	//윈도우 초기화 및 생성
	srand( (unsigned)time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutCreateWindow("Points Drawing");

	//필요한 콜백 함수 설정
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{

	float x, y, z;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //바탕색 지정
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT); //설정된 색으로 전체를 칠하기
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);  
	//카메라 위치 바꾸기
	gluLookAt(
		0.0, 0.0, per_z, 
		0.0, 0.0, 0.0, 
		0.0, 1.0, 0.0);

	//보는 각도 바꾸기
	glRotatef(30+world_x, 1.0, 0.0, 0.0);
	glRotatef(world_y, 0.0, 1.0, 0.0);
	glRotatef(world_z, 0.0, 0.0, 1.0);

	//바닥 그리기
	glColor4f(1.0f, 1.0f, .0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3f(-400.0f, 0.0, -400.0f);
	glVertex3f(400.0f, 0.0, -400.0f);
	glVertex3f(400.0f, 0.0, 400.0f);
	glVertex3f(-400.0f, 0.0, 400.0f);
	glEnd();
	
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(rand()%600-300, rand()%200, rand()%600-300);
	glutSolidSphere(10, 10, 10);
	//for(i=0; i<50; i++)
	//{
	//	glTranslatef(snow[i].x, snow[i].y, snow[i].z);
	//	glutSolidSphere(10, 10, 10);
	//	snow[i].y--;
	//}
	
	
	

	glLoadIdentity();
	glutSwapBuffers(); //화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90, 500/500, 1.0, 1500);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'x':
		world_x +=10.0;
		//for(i=0; i<50; i++)
		//{
		//	snow[i].x = rand()%600-300;
		//	snow[i].y = rand()%100;
		//	snow[i].z = rand()%600-300;
		//}
		break;
	case 'y':
		world_y +=10.0;
		break;
	case 'z':
		world_z +=10.0;
		break;
	case 'p':
		per_z +=10.0;
		break;
	case 'o':
		per_z -=10.0;
		break;
	}
	glutPostRedisplay();
}
void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}