#ifndef __CALLBACKFUC_H__
#define __CALLBACKFUC_H__

#include <iostream>
#include <vector>

#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <cstdlib>
#include <ctime>

#include "Object.h"

#define HEIGHT 600
#define WIDTH 800

std::vector<Object*> obj;

GLvoid drawScene( GLvoid );
GLvoid reshape( int w, int h );
GLvoid mouse(int button, int state, int x, int y);

GLvoid drawScene ( GLvoid )
{
	glClearColor( 0.0f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );

	static bool init = 0;

	if(init == 0){
		init = 1;
		obj.push_back(new RectObject( 100, 100 + (rand() % 500), 100 ));
		for(auto it = obj.begin(); it != obj.end(); it++)
			(*it)->setColor( 1.0f, 1.0f, 0.0f, 1.0f);
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
		(*it)->setRescaleAnimation(true, 2.0f, 0.3f);
		(*it)->draw();		
	}
}

GLvoid mouse(int button, int state, int x, int y)
{
	int r_y = HEIGHT - y;
	printf("mouse x : %d, y : %d\n", x, y);
	if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)){
		obj.push_back(new RectObject( x, r_y, 20 ));
		std::vector<Object*>::reverse_iterator it = obj.rbegin();
		(*it)->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
		(*it)->setRescaleAnimation(rand() % 2, 3.0f, 0.5f);
	}
}

GLvoid timerFunc(int val)
{
	for(auto it = obj.begin(); it != obj.end(); it++)
	{
		if((*it)->getX() > WIDTH){
			(*it)->setPosition(0, (rand() % 600));
			(*it)->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
		}
		(*it)->setPosition((*it)->getX() + 1, (*it)->getY());
	}
	glutPostRedisplay();
	glutTimerFunc( 16, timerFunc, 1 );
}
#endif //__CALLBACKFUC_H__