#include "CallBackFunc.h"

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( WIDTH, HEIGHT );
	glutCreateWindow( "3-7.AnyObject" );
	glutDisplayFunc( drawScene );
	glutReshapeFunc( reshape );
	glutMouseFunc( mouse );
	//glutMotionFunc( mouseMove );
	glutKeyboardFunc( keyBoardFunc );
	glutSpecialFunc( specialKeyBoardFunc );
	glutTimerFunc( 600, timerFunc, 1 );
	glutMainLoop();
}

