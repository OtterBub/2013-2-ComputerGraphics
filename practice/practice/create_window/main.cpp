#include <stdio.h>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#define HEIGHT 600
#define WIDTH 800

GLvoid drawScene( GLvoid );
GLvoid reshape( int w, int h );

void main(int argc, char *argv[])
{
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( WIDTH, HEIGHT );
	glutCreateWindow( "3-2.CheckPattern" );
	glutDisplayFunc( drawScene );
	glutReshapeFunc( reshape );
	glutMainLoop();
}

GLvoid drawScene ( GLvoid )
{
	glClearColor( 1.0f, 0.0f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
	
	GLdouble div_w = 100, div_h = 7;
	GLdouble rect_w = WIDTH / div_w;
	GLdouble rect_h = HEIGHT / div_h;

	for(int i = 0; i < div_h; i++){
		for(int j = 0; j < div_w; j++){
			if((i + j) % 2)
				glColor4f(1.0f, 0.0f, 0.0f, 1.0f );
			else
				glColor4f(0.0f, 1.0f, 0.0f, 1.0f );
			glBegin( GL_POLYGON );
			glVertex2d( 0 + (rect_w * j) , 0 + (rect_h * i) );
			glVertex2d( 0 + (rect_w * j), rect_h + (rect_h * i) );
			glVertex2d( rect_w + (rect_w * j), rect_h + (rect_h * i) );
			glVertex2d( rect_w + (rect_w * j), 0 + (rect_h * i) );
			glEnd();
		}
	}
	

	//glRectf( -0.5f, -0.5f, 0.5f, 0.5f );
	glFlush();
}

GLvoid reshape ( int w, int h )
{
	glViewport(0, 0, w, h);
	glOrtho(0, w, 0, h, -1.0, 1.0);

}