#include "CallBackFunc.h"

std::vector<Object*> obj;

GLvoid drawScene ( GLvoid )
{
	glClearColor( 0.0f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );

	static bool init = 0;

	if(init == 0){
		init = 1;
		RectObject* temp = new RectObject( 400, 300, 50 );
		temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
		temp->setRescaleAnimation(rand() % 2, 3.0f, 0.5f);
		temp->setVelocity(true, rand() % 10, rand() % 10);
		obj.push_back(temp);
	}

	for(auto it = obj.begin(); it != obj.end(); it++)
	{	
		(*it)->draw();		
	}

	glFlush();
}

GLvoid reshape ( int w, int h )
{
	glViewport(0, 0, w, h);
	glOrtho(0, w, 0, h, -1.0, 1.0);

	for(auto it = obj.begin(); it != obj.end(); it++)
	{
		(*it)->draw();		
	}
}

GLvoid mouse(int button, int state, int x, int y)
{
	int r_y = HEIGHT - y;
	printf("mouse x : %d, y : %d\n", x, y);
	if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)){
		RectObject* temp = new RectObject( x, r_y, 20 );
		temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f);
		temp->setRescaleAnimation(rand() % 2, 1.0 + ((double)rand() / RAND_MAX) + (rand() % 4), 0.1f + (double)rand() / RAND_MAX);
		temp->setVelocity(true, rand() % 5, rand() % 5);
		obj.push_back(temp);
	}
}

GLvoid mouseMove(int x, int y)
{
	int r_y = HEIGHT - y;
	RectObject* temp = new RectObject( x, r_y, 20 );
	temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
	temp->setRescaleAnimation(rand() % 2, 1.0 + ((double)rand() / RAND_MAX) + (rand() % 4), 0.1f + (double)rand() / RAND_MAX);
	temp->setVelocity(true, 1 + rand() % 3, 1 + rand() % 3);
	obj.push_back(temp);
}

GLvoid timerFunc(int val)
{
	glutPostRedisplay();
	glutTimerFunc( 16, timerFunc, 1 );
}