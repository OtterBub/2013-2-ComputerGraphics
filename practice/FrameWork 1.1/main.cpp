#include "CallBackFunction.h"

int main()
{
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize(800, 600);
	glutCreateWindow("Fractal");

	glutMouseFunc( mouseFunc );
	glutMotionFunc( mouseMove );

	glutDisplayFunc( drawScene );
	glutReshapeFunc( reShape );

	glutTimerFunc( 16, timerFunc, 0 );

	glutMainLoop();

	return 0;
}