#include "CallBackFunc.h"

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( WIDTH, HEIGHT );
	glutCreateWindow( "3-9.Curve" );
	glutDisplayFunc( drawScene );
	glutReshapeFunc( reshape );
	glutMouseFunc( mouse );
	//glutMotionFunc( mouseMove );
	glutKeyboardFunc( keyBoardFunc );
	glutSpecialFunc( specialKeyBoardFunc );
	glutTimerFunc( 600, timerFunc, 1 );

	glutMainLoop();
}

