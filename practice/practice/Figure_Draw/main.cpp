#include <iostream>
#include <vector>

#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <cstdlib>
#include <ctime>

#define HEIGHT 600
#define WIDTH 800

class DrawDisplay{
private:
	GLdouble m_x;
	GLdouble m_y;
	GLdouble m_w;
	GLdouble m_h;

	GLfloat m_R;
	GLfloat m_G;
	GLfloat m_B;
	GLfloat m_A;

	GLint m_shape;

	bool m_set_Color;

public:
	DrawDisplay(GLdouble x, GLdouble y, GLdouble w, GLdouble h) : m_x(x), m_y(y), m_w(w), m_h(h), m_set_Color(false) {};
	void setColor(GLfloat R, GLfloat G, GLfloat B, GLfloat A) { m_R = R; m_G = G; m_B = B; m_A = A; m_set_Color = true;};
	
	void setPosition(GLdouble x, GLdouble y) { m_x = x; m_y = y; }
	
	void drawRect(){
		if(m_set_Color)
			glColor4f(m_R, m_G, m_B, m_A);
		glBegin( GL_POLYGON );
		glVertex2d( m_x, m_y);
		glVertex2d( m_x, m_y + m_h );
		glVertex2d( m_x + m_w, m_y + m_h );
		glVertex2d( m_x + m_w, m_y );
		glEnd();
	}

	void drawShape(GLint num){
		m_shape = num;

		if(m_set_Color)
			glColor4f(1.0f - m_R, 1.0f -  m_G, 1.0f -  m_B, m_A);

		switch(m_shape)
		{
		case 0:
			glBegin( GL_LINES );
			glVertex2d( m_x + rand() % (int)m_w, m_y + rand() % (int)m_h );
			glVertex2d( m_x + rand() % (int)m_w, m_y + rand() % (int)m_h );
			glEnd();
			break;
		case 1:
			glBegin( GL_POLYGON );
			glVertex2d( m_x + rand() % (int)m_w, m_y + rand() % (int)m_h );
			glVertex2d( m_x + rand() % (int)m_w, m_y + rand() % (int)m_h );
			glVertex2d( m_x + rand() % (int)m_w, m_y + rand() % (int)m_h );
			glEnd();
			break;
		case 2:
			glBegin( GL_POLYGON );
			glVertex2d( m_x + rand() % (int)m_w/2, m_y + rand() % (int)m_h/2 );
			glVertex2d( m_x + m_w/2 + rand() % (int)m_w/2, m_y + rand() % (int)m_h/2 );
			glVertex2d( m_x + m_w/2 + rand() % (int)m_w/2, m_y + m_h/2 + rand() % (int)m_h/2 );
			glVertex2d( m_x + rand() % (int)m_w/2, m_y + m_h/2 + rand() % (int)m_h/2 );
			glEnd();
			break;
		case 3:
			glBegin( GL_POLYGON );
			glVertex2d( m_x + rand() % (int)m_w/2, m_y + rand() % (int)m_h/2 );
			glVertex2d( m_x + m_w/2 + rand() % (int)m_w/2, m_y + rand() % (int)m_h/2 );
			glVertex2d( m_x + (m_w*2/3) + rand() % (int)m_w/3, m_y + m_h/2 + rand() % (int)m_h/2 );
			glVertex2d( m_x + m_w/3 + rand() % (int)m_w/3, m_y + m_h/2 + rand() % (int)m_h/2 );
			glVertex2d( m_x + rand() % (int)m_w/3, m_y + m_h/2 + rand() % (int)m_h/2 );
			glEnd();
			break;
		default:
			break;
		}

	}
};

GLvoid drawScene( GLvoid );
GLvoid reshape( int w, int h );

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( WIDTH, HEIGHT );
	glutCreateWindow( "3-3.Draw_Figure" );
	glutDisplayFunc( drawScene );
	glutReshapeFunc( reshape );
	glutMainLoop();
}

GLvoid drawScene ( GLvoid )
{
	glClearColor( 1.0f, 0.0f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
	
	GLdouble div = 13;
	GLdouble rect_w = WIDTH / div;
	GLdouble rect_h = HEIGHT / div;

	std::vector<DrawDisplay*> display;

	for(int i = 0; i < div; i++){
		for(int j = 0; j < div; j++){
			display.push_back(new DrawDisplay(rect_w * j, rect_h * i, rect_w, rect_h));
		}
	}

	for(auto it = display.begin(); it != display.end(); it++){
		static int i = 0;
		if(i = (i++) % 2)
			(*it)->setColor( 0.0f, 1.0f, 1.0f, 1.0f );
		else
			(*it)->setColor( 1.0f, 1.0f, 0.0f, 1.0f );
		(*it)->drawRect();
		(*it)->drawShape(rand() % 4);
	}
	
	glFlush();
}

GLvoid reshape ( int w, int h )
{
	glViewport(0, 0, w, h);
	glOrtho(0, w, 0, h, -1.0, 1.0);
}