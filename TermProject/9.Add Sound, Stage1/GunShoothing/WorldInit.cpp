#include "WorldInit.h"


// ------- TEST STAGE ----------

void initParticleTest() {
	if(GLOBAL.g_init)
		return;
	GLOBAL.g_init = true;

	float fGroundSize = 300;
	float fGroundHalfSize = fGroundSize / 2;

	TKpoint setPos;
	setPos.x = 0;
	setPos.y = -1;
	setPos.z = 0;

	Object* temp;

	temp = WORLD.addObejct(new Ground(setPos));
	dynamic_cast<Ground*>(temp)->setGroundSize(fGroundSize);

	setPos.y = 50;
	for(int i = 0; i < 20; i++)
		WORLD.addObejct(new Particle(setPos));

	CAMERA.removeAllNode();

	TKpoint setCameraPos;

	setCameraPos.x = 0;
	setCameraPos.y = 60;
	setCameraPos.z = 300;

	CAMERA.setEyePos(setCameraPos);

	setCameraPos.x = 0;
	setCameraPos.y = 60;
	setCameraPos.z = 0;

	CAMERA.setCenterPos(setCameraPos);
}

void initCameraTest() {
	if(GLOBAL.g_init)
		return;
	GLOBAL.g_init = true;

	float fGroundSize = 300;
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
	temp->setRotate(0, -90, 0);

	setPos.x = -fGroundSize;
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

	temp = WORLD.addObejct(new Target(setPos));

	setPos.x = 100;
	setPos.y = 20;
	setPos.z = -50;

	dynamic_cast<Target*>(temp)->set_end_position(setPos);

	setPos.x = -100;
	setPos.y = 0;
	setPos.z = -100;

	temp = WORLD.addObejct(new Target(setPos));

	setPos.x = 50;
	setPos.y = 20;
	setPos.z = -125;

	dynamic_cast<Target*>(temp)->set_end_position(setPos);

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

	CAMERA.removeAllNode();

	TKpoint setCameraPos;

	setCameraPos.x = 0;
	setCameraPos.y = 60;
	setCameraPos.z = 300;

	CAMERA.setEyePos(setCameraPos);

	setCameraPos.x = 0;
	setCameraPos.y = 60;
	setCameraPos.z = 0;

	CAMERA.setCenterPos(setCameraPos);
	

	setCameraPos.x = 150;
	setCameraPos.y = 60;
	setCameraPos.z = 300;

	CAMERA.addCameraNode(setCameraPos, false, true);

	setCameraPos.z += -300;

	CAMERA.addCameraNode(setCameraPos, true, true);

	setCameraPos.x -= 5;

	CAMERA.addCameraNode(setCameraPos, true, true);

	setCameraPos.x += 5;

	CAMERA.addCameraNode(setCameraPos, false, true);

	setCameraPos.z -= 100;

	CAMERA.addCameraNode(setCameraPos, false, true, 2500);

	setCameraPos.x += 150;

	CAMERA.addCameraNode(setCameraPos, false, true, 1000);

	setCameraPos.x -= 30;
	setCameraPos.z += 5;

	CAMERA.addCameraNode(setCameraPos, true, true, 1000);
}

void initTest() {
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

	CAMERA.removeAllNode();

	TKpoint setCameraPos;

	setCameraPos.x = 0;
	setCameraPos.y = 30;
	setCameraPos.z = 300;

	CAMERA.setEyePos(setCameraPos);

	setCameraPos.x = 0;
	setCameraPos.y = 30;
	setCameraPos.z = 0;

	CAMERA.setCenterPos(setCameraPos);
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

	CAMERA.removeAllNode();

	TKpoint setCameraPos;

	setCameraPos.x = 0;
	setCameraPos.y = 30;
	setCameraPos.z = 300;

	CAMERA.setEyePos(setCameraPos);

	setCameraPos.x = 0;
	setCameraPos.y = 30;
	setCameraPos.z = 0;

	CAMERA.setCenterPos(setCameraPos);
}

// ------------ GAME STAGE 1 INIT --------------

