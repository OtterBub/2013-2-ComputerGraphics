#include "CallBackFunc.h"

// left : 100 / up : 101 / right : 102 / down : 103
#define LEFT	100
#define UP		101
#define RIGHT	102
#define DOWN	103

#define SPHERE 0
#define CUBE 1
#define CONE 2
#define TEAPOT 3

#define GROUND_SIZE 300.0f
#define OBJECT_SIZE 100

#define AUTO_STOP	10000
#define AUTO_LEFT	10001
#define AUTO_RIGHT	10002
#define AUTO_UP		10003
#define AUTO_DOWN	10004
#define AUTO_ZIGZAG	10005

#define AUTO_ZIGZAG_ASCEND 10010
#define AUTO_ZIGZAG_DEASCEND 10011

World* world = new World();

int g_Shage = CUBE;
int g_WorldX = 45;
int g_WorldY = 30;
int g_WorldZ;

float g_WorldScale = 1.0f;


GLvoid drawScene ( GLvoid )
{
	glClearColor( 0.0f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Global View;
	glTranslatef( WIDTH/2, HEIGHT/2, 0.0f );
	glRotatef(g_WorldX, 1.0, 0.0, 0.0);
	glRotatef(g_WorldY, 0.0, 1.0, 0.0);
	glRotatef(g_WorldZ, 0.0, 0.0, 1.0);
	glScalef(g_WorldScale, g_WorldScale, g_WorldScale);

	// 2d Screen
	glPushMatrix();
	{
		glTranslatef(-400.0, 0.0 , -300);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(WIDTH, 0.0, 0.0);
		glVertex3f(WIDTH, HEIGHT, 0.0);
		glVertex3f(0.0, HEIGHT, 0.0);
		glEnd();
		world->draw();
	}
	glPopMatrix();

	glPushMatrix();
	{
		const float COORDI_AXIS_SIZE = 7.0;
		const float AXIS_TRANS = (COORDI_AXIS_SIZE * 5.0f) / 2.0f;
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(AXIS_TRANS, 0.0, 0.0);
		glScalef(COORDI_AXIS_SIZE, 1, 1);
		glutSolidCube(5);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, AXIS_TRANS, 0.0);
		glScalef(1, COORDI_AXIS_SIZE, 1);
		glColor3f(0.0, 1.0, 0.0);
		glutSolidCube(5);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 0.0, AXIS_TRANS);
		glScalef(1, 1, COORDI_AXIS_SIZE);
		glColor3f(0.0, 0.0, 1.0);
		glutSolidCube(5);
		glPopMatrix();
	}
	glPopMatrix();

	glColor3f(0.5, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-GROUND_SIZE, 0.0, -GROUND_SIZE);
	glVertex3f(GROUND_SIZE, 0.0, -GROUND_SIZE);
	glVertex3f(GROUND_SIZE, 0.0, GROUND_SIZE);
	glVertex3f(-GROUND_SIZE, 0.0, GROUND_SIZE);
	glEnd();

	glPushMatrix();
	{
		glTranslatef(-200, 100, -100.0);
		glPushMatrix();
		{
			glColor3f(1.0, 0.0, 0.0);
			glScalef(1.0, 50.0, 1.0);
			glutSolidCube(5);
		}
		glPopMatrix();

		static float obj_angle = 0;
		glRotatef(obj_angle+=0.5, 0.0, 1.0, 0.0);
		glTranslatef(80, 0, 0);
		glColor3d(1.0, 0.0, 1.0);
		glutWireCube(80);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(200, 100, -100.0);
		glPushMatrix();
		{
			glColor3f(1.0, 0.0, 0.0);
			glScalef(1.0, 50.0, 1.0);
			glutSolidCube(5);
		}
		glPopMatrix();

		static float obj_angle = 0;
		glRotatef(obj_angle+=1, 0.0, 1.0, 0.0);
		glColor3d(1.0, 0.0, 1.0);
		glutWireSphere(40, 10, 10);
	}
	glPopMatrix();


	glPushMatrix();
	{
		glTranslatef(200, 200, 200.0);
		glRotatef(45, 0.0, 0.0, 1.0);
		glPushMatrix();
		{
			glColor3f(1.0, 0.0, 0.0);
			glScalef(1.0, 50.0, 1.0);
			glutSolidCube(5);
		}
		glPopMatrix();

		static float obj_angle = 0;
		glRotatef(obj_angle+=1, 0.0, 1.0, 0.0);
		glTranslatef(90, 0, 0);
		glColor3d(1.0, 0.0, 1.0);
		glutWireTorus(10, 80, 10, 15);

		glPushMatrix();
		{
			static float sub_obj_angle = 0;
			glRotatef(sub_obj_angle+=1, 0.0, 1.0, 0.0);
			glRotatef(90, 0.0, 0.0, 1.0);
			glutWireSphere(40, 10, 10);
		}
		glPopMatrix();
		
	}
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	glutSwapBuffers();
}

