#include "DrawSystem.h"

DrawSystem::DrawSystem()
{
}

DrawSystem::~DrawSystem()
{
}

bool DrawSystem::Init()
{
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( 800, 600 );
	glutCreateWindow( "OpenGL Frame" );
	glutDisplayFunc( DrawScene );
	glutReshapeFunc( Reshape );
	WORLD_INST->Init();

	return true;
}

bool DrawSystem::Run()
{
	glutMainLoop();
	return true;
} 

GLvoid DrawSystem::DrawScene( GLvoid )
{
	
	glClearColor( 1.0f, 0.0f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );

	WORLD_INST->Update();
	WORLD_INST->Draw();

	//glRectf( -0.5f, -0.5f, 0.5f, 0.5f );
	glutSwapBuffers();
}

GLvoid DrawSystem::Reshape( int w, int h )
{
	glViewport( 0, 0, w, h );
}