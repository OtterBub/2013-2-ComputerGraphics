#include <stdio.h>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>

GLvoid drawScene( GLvoid );

GLvoid reshape( int w, int h );

void main(int argc, char *argv[])
{
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( 800, 600 );
	glutCreateWindow( "3-1.create_window" );
	glutDisplayFunc( drawScene );
	glutReshapeFunc( reshape );
	glutMainLoop();
}

GLvoid drawScene ( GLvoid )
{
	glClearColor( 1.0f, 0.0f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
	
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f );
	glBegin( GL_POLYGON );
    glVertex2f( -1.0, -1.0 );
    glVertex2f( -0.6, -1.0 );
    glVertex2f( -0.6, -0.6 );
	glVertex2f( -1.0, -0.6 );
	glEnd();

	glColor4f(0.0f, 1.0f, 1.0f, 1.0f );
	glBegin( GL_POLYGON );
    glVertex2f( -1.0, 1.0 );
    glVertex2f( -1.0, 0.6 );
    glVertex2f( -0.6, 0.6 );
	glVertex2f( -0.6, 1.0 );
	glEnd();

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f );
	glBegin( GL_POLYGON );
    glVertex2f( 1.0, 1.0 );
    glVertex2f( 0.6, 1.0 );
    glVertex2f( 0.6, 0.6 );
	glVertex2f( 1.0, 0.6 );
	glEnd();

	glColor4f(1.0f, 1.0f, 0.0f, 1.0f );
	glBegin( GL_POLYGON );
    glVertex2f( 1.0, -1.0 );
    glVertex2f( 1.0, -0.6 );
    glVertex2f( 0.6, -0.6 );
	glVertex2f( 0.6, -1.0 );
	glEnd();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f );
	glBegin( GL_POLYGON );
    glVertex2f( 0.2, 0.2 );
    glVertex2f( -0.2, 0.2 );
    glVertex2f( -0.2, -0.2 );
	glVertex2f( 0.2, -0.2 );
	glEnd();


	//glRectf( -0.5f, -0.5f, 0.5f, 0.5f );
	glFlush();
}

GLvoid reshape ( int w, int h )
{
	glViewport(0, 0, w, h);
}