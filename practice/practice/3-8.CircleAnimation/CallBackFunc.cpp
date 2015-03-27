#include "CallBackFunc.h"

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
		temp->setRescaleAnimation(rand() % 2, 3.0f, 0.5f);
		//temp->setVelocity(true, rand() % 10, rand() % 10);

		world->addObject(temp);

		int width = 200;
		int height = 120;

		for(int i = 0; i < 20; i++){
			point[(i * 2)] = (i * 40) + (rand() % 40);
			point[(i * 2)+1] = rand() % 600;
		}
	}

	if(g_shape == GL_POLYGON){		
		for(int i = 0; i < 6; i++){
			glBegin(g_shape);
			glVertex2f(point[(i * 10)], point[(i * 10) + 1]);
			glVertex2f(point[(i * 10) + 2], point[(i * 10) + 3]);
			glVertex2f(point[(i * 10) + 4], point[(i * 10) + 5]);
			glVertex2f(point[(i * 10) + 6], point[(i * 10) + 7]);
			glVertex2f(point[(i * 10) + 8], point[(i * 10) + 9]);
			glEnd();
		}		
	}
	else{
		glBegin(g_shape);
		for(int i = 0; i < 20; i++){
			glVertex2f(point[(i * 2)], point[(i * 2) + 1]);
		}
		glEnd();
	}
	

	world->draw();

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
			
			switch(rand() % 2)
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
					temp->setRescaleAnimation(rand() % 2, 10.0f, 0.5f);
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
	case 'l':
	case 'L':
		g_shape = GL_LINES;
		break;
	case 's':
	case 'S':
		g_shape = GL_LINE_STRIP;
		break;
	case 'o':
	case 'O':
		g_shape = GL_LINE_LOOP;
		break;
	case 't':
	case 'T':
		g_shape = GL_TRIANGLES;
		break;
	case 'p':
	case 'P':
		g_shape = GL_TRIANGLE_STRIP;
		break;
	case 'f':
	case 'F':
		g_shape = GL_TRIANGLE_FAN;
		break;
	case 'q':
	case 'Q':
		g_shape = GL_QUADS;
		break;
	case 'u':
	case 'U':
		g_shape = GL_QUAD_STRIP;
		break;
	case 'n':
	case 'N':
		g_shape = GL_POLYGON;
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