void initStage1() 
{
	if(GLOBAL.g_init)
		return;
	GLOBAL.g_init = true;

	float fGroundSize = 1000;
	float fGroundHalfSize = fGroundSize / 2;

	TKpoint setPos;
	setPos.x = 0;
	setPos.y = -1;
	setPos.z = 0;

	Object* temp;

	temp = WORLD.addObejct(new Ground(setPos));
	dynamic_cast<Ground*>(temp)->setGroundSize(fGroundSize);

	setPos.x = 555;
	setPos.y = 0;
	setPos.z = 980;

	temp = WORLD.addObejct(new Wall(setPos));
	dynamic_cast<Wall*>(temp)->setWallSize(200);
	temp->setRotate(0, -90, 0);

	for(int i = 0; i < 5; i++){

		setPos.z -= 400;

		temp = WORLD.addObejct(new Wall(setPos));
		dynamic_cast<Wall*>(temp)->setWallSize(200);
		temp->setRotate(0, -90, 0);
	}	

	setPos.x = -555;
	setPos.y = 0;
	setPos.z = 980;

	temp = WORLD.addObejct(new Wall(setPos));
	dynamic_cast<Wall*>(temp)->setWallSize(200);
	temp->setRotate(0, 90, 0);

	for(int i = 0; i < 5; i++){


		setPos.z -= 400;

		temp = WORLD.addObejct(new Wall(setPos));
		dynamic_cast<Wall*>(temp)->setWallSize(200);
		temp->setRotate(0, 90, 0);
	}

	setPos.x = 20;
	setPos.y = 0;
	setPos.z = 0;

	WORLD.addObejct(new Pillar(setPos));

	setPos.x = -340;
	setPos.y = 0;
	setPos.z = 415;

	WORLD.addObejct(new Pillar(setPos));

	setPos.x = 140;
	setPos.y = 0;
	setPos.z = 450;

	WORLD.addObejct(new Pillar(setPos));

	for(int i = 0; i < 10; i++) {
		setPos.x += 60;

		WORLD.addObejct(new Pillar(setPos));
	}

	setPos.x = 80;
	setPos.y = 0;
	setPos.z = 800;

	WORLD.addObejct(new IronBarrel(setPos));

	for(int i = 0 ; i < 10; i++) {

		setPos.x += 40;
		setPos.y = 0;
		setPos.z = 800;

		WORLD.addObejct(new IronBarrel(setPos));
	}

	setPos.x = -80;
	setPos.y = 0;
	setPos.z = 800;

	WORLD.addObejct(new IronBarrel(setPos));

	for(int i = 0 ; i < 10; i++) {

		setPos.x -= 40;
		setPos.y = 0;
		setPos.z = 800;

		WORLD.addObejct(new IronBarrel(setPos));
	}
	
	setPos.x = 515;
	setPos.y = 0;
	setPos.z = -375;

	WORLD.addObejct(new IronBarrel(setPos));

	for(int i = 0; i < 5; i++) {
		setPos.x -= 70;
		WORLD.addObejct(new IronBarrel(setPos));
	}
	
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

	CAMERA.removeAllNode();

	TKpoint setCameraPos;

	setCameraPos.x = 0;
	setCameraPos.y = 30;
	setCameraPos.z = 1000;

	CAMERA.setEyePos(setCameraPos);

	setCameraPos.x = 0;
	setCameraPos.y = 30;
	setCameraPos.z = 980;

	CAMERA.setCenterPos(setCameraPos);	

	setCameraPos.x = 0;
	setCameraPos.y = 30;
	setCameraPos.z = 1000;

	CAMERA.addCameraNode(setCameraPos, true, true, 1000);

	setCameraPos.x = 0;
	setCameraPos.y = 30;
	setCameraPos.z = 680;

	CAMERA.addCameraNode(setCameraPos, true, true, 500);

	setCameraPos.x += 50;

	CAMERA.addCameraNode(setCameraPos, true, true);

	setCameraPos.x -= 50;

	CAMERA.addCameraNode(setCameraPos, false, true, 500);

	setCameraPos.z -= 25;

	CAMERA.addCameraNode(setCameraPos, true, true);

	setCameraPos.x -= 25;

	CAMERA.addCameraNode(setCameraPos, true, true);
}

