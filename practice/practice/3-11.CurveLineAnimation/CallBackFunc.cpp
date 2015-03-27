#include "CallBackFunc.h"

#define TRIANGLE	0
#define RECTANGLE	1

World* world = new World();
int g_shape = 0;

GLvoid drawScene ( GLvoid )
{
	glClearColor( 0.0f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	static bool init = 0;
	static GLfloat point[40];

	if(init == 0) {
		init = 1;
		Object* temp = new RectObject( 400, 300, 50 );
		temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
		temp->setRescaleAnimation(true, 3.0f, 0.5f);
		//temp->setVelocity(true, rand() % 10, rand() % 10);
		world->addObject(temp);
	}

	{

		glPushMatrix();
		glTranslatef( WIDTH/2, HEIGHT/2, 0.0f );
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		float degreeMul = 360 / ((float)48);
		for(int i = 0; i < 48; i++){
			float x;
			float y;
			x = cos(((i*degreeMul)) * 3.14/180) * ( 200 );
			y = -sin(((i*degreeMul)) * 3.14/180) * ( 200 );
			glVertex2f(x, y);
		}
		glEnd();

		static float angular_variation = 0;
		static float scale_variation = 1;
		static bool scale_plus = true;

		angular_variation += 0.5;

		if(scale_plus){
			scale_variation += 0.05;
		} else {
			scale_variation -= 0.05;
		}

		if(scale_variation > 2.0f)
			scale_plus = false;
		else if(scale_variation < 0.5f)
			scale_plus = true;

		glRotatef( angular_variation, 0.0, 0.0, 1.0);

		glTranslatef( 200, 0.0, 0.0f );
		glScalef( scale_variation, scale_variation, 1.0f );

		switch(g_shape)
		{
		case RECTANGLE:
			glBegin(GL_POLYGON);
			glVertex2f(-25, -50);
			glVertex2f(25, -50);
			glVertex2f(25, 0);
			glVertex2f(-25, 0);
			glEnd();
			break;
		case TRIANGLE:
			glBegin(GL_POLYGON);
			glVertex2f(-25, -50);
			glVertex2f(25, -50);
			glVertex2f(0, 0);
			glEnd();
			break;
		default:
			break;
		}
		

		glPopMatrix();
	}
	
	

	world->draw();
	
	glLoadIdentity();
	glutSwapBuffers();
}

GLvoid reshape ( int w, int h )
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, w, 0, h, -1.0, 1.0);

	/*gluLookAt(0.0, 0.0, 0.0,
		0.0, 0.0, 1.0,
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
	case 'S':
	case 's':
		if(g_shape == TRIANGLE)
			g_shape = RECTANGLE;
		else
			g_shape = TRIANGLE;
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