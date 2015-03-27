#include "CallBackFunc.h"

World* world = new World();
int g_Shage = 0; // Wire
int g_x;
int g_y;
int g_z;

double g_eye_x = 0, g_eye_y = 200, g_eye_z = 500;
double g_center_x, g_center_y, g_center_z;
double g_up_x, g_up_y, g_up_z;
double g_w, g_h;

Mainchar* obj = new Mainchar();

GLvoid drawScene ( GLvoid )
{
	static bool init = true;
	if(init){
		Stage::Instance()->SetChar(obj);
		init = false;
	}
	glClearColor( 0.0f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	/*static bool init = true;
	if(init){
		Stage::Instance()->AddObject(obj);
		init = false;
	}*/

	// 2d Screen
	glPushMatrix();
	{
		const float SCREEN_POS_X = -400, SCREEN_POS_Y = -100;
		const float SCREEN_SCALE = 0.5;
		glScalef(SCREEN_SCALE, SCREEN_SCALE, 0);
		glTranslatef(SCREEN_POS_X, SCREEN_POS_Y , 0.0);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(WIDTH, 0.0, 0.0);
		glVertex3f(WIDTH, HEIGHT, 0.0);
		glVertex3f(0.0, HEIGHT, 0.0);
		glEnd();
		world->draw();
	}
	glPopMatrix();

	// Camera Control
	
	
	/*gluLookAt(g_eye_x, g_eye_y, g_eye_z,
		g_center_x, g_center_y, g_center_z,
		0.0, 1.0, 0.0);*/
	gluLookAt(obj->GetPoint().x, g_eye_y, g_eye_z,
		obj->GetPoint().x, g_center_y, g_center_z,
		0.0, 1.0, 0.0);
	
	

	// Camera View
	glPushMatrix();
	{
		glTranslated(g_center_x, g_center_y, g_center_z);
		glutWireCube(30);
	}
	glPopMatrix();

	// Global View;
	glTranslatef( 0.0, 0.0, 0.0f );
	glRotatef(g_x, 1.0, 0.0, 0.0);
	glRotatef(g_y, 0.0, 1.0, 0.0);
	glRotatef(g_z, 0.0, 0.0, 1.0);	

	static int CreateTimer = 1000;
	static int CurrentTimer = clock();
	static int CreateCount = 0;
	if((CreateTimer < (clock() - CurrentTimer)) && (CreateCount < 25)){
		CreateCount++;
		CurrentTimer = clock();
		switch(rand()%3)
		{
		case 0:
			{
				Object* temp = new RectObject( rand() % 300, rand() % 300, 10 + rand() % 30, 10 + rand() % 30 );
				temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
				temp->setRescaleAnimation(rand() % 2, 3.0f, 0.5f);
				temp->setVelocity(true, rand() % 10, rand() % 10);

				world->addObject(temp);
			}
			break;
		case 1:
			{
				Object* temp = new CircleObject( rand() % 300, rand() % 300, 10 + rand() % 20, 10 + rand() % 20 );
				temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
				temp->setRescaleAnimation(rand() % 2, 2.0f, 0.5f, 0.01f);
				temp->setVelocity(true, rand() % 2, rand() % 2);

				world->addObject(temp);
			}
			break;
		case 2:
			{
				Object* temp = new MorpingObject( rand() % 300, rand() % 300, 20 + rand() % 20, 20 + rand() % 20 );
				temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
				temp->setRescaleAnimation(rand() % 2, 2.0f, 0.5f, 0.01f);
				temp->setVelocity(true, rand() % 2, rand() % 2);

				world->addObject(temp);
			}
			break;;
		}
	}
	

	// Draw 3DWorld
	Stage::Instance()->Draw();
	glLoadIdentity();
	glutSwapBuffers();
}

GLvoid reshape ( int w, int h )
{
	g_w = w;
	g_h = h;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(0, w, 0, h, -h, h);
	gluPerspective(60, w/h, 0, 100);
	gluLookAt(0.0, 0.0, 500.0,
	0.0, 0.0, 0.0,
	0.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
}


GLvoid mouse(int button, int state, int x, int y)
{
	int r_y = HEIGHT - y;
	printf("mouse x : %d, y : %d\n", x, y);

	if(state == GLUT_DOWN) {
		switch (button)	{
		case GLUT_LEFT_BUTTON:

			switch(rand()%3)
			{
			case 0:
				{
					Object* temp = new RectObject( x, r_y, 10 + rand() % 30, 10 + rand() % 30 );
					temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
					temp->setRescaleAnimation(rand() % 2, 3.0f, 0.5f);
					temp->setVelocity(true, rand() % 10, rand() % 10);

					world->addObject(temp);
				}
				break;
			case 1:
				{
					Object* temp = new CircleObject( x, r_y, 10 + rand() % 20, 10 + rand() % 20 );
					temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
					temp->setRescaleAnimation(rand() % 2, 2.0f, 0.5f, 0.01f);
					temp->setVelocity(true, rand() % 2, rand() % 2);

					world->addObject(temp);
				}
				break;
			case 2:
				{
					Object* temp = new MorpingObject( x, r_y, 20 + rand() % 20, 20 + rand() % 20 );
					temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
					temp->setRescaleAnimation(rand() % 2, 2.0f, 0.5f, 0.01f);
					temp->setVelocity(true, rand() % 2, rand() % 2);

					world->addObject(temp);
				}
				break;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			world->allMoveToPoint(x, r_y);
			break;		

		default:
			break;
		}
	}
}

GLvoid mouseMove(int x, int y)
{
	int r_y = HEIGHT - y;
	switch(rand()%2)
	{
	case 0:
		{
			Object* temp = new RectObject( x, r_y, 20 );
			temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
			temp->setRescaleAnimation(rand() % 2, 3.0f, 0.5f);
			//temp->setVelocity(true, rand() % 10, rand() % 10);
			world->addObject(temp);
		}
		break;
	case 1:
		{
			Object* temp = new CircleObject( x, r_y, 20 );
			temp->setColor( (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
			temp->setRescaleAnimation(rand() % 2, 3.0f, 0.5f);
			//temp->setVelocity(true, rand() % 10, rand() % 10);
			world->addObject(temp);
		}
		break;
	}

}

#define CAMERA_EYE_SPEED 10

GLvoid keyBoardFunc(unsigned char key, int x, int y)
{
	
	static bool init = true;
	switch(key)
	{
	case '1':
		Stage::Instance()->AddObject(new Mainchar());
		
		break;
	case 'a':
		g_eye_x -= CAMERA_EYE_SPEED;
		break;
	case 'd':
		g_eye_x += CAMERA_EYE_SPEED;
		break;
	case 'w':
		g_eye_z -= CAMERA_EYE_SPEED;
		break;
	case 's':
		g_eye_z += CAMERA_EYE_SPEED;
		break;
	case 'r':
		g_eye_y += CAMERA_EYE_SPEED;
		break;
	case 'f':
		g_eye_y -= CAMERA_EYE_SPEED;
		break;
	case 'x':
		g_x--;
		break;
	case 'X':
		g_x++;
		break;
	case 'y':
		g_y--;
		break;
	case 'Y':
		g_y++;
		break;
	case 'z':
		g_z--;
		break;
	case 'Z':
		g_z++;
		break;
	
	case 'i':
		obj->ObjectControlPosition(0.0, 0.0, -5.0);
		break;
	case 'k':
		obj->ObjectControlPosition(0.0, 0.0, +5.0);
		break;
	case 'j':
		if(obj->GetJump()){
			obj->ObjectControlPosition(-2.0, 0.0, 0.0);
		} else {
			obj->ChargeJumpState(JumpLeft::Instance());
		}
		break;
	case 'l':
		if(obj->GetJump()){
			obj->ObjectControlPosition(2.0, 0.0, 0.0);
		} else {
			obj->ChargeJumpState(JumpRight::Instance());
		}
		break;

	case 'o':
		obj->ObjectControlAngle(+5);
		break;
	case 'p':
		obj->ObjectControlAngle(-5);
		break;
	case ' ':
		obj->ChargeJumpState(JumpUp::Instance());
		break;
	default:
		break;
	}
}

GLvoid timerFunc(int val)
{
	Stage::Instance()->Update();
	glutPostRedisplay();
	glutTimerFunc( 16, timerFunc, 1 );
}

GLvoid specialKeyBoardFunc(int key, int x, int y)
{
	// left : 100 / up : 101 / right : 102 / down : 103
	// page up : 104 / page down : 105
	switch(key)
	{
	case 100:
		g_center_x -= CAMERA_EYE_SPEED;
		break;
	case 102:
		g_center_x += CAMERA_EYE_SPEED;
		break;
	case 101:
		g_center_z -= CAMERA_EYE_SPEED;
		break;
	case 103:
		g_center_z += CAMERA_EYE_SPEED;
		break;
	case 104:
		g_center_y += CAMERA_EYE_SPEED;
		break;
	case 105:
		g_center_y -= CAMERA_EYE_SPEED;
		break;
	}
	printf("%d\n", key);
}