void initTartgetStage1(int num) {
	TKpoint setPos;
	TKpoint cameraPos = CAMERA.getEyePos();
	Object* temp;
	switch(num) {
	case 1:
		CAMERA.removeAllNode();
		CAMERA.addCameraNode(cameraPos, true, false);

		setPos.x = -415;
		setPos.y = 0;
		setPos.z = 405;

		temp = WORLD.addObejct(new Target(setPos));

		setPos.z = 470;

		dynamic_cast<Target*>(temp)->set_end_position(setPos);
		temp->setRotate(0, 90, 0);
		break;

	case 2:
		CAMERA.removeAllNode();
		cameraPos.x = 60;
		cameraPos.z = 492;

		CAMERA.addCameraNode(cameraPos, true, false);

		setPos.x = -100;
		setPos.y = 0;
		setPos.z = -50;

		temp = WORLD.addObejct(new Target(setPos));

		setPos.x = 100;
		setPos.y = 20;
		setPos.z = -50;

		dynamic_cast<Target*>(temp)->set_end_position(setPos);

		setPos.x = -100;
		setPos.y = 0;
		setPos.z = -100;

		temp = WORLD.addObejct(new Target(setPos));

		setPos.x = 50;
		setPos.y = 20;
		setPos.z = -125;

		dynamic_cast<Target*>(temp)->set_end_position(setPos);
		break;

	case 3:
		CAMERA.removeAllNode();
		cameraPos.x += 30;
		cameraPos.z -= 100;

		CAMERA.addCameraNode(cameraPos, true, true);

		cameraPos.x += 10;

		CAMERA.addCameraNode(cameraPos, true, false);

		setPos.x = 520;
		setPos.y = 0;
		setPos.z = 275;

		temp = WORLD.addObejct(new Target(setPos));
		temp->setRotate(0, -90, 0);

		setPos.z -= 50;

		temp = WORLD.addObejct(new Target(setPos));
		temp->setRotate(0, -90, 0);

		setPos.z -= 150;

		dynamic_cast<Target*>(temp)->set_end_position(setPos, 2);
		dynamic_cast<Target*>(temp)->moveReversing(true);

		setPos.z -= 100;

		temp = WORLD.addObejct(new Target(setPos));
		temp->setRotate(0, -90, 0);
		break;

	case 4:

		CAMERA.removeAllNode();
		cameraPos.x = 245;
		cameraPos.z = 256;

		CAMERA.addCameraNode(cameraPos, true, true);

		cameraPos.x -= 5;
		cameraPos.z -= 20;

		CAMERA.addCameraNode(cameraPos, true, false);

		setPos.x = 125;
		setPos.y = 0;
		setPos.z = -487;

		temp = WORLD.addObejct(new Target(setPos));

		setPos.x = 25;

		dynamic_cast<Target*>(temp)->set_end_position(setPos, 1);
		dynamic_cast<Target*>(temp)->moveReversing(true);
		break;
	case 5:
		CAMERA.removeAllNode();

		cameraPos.x = 270;
		cameraPos.z = 129;
		
		CAMERA.addCameraNode(cameraPos, true, true);

		cameraPos.x = 155;
		cameraPos.z = -26;
		
		CAMERA.addCameraNode(cameraPos, true, true);

		cameraPos.x = -64;
		cameraPos.z = -68;
		
		CAMERA.addCameraNode(cameraPos, true, true);

		break;
	case 6:
		CAMERA.removeAllNode();

		cameraPos.x = -159;
		cameraPos.z = -288;

		CAMERA.addCameraNode(cameraPos, false, false);

		setPos.x = 300;
		setPos.y = 0;
		setPos.z = 547;

		temp = WORLD.addObejct(new Target(setPos));
		temp->setRotate(0, 180, 0);

		setPos.x = 61;
		setPos.y = 0;
		setPos.z = 547;

		dynamic_cast<Target*>(temp)->set_end_position(setPos, 1);

		setPos.x = 46;
		setPos.y = 0;
		setPos.z = 72;

		temp = WORLD.addObejct(new Target(setPos));
		temp->setRotate(0, 180, 0);

		setPos.x = -18;
		setPos.y = 0;
		setPos.z = 72;

		dynamic_cast<Target*>(temp)->set_end_position(setPos, 0.5);
		break;

	case 7:
		CAMERA.removeAllNode();

		cameraPos.x = 13;
		cameraPos.z = -302;

		CAMERA.addCameraNode(cameraPos, false, true);

		cameraPos.x = 51;
		cameraPos.z = -467;

		CAMERA.addCameraNode(cameraPos, true, true);

		cameraPos.x = 51;
		cameraPos.z = -987;

		CAMERA.addCameraNode(cameraPos, true, true);

		break;
	case 8:
		UI.setStage(2);
		break;
	}
}

// ------------ GAME STAGE 2 INIT --------------

void initStage2() 
{
	if(GLOBAL.g_init)
		return;
	GLOBAL.g_init = true;

	float fGroundSize = 300;
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
	temp->setRotate(0, -90, 0);

	setPos.x = -fGroundSize;
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

	temp = WORLD.addObejct(new Target(setPos));

	setPos.x = 100;
	setPos.y = 20;
	setPos.z = -50;

	dynamic_cast<Target*>(temp)->set_end_position(setPos);

	setPos.x = -100;
	setPos.y = 0;
	setPos.z = -100;

	temp = WORLD.addObejct(new Target(setPos));

	setPos.x = 50;
	setPos.y = 20;
	setPos.z = -125;

	dynamic_cast<Target*>(temp)->set_end_position(setPos);

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

	CAMERA.removeAllNode();

	TKpoint setCameraPos;

	setCameraPos.x = 0;
	setCameraPos.y = 30;
	setCameraPos.z = 300;

	CAMERA.setEyePos(setCameraPos);

	setCameraPos.x = 0;
	setCameraPos.y = 30;
	setCameraPos.z = 0;

	CAMERA.setCenterPos(setCameraPos);
}