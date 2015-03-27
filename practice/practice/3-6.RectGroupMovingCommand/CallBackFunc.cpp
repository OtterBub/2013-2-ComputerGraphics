#include "CallBackFunc.h"

std::vector<Object*> obj;

GLvoid drawScene ( GLvoid )
{
	glClearColor( 0.0f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );

	static bool init = 0;

	if(init == 0) {
		init = 1;
		RectObject* temp = new RectObject( 400, 300, 50 );
		temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
		temp->setRescaleAnimation(rand() % 2, 3.0f, 0.5f);
		//temp->setVelocity(true, rand() % 10, rand() % 10);
		obj.push_back(temp);
	}

	for(auto it = obj.begin(); it != obj.end(); it++) {	
		(*it)->draw();		
	}

	glFlush();
}

GLvoid reshape ( int w, int h )
{
	glViewport(0, 0, w, h);
	glOrtho(0, w, 0, h, -1.0, 1.0);

	for(auto it = obj.begin(); it != obj.end(); it++) {
		(*it)->draw();		
	}
}

GLvoid mouse(int button, int state, int x, int y)
{
	int r_y = HEIGHT - y;
	printf("mouse x : %d, y : %d\n", x, y);

	if(state == GLUT_DOWN) {
		switch (button)	{
		case GLUT_LEFT_BUTTON: {
				RectObject* temp = new RectObject( x, r_y, 10 + rand() % 30, 10 + rand() % 30 );
				temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
				temp->setRescaleAnimation(rand() % 2, 3.0f, 0.5f);
				temp->setVelocity(true, rand() % 10, rand() % 10);
				obj.push_back(temp);
			}
			break;

		case GLUT_RIGHT_BUTTON: {
				for(auto it = obj.begin(); it != obj.end(); it++) {
					(*it)->moveToPoint(x, r_y);
				}
			} break;		

		default:
			break;
		}
	}
}

GLvoid mouseMove(int x, int y)
{
	int r_y = HEIGHT - y;
	RectObject* temp = new RectObject( x, r_y, 20 );
	temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
	temp->setRescaleAnimation(rand() % 2, 3.0f, 0.5f);
	//temp->setVelocity(true, rand() % 10, rand() % 10);
	obj.push_back(temp);
}

GLvoid keyBoard(unsigned char key, int x, int y)
{
	
}

GLvoid timerFunc(int val)
{
	glutPostRedisplay();
	glutTimerFunc( 16, timerFunc, 1 );
}

GLvoid keyBoardFunc(int key, int x, int y)
{
	// left : 100 / up : 101 / right : 102 / down : 103
	switch(key)
	{
	case 101:
		for( auto it = obj.begin(); it != obj.end(); it++) {
			(*it)->plusVelocity();
		}	
		break;
	case 103:
		for( auto it = obj.begin(); it != obj.end(); it++) {
			(*it)->MinorVelocity();
		}	
		break;
	}
	printf("%d\n", key);
}