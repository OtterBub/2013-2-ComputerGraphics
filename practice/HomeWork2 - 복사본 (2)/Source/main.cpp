#include "CallBackFunc.h"

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( WIDTH, HEIGHT );
	glutCreateWindow( "21.Curve" );
	glutDisplayFunc( drawScene );
	glutReshapeFunc( reshape );
	glutMouseFunc( mouse );
	glutMotionFunc( mouseMove );
	glutKeyboardFunc( keyBoardFunc );
	glutSpecialFunc( specialKeyBoardFunc );

	int CullingMenu, ViewModeMenu, WeatherMenu;
	int MainMenu;

	CullingMenu = glutCreateMenu( MenuFuntion );
	glutAddMenuEntry("On", 11);
	glutAddMenuEntry("Off", 22);

	ViewModeMenu = glutCreateMenu( MenuFuntion );
	glutAddMenuEntry("2D View Front", 1111);
	glutAddMenuEntry("3D View", 2222);

	WeatherMenu = glutCreateMenu( MenuFuntion );
	glutAddMenuEntry("SNOW", 1);
	glutAddMenuEntry("RAIN", 2);
	glutAddMenuEntry("SUNNY", 3);

	MainMenu = glutCreateMenu( MenuFuntion );

	glutAddSubMenu("Weather", WeatherMenu);
	glutAddSubMenu("Culling", CullingMenu);
	glutAddSubMenu("View Mode", ViewModeMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutTimerFunc( 600, timerFunc, 1 );

	glutMainLoop();
}

