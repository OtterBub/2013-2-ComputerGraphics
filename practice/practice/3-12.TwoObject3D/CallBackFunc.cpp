#include "CallBackFunc.h"

#define SPHERE 0
#define CUBE 1
#define CONE 2
#define TEAPOT 3

World* world = new World();
int g_Shage = 0; // Wire
int g_x;
int g_y;
int g_z;
int g_Rotate_R;
int g_Rotate_L;

GLvoid drawScene ( GLvoid )
{
	glClearColor( 0.0f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Global View;
	glTranslatef( WIDTH/2, HEIGHT/2, 0.0f );
	glRotatef(g_x, 1.0, 0.0, 0.0);
	glRotatef(g_y, 0.0, 1.0, 0.0);
	glRotatef(g_z, 0.0, 0.0, 1.0);
	

	glPushMatrix();
	{
		const float COODI_AXIS_SIZE = 7.0;
		const float AXIS_TRANS = (COODI_AXIS_SIZE * 5.0f) / 2.0f;
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(AXIS_TRANS, 0.0, 0.0);
		glScalef(COODI_AXIS_SIZE, 1, 1);
		glutSolidCube(5);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, AXIS_TRANS, 0.0);
		glScalef(1, COODI_AXIS_SIZE, 1);
		glColor3f(0.0, 1.0, 0.0);
		glutSolidCube(5);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 0.0, AXIS_TRANS);
		glScalef(1, 1, COODI_AXIS_SIZE);
		glColor3f(0.0, 0.0, 1.0);
		glutSolidCube(5);
		glPopMatrix();
	}
	glPopMatrix();
	
	const float SOLID_POS_X = -200;
	const float SOLID_POS_Y = -100;
	const float GROUND_SIZE = 300.0f;
	glColor3f(0.5, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-GROUND_SIZE, SOLID_POS_Y - 80, -GROUND_SIZE);
	glVertex3f(GROUND_SIZE, SOLID_POS_Y - 80, -GROUND_SIZE);
	glVertex3f(GROUND_SIZE, SOLID_POS_Y - 80, GROUND_SIZE);
	glVertex3f(-GROUND_SIZE, SOLID_POS_Y - 80, GROUND_SIZE);
	glEnd();

	glPushMatrix();
	{
		
		// L Solid
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslatef(SOLID_POS_X, SOLID_POS_Y, 0);
		glRotatef(g_Rotate_L, 1.0, 0.0, 0.0);
		switch(g_Shage)
		{
		case SPHERE:
			glutSolidSphere(50, 10, 10);
			break;
			
		case CUBE:
			glutSolidCube(50);
			break;
			
		case CONE:
			glutSolidCone(50, 50, 10, 10);
			break;

		case TEAPOT:
			glutSolidTeapot(50);
			break;

		default:
			break;
		}
		glPopMatrix();

		// R Wire
		glPushMatrix();
		glTranslatef(-SOLID_POS_X, SOLID_POS_Y, 0);
		glRotatef(g_Rotate_R, 1.0, 0.0, 0.0);
		switch(g_Shage)
		{
		case SPHERE:
			glutWireSphere(50, 10, 10);
			break;
			
		case CUBE:
			glutWireCube(50);
			break;
			
		case CONE:
			glutWireCone(50, 50, 10, 10);
			break;

		case TEAPOT:
			glutWireTeapot(50);
			break;

		default:
			break;
		}
		glPopMatrix();
	}
	glPopMatrix();
	
	


	world->draw();
	
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
			
			switch(2)
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
		g_x--;
		break;
	case 'X':
		g_x++;
		break;
	case 'y':
		g_y--;
		break;
	case 'Y':
		g_y++;
		break;
	case 'z':
		g_z--;
		break;
	case 'Z':
		g_z++;
		break;
	case 'r':
		g_Rotate_R++;
		break;
	case 'l':
		g_Rotate_L++;
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
	case 101:
		world->allPlusVelocity();
		break;
	case 103:
		world->allMinorVelocity();
		break;
	}
	printf("%d\n", key);
}