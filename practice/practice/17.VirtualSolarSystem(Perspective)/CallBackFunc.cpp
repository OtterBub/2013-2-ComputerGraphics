#include "CallBackFunc.h"

#define SPHERE 0
#define CUBE 1
#define CONE 2
#define TEAPOT 3

#define GROUND_SIZE 300.0f

World* world = new World();
int g_Shage = 0; // Wire
int g_x = 30;
int g_y;
int g_z;
int g_Rotate_R;
int g_Rotate_L;

double g_eye_x = 300, g_eye_y= 400, g_eye_z = 500;
double g_camera_x, g_camera_y, g_camera_z;
double g_up_x, g_up_y, g_up_z;

GLvoid drawScene ( GLvoid )
{
	glClearColor( 0.0f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	

	gluLookAt(g_eye_x, g_eye_y, g_eye_z,
		g_camera_x, g_camera_y, g_camera_z,
		0.0, 1.0, 0.0);

	// Global View;
	glTranslatef( WIDTH/2, HEIGHT/2, 0.0f );
	glRotatef(g_x, 1.0, 0.0, 0.0);
	glRotatef(g_y, 0.0, 1.0, 0.0);
	glRotatef(g_z, 0.0, 0.0, 1.0);

	
	glPushMatrix();
	{
		glTranslated(g_camera_x, g_camera_y, g_camera_z);
		glutWireCube(30);
	}
	glPopMatrix();
	

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

	glColor3f(0.5, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-GROUND_SIZE, 0.0, -GROUND_SIZE);
	glVertex3f(GROUND_SIZE, 0.0, -GROUND_SIZE);
	glVertex3f(GROUND_SIZE, 0.0, GROUND_SIZE);
	glVertex3f(-GROUND_SIZE, 0.0, GROUND_SIZE);
	glEnd();

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

	glColor3f(1.0, 0.0, 0.0);
	glutWireSphere(80, 10, 10);


	glPushMatrix();
	{
		glPushMatrix();
		{
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINE_LOOP);
			float satellitedegreeMul = 360 / ((float)48);
			for(int i = 0; i < 48; i++){
				float x;
				float y;
				x = cos(((i*satellitedegreeMul)) * 3.14/180) * ( 200 );
				y = -sin(((i*satellitedegreeMul)) * 3.14/180) * ( 200 );
				glVertex3f(x, y, 0.0);
			}
			glEnd();
			static int satellite_1 = 0;
			satellite_1++;
			glRotated(satellite_1, 0.0, 0.0, 1.0);
			glTranslatef(200, 0.0, 0.0);		
			glColor3f(1.0, 0.0, 1.0);
			glutWireSphere(50, 10, 10);

			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINE_LOOP);
			float degreeMul = 360 / ((float)48);
			for(int i = 0; i < 48; i++){
				float x;
				float y;
				x = cos(((i*degreeMul)) * 3.14/180) * ( 80 );
				y = -sin(((i*degreeMul)) * 3.14/180) * ( 80 );
				glVertex3f(x, y, 0.0);
			}
			glEnd();

			glPushMatrix();
			{
				glRotated(satellite_1, 0.0, 0.0, 1.0);
				glTranslatef(80, 0.0, 0.0);
				glColor3f(0.0, 1.0, 1.0);
				glutWireSphere(20, 10, 10);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glPushMatrix();
		{
			glRotated(45, 0.0, 1.0, 0.0);
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINE_LOOP);
			float satellitedegreeMul = 360 / ((float)48);
			for(int i = 0; i < 48; i++){
				float x;
				float y;
				x = cos(((i*satellitedegreeMul)) * 3.14/180) * ( 200 );
				y = -sin(((i*satellitedegreeMul)) * 3.14/180) * ( 200 );
				glVertex3f(x, y, 0.0);
			}
			glEnd();
			static int satellite_1 = 0;
			satellite_1+=2;
			glRotated(satellite_1, 0.0, 0.0, 1.0);
			glTranslatef(200, 0.0, 0.0);		
			glColor3f(1.0, 0.0, 1.0);
			glutWireSphere(50, 10, 10);

			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINE_LOOP);
			float degreeMul = 360 / ((float)48);
			for(int i = 0; i < 48; i++){
				float x;
				float y;
				x = cos(((i*degreeMul)) * 3.14/180) * ( 80 );
				y = -sin(((i*degreeMul)) * 3.14/180) * ( 80 );
				glVertex3f(x, y, 0.0);
			}
			glEnd();

			glPushMatrix();
			{
				glRotated(satellite_1, 0.0, 0.0, 1.0);
				glTranslatef(80, 0.0, 0.0);
				glColor3f(0.0, 1.0, 1.0);
				glutWireSphere(20, 10, 10);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glPushMatrix();
		{
			glRotated(-45, 0.0, 1.0, 0.0);
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINE_LOOP);
			float satellitedegreeMul = 360 / ((float)48);
			for(int i = 0; i < 48; i++){
				float x;
				float y;
				x = cos(((i*satellitedegreeMul)) * 3.14/180) * ( 200 );
				y = -sin(((i*satellitedegreeMul)) * 3.14/180) * ( 200 );
				glVertex3f(x, y, 0.0);
			}
			glEnd();
			static int satellite_1 = 0;
			satellite_1+=3;
			glRotated(satellite_1, 0.0, 0.0, 1.0);
			glTranslatef(200, 0.0, 0.0);		
			glColor3f(1.0, 0.0, 1.0);
			glutWireSphere(50, 10, 10);

			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINE_LOOP);
			float degreeMul = 360 / ((float)48);
			for(int i = 0; i < 48; i++){
				float x;
				float y;
				x = cos(((i*degreeMul)) * 3.14/180) * ( 80 );
				y = -sin(((i*degreeMul)) * 3.14/180) * ( 80 );
				glVertex3f(x, y, 0.0);
			}
			glEnd();

			glPushMatrix();
			{
				glRotated(satellite_1, 0.0, 0.0, 1.0);
				glTranslatef(80, 0.0, 0.0);
				glColor3f(0.0, 1.0, 1.0);
				glutWireSphere(20, 10, 10);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();


	glLoadIdentity();
	glutSwapBuffers();
}

GLvoid reshape ( int w, int h )
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(0, w, 0, h, -h, h);
	gluPerspective(60, w/h, 0, 300);
	gluLookAt(300.0, 400.0, 500.0,
	w/2, h/2, 0.0,
	0.0, 1.0, 0.0);

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
	case 'a':
		g_eye_x -= 5;
		break;
	case 'd':
		g_eye_x += 5;
		break;
	case 'w':
		g_eye_z -= 5;
		break;
	case 's':
		g_eye_z += 5;
		break;
	case 'r':
		g_eye_y += 5;
		break;
	case 'f':
		g_eye_y -= 5;
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
	// page up : 104 / page down : 105
	switch(key)
	{
	case 100:
		g_camera_x -= 5;
		break;
	case 102:
		g_camera_x += 5;
		break;
	case 101:
		g_camera_z -= 5;
		break;
	case 103:
		g_camera_z += 5;
		break;
	case 104:
		g_camera_y += 5;
		break;
	case 105:
		g_camera_y -= 5;
		break;
	}
	printf("%d\n", key);
}