GLvoid reshape ( int w, int h )
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, w, 0, h, -h, h);
	//gluPerspective(60.0f, w/h, -h, h);
	/*gluLookAt(0.0, 0.0, 100.0,
	w/2, h/2, 0.0,
	0.0, 1.0, 0.0);*/

	glMatrixMode(GL_MODELVIEW);
}


GLvoid mouse(int button, int state, int x, int y)
{
	int r_y = HEIGHT - y;
	printf("mouse x : %d, y : %d\n", x, y);

	if(state == GLUT_DOWN) {
		switch (button)	{
		case GLUT_LEFT_BUTTON:

			switch(rand()%3)
			{
		
			case 0:
				{
					Object* temp = new RectObject( x, r_y, 10 + rand() % 30, 10 + rand() % 30 );
					temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
					temp->setRescaleAnimation(rand() % 2, 3.0f, 0.5f);
					temp->setVelocity(true, rand() % 10, rand() % 10);

					world->addObject(temp);
				}
				break;
			case 1:
				{
					Object* temp = new CircleObject( x, r_y, 10 + rand() % 20, 10 + rand() % 20 );
					temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
					temp->setRescaleAnimation(rand() % 2, 2.0f, 0.5f, 0.01f);
					temp->setVelocity(true, rand() % 2, rand() % 2);

					world->addObject(temp);
				}
				break;
			case 2:
				{
					Object* temp = new MorpingObject( x, r_y, 20 + rand() % 20, 20 + rand() % 20 );
					temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
					temp->setRescaleAnimation(rand() % 2, 2.0f, 0.5f, 0.01f);
					temp->setVelocity(true, rand() % 2, rand() % 2);

					world->addObject(temp);
				}
				break;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			world->allMoveToPoint(x, r_y);
			break;		

		default:
			break;
		}
	}
}

GLvoid mouseMove(int x, int y)
{
	int r_y = HEIGHT - y;
	switch(rand()%2)
	{
	case 0:
		{
			Object* temp = new RectObject( x, r_y, 20 );
			temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
			temp->setRescaleAnimation(rand() % 2, 3.0f, 0.5f);
			//temp->setVelocity(true, rand() % 10, rand() % 10);
			world->addObject(temp);
		}
		break;
	case 1:
		{
			Object* temp = new CircleObject( x, r_y, 20 );
			temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
			temp->setRescaleAnimation(rand() % 2, 3.0f, 0.5f);
			//temp->setVelocity(true, rand() % 10, rand() % 10);
			world->addObject(temp);
		}
		break;
	}

}

GLvoid keyBoardFunc(unsigned char key, int x, int y)
{
	switch(key)
	{
	case '1':
		g_Shage = SPHERE;
		break;
	case '2':
		g_Shage = CUBE;
		break;
	case '3':
		g_Shage = CONE;
		break;
	case '4':
		g_Shage = TEAPOT;
		break;
	case 'x':
		g_WorldX--;
		break;
	case 'X':
		g_WorldX++;
		break;
	case 'y':
		g_WorldY--;
		break;
	case 'Y':
		g_WorldY++;
		break;
	case 'z':
		g_WorldZ--;
		break;
	case 'Z':
		g_WorldZ++;
		break;
	case '-':
		g_WorldScale -= 0.05;
		break;
	case '=':
		g_WorldScale += 0.05;
		break;
	case ' ':
		break;
	default:
		break;
	}
}

GLvoid timerFunc(int val)
{
	glutPostRedisplay();
	glutTimerFunc( 16, timerFunc, 1 );
}

GLvoid specialKeyBoardFunc(int key, int x, int y)
{
	// left : 100 / up : 101 / right : 102 / down : 103
	switch(key)
	{
	case UP:
		break;
	case DOWN:
		break;
	case LEFT:
		break;
	case RIGHT:
		break;
	default:
		break;
	}
}