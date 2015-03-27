#include "CallBackFunction.h"

TKpoint g_eye = {0, };
TKpoint g_center = {0, };
TKpoint g_angle = {0, };

bool g_init = false;

// -------------- INIT ---------------
void init()
{
	if(g_init)
		return;
	g_init = true;

	g_eye.x;
	g_eye.y = 100;
	g_eye.z = 500;

	g_center.x;
	g_center.y;
	g_center.z;

	float fGroundSize = 200;
	float fGroundHalfSize = fGroundSize / 2;

	TKpoint setPos;
	setPos.x = 0;
	setPos.y = -1;
	setPos.z = 0;

	Object* temp;

	temp = WORLD.addObejct(new Ground(setPos));
	dynamic_cast<Ground*>(temp)->setGroundSize(fGroundSize);

	setPos.x = -fGroundHalfSize;
	setPos.y = 50;
	setPos.z = -fGroundHalfSize;

	WORLD.addBlendObejct(new MiracleCube(setPos));

	setPos.x = -fGroundHalfSize;
	setPos.y = 0;
	setPos.z = fGroundHalfSize;

	WORLD.addObejct(new Kid(setPos));

	setPos.x = fGroundHalfSize;
	setPos.y = 100;
	setPos.z = -fGroundHalfSize;

	WORLD.addObejct(new Hammock(setPos));

	setPos.x = fGroundHalfSize;
	setPos.y = 0;
	setPos.z = fGroundHalfSize;

	WORLD.addObejct(new Pond(setPos));

	setPos.x = 0;
	setPos.y = 0;
	setPos.z = -fGroundSize;

	temp = WORLD.addObejct(new Wall(setPos));
	dynamic_cast<Wall*>(temp)->setWallSize(200);
	
	char* fileName[1] = {"stone-wall.bmp"};

	temp->addTexture(fileName, 1);
	

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat position[4];

	position[0] = 0;
	position[1] = 0;
	position[2] = 100;
	position[3] = 0;

	glLightfv(GL_LIGHT0, GL_POSITION, position);

	GLfloat color[4];

	color[0] = 1;
	color[1] = 1;
	color[2] = 1;
	color[3] = 1;

	glLightfv(GL_LIGHT0, GL_SPECULAR, color);

	color[0] = 1;
	color[1] = 1;
	color[2] = 1;
	color[3] = 1;

	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);

	color[0] = 1;
	color[1] = 1;
	color[2] = 1;
	color[3] = 1;

	glLightfv(GL_LIGHT0, GL_AMBIENT, color);

	glEnable(GL_COLOR_MATERIAL);
	GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 30);
}

void drawScene()
{
	glClearColor( 0.5, 0.5, 0.5, 1);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	init();

	// Gloval View
	gluLookAt(g_eye.x, g_eye.y, g_eye.z
		, g_center.x, g_center.y, g_center.z
		, 0, 1, 0);
	glRotatef(g_angle.x, 1, 0, 0);
	glRotatef(g_angle.y, 0, 1, 0);
	glRotatef(g_angle.z, 0, 0, 1);
	
	WORLD.draw();

	glLoadIdentity();
	glutSwapBuffers();
}

void reShape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, w/h, 1.0, 2000.0f);

	glMatrixMode(GL_MODELVIEW);	
}

void timerFunc(int value)
{
	WORLD.update();
	glutPostRedisplay();
	glutTimerFunc( 16, timerFunc, 0 );
}