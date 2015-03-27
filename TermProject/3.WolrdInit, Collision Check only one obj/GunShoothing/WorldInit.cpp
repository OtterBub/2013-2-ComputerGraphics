#include "WorldInit.h"

void initStage1() {
	if(GLOBAL.g_init)
		return;
	GLOBAL.g_init = true;

	float fGroundSize = 200;
	float fGroundHalfSize = fGroundSize / 2;

	TKpoint setPos;
	setPos.x = 0;
	setPos.y = -1;
	setPos.z = 0;

	Object* temp;

	temp = WORLD.addObejct(new Ground(setPos));
	dynamic_cast<Ground*>(temp)->setGroundSize(fGroundSize);

	setPos.x = fGroundSize;
	setPos.y = 0;
	setPos.z = 0;

	temp = WORLD.addObejct(new Wall(setPos));
	dynamic_cast<Wall*>(temp)->setWallSize(200);
	temp->setRotate(0, 90, 0);


	setPos.x = -100;
	setPos.y = 0;
	setPos.z = -50;

	WORLD.addObejct(new Target(setPos));

	setPos.x = -100;
	setPos.y = 0;
	setPos.z = -100;

	WORLD.addObejct(new Target(setPos));

	setPos.x = 20;
	setPos.y = 0;
	setPos.z = -100;

	WORLD.addObejct(new Target(setPos));

	setPos.x = 20;
	setPos.y = 0;
	setPos.z = 0;

	WORLD.addObejct(new Pillar(setPos));

	setPos.x = -100;
	setPos.y = 0;
	setPos.z = 0;

	WORLD.addObejct(new Pillar(setPos));
	
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


void init()
{
	if(GLOBAL.g_init)
		return;
	GLOBAL.g_init = true;

	float fGroundSize = 200;
	float fGroundHalfSize = fGroundSize / 2;

	TKpoint setPos;
	setPos.x = 0;
	setPos.y = -1;
	setPos.z = 0;

	Object* temp;

	temp = WORLD.addObejct(new Ground(setPos));
	dynamic_cast<Ground*>(temp)->setGroundSize(fGroundSize);

	setPos.x = fGroundSize;
	setPos.y = 0;
	setPos.z = 0;

	temp = WORLD.addObejct(new Wall(setPos));
	dynamic_cast<Wall*>(temp)->setWallSize(200);
	temp->setRotate(0, 90, 0);
	
	setPos.x = -100;
	setPos.y = 0;
	setPos.z = 0;

	WORLD.addObejct(new Target(setPos));

	setPos.x = -100;
	setPos.y = 0;
	setPos.z = -50;

	WORLD.addObejct(new Target(setPos));

	setPos.x = -100;
	setPos.y = 0;
	setPos.z = -100;

	WORLD.addObejct(new Target(setPos));

	setPos.x = 20;
	setPos.y = 0;
	setPos.z = 0;

	WORLD.addObejct(new Pillar(setPos));
	
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