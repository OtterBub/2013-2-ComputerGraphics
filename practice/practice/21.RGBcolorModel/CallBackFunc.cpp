#include "CallBackFunc.h"
#define GROUND_SIZE 300.0f

void drawStrokeText(char *string, int x, int y, int z){
	char *c;
	glPushMatrix();
	{
		glTranslatef(x, y + 8, z);
		glColor3f(1.0, 1.0, 1.0);
		glScalef(0.09f, 0.08f, z);
		for(c = string; *c != '\0'; c++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();
}

World* world = new World();
int g_Shage = 0; // Wire
int g_x;
float g_y;
int g_z;

double g_eye_x = 0, g_eye_y = 500, g_eye_z = 500;
double g_center_x, g_center_y, g_center_z = -1;
double g_up_x, g_up_y, g_up_z;
double g_w, g_h;

double g_r = 0.25, g_g = 0.25, g_b = 0.6;

bool g_init = true;
inline void init(){
	if(!g_init)
		return;
	else
		g_init = false;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	World3D::Instance()->AddObject(new Pyramid(250, 1,250));
	World3D::Instance()->AddObject(new Pyramid(250, 1, -250));
	World3D::Instance()->AddObject(new Pyramid(-250, 1, -250));
	World3D::Instance()->AddObject(new Pyramid(-250, 1, 250));
	World3D::Instance()->AddObject(new Pyramid(0, 1, 0, 10));
}

inline void AutoAddObject2D(){
	static int CreateTimer = 1000;
	static int CurrentTimer = clock();
	static int CreateCount = 0;
	static int CreateNum = 0;
	CreateNum = (CreateNum + 1) % 3;
	if((CreateTimer < (clock() - CurrentTimer)) && (CreateCount < 12)){
		CreateCount++;
		CurrentTimer = clock();
		switch(CreateNum)
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
}

GLvoid drawScene ( GLvoid )
{
	init();

	//glClearColor( 0.0f, 0.3f, 0.3f, 1.0f ); (Blue Black)
	glClearColor( g_r, g_g, g_b, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Camera Control
	gluLookAt(g_eye_x, g_eye_y, g_eye_z,
		g_center_x, g_center_y, g_center_z,
		0.0, 1.0, 0.0);

	// Global View;
	//glTranslatef( g_eye_x, g_eye_y, g_eye_z );
	glTranslatef( 0, 0, 0 );
	glRotatef(g_x, 1.0, 0.0, 0.0);
	glRotatef(g_y, 0.0, 1.0, 0.0);
	glRotatef(g_z, 0.0, 0.0, 1.0);

	// 2d Screen
	glPushMatrix();
	{
		/*gluLookAt(0, 0, 400,
		0, 0, 0,
		0.0, 1.0, 0.0);*/
		
		const float SCREEN_POS_X = -300, SCREEN_POS_Y = 0, SCREEN_POS_Z = -400;
		//const float SCREEN_POS_X = 0, SCREEN_POS_Y = 0;
		const float SCREEN_SCALE = 1.0;
		char Text[100];

		glTranslatef(SCREEN_POS_X, SCREEN_POS_Y , SCREEN_POS_Z);
		glScalef(SCREEN_SCALE, SCREEN_SCALE, 0);
		glColor4f(0.1, 0.1, 0.1, 0.5);
		glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(WIDTH, 0.0, 0.0);
		glVertex3f(WIDTH, HEIGHT, 0.0);
		glVertex3f(0.0, HEIGHT, 0.0);
		glEnd();

		world->draw();
		
		AutoAddObject2D();

		sprintf(Text, "%.3f, %.3f, %.3f \n eye::(%.3f, %.3f, %.3f) \n center::(%.3f, %.3f, %.3f)", 
			g_r, g_g, g_b,
			g_eye_x, g_eye_y, g_eye_z,
			g_center_x, g_center_y, g_center_z);
		/*printf("%.3f, %.3f, %.3f \n eye::(%.3f, %.3f, %.3f) \n center::(%.3f, %.3f, %.3f)", 
			g_r, g_g, g_b,
			g_eye_x, g_eye_y, g_eye_z,
			g_center_x, g_center_y, g_center_z);*/
		drawStrokeText(Text, 0, 100, 1000);
	}
	glPopMatrix();

	glColor3f(0.0, 0.7, 0.7);
	glBegin(GL_POLYGON);
	glVertex3f(-GROUND_SIZE, 0.0, -GROUND_SIZE);
	glVertex3f(-GROUND_SIZE, 0.0, GROUND_SIZE);
	glVertex3f(GROUND_SIZE, 0.0, GROUND_SIZE);
	glVertex3f(GROUND_SIZE, 0.0, -GROUND_SIZE);	
	glEnd();
	
	// Draw 3DWorld
	World3D::Instance()->Draw();
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
	gluPerspective(60, w/h, 1.0, 2000.0f);
	/*gluLookAt(0.0, 0.0, 500.0,
	0.0, 0.0, 0.0,
	0.0, 1.0, 0.0);*/

	glMatrixMode(GL_MODELVIEW);
}


GLvoid mouse(int button, int state, int x, int y)
{
	int r_y = HEIGHT - y;
	printf("mouse x : %d, y : %d\n", x, y);

	if(state == GLUT_DOWN) {
		switch (button)	{
		case GLUT_LEFT_BUTTON:
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

GLvoid timerFunc(int val)
{
	World3D::Instance()->Update();
	g_y += 0.5;
	glutPostRedisplay();
	glutTimerFunc( 16, timerFunc, 1 );
}

#define CAMERA_EYE_SPEED 10

GLvoid keyBoardFunc(unsigned char key, int x, int y)
{
	
	static bool init = true;
	switch(key)
	{
	case '1':
		World3D::Instance()->AddObject(new Pyramid(rand()%600 - 300, 0, rand()%600 - 300));
		break;
	case 'a':
		//g_eye_x -= CAMERA_EYE_SPEED;
		g_y -= 1;
		break;
	case 'd':
		//g_eye_x += CAMERA_EYE_SPEED;
		g_y += 1;
		break;
	case 'w':
		g_eye_z -= CAMERA_EYE_SPEED;
		g_center_z -= CAMERA_EYE_SPEED;
		break;
	case 's':
		g_eye_z += CAMERA_EYE_SPEED;
		g_center_z += CAMERA_EYE_SPEED;
		break;
	case 'r':
		g_eye_y += CAMERA_EYE_SPEED;
		break;
	case 'f':
		g_eye_y -= CAMERA_EYE_SPEED;
		break;
	case 'q':
		g_eye_x -= CAMERA_EYE_SPEED;
		g_center_x -= CAMERA_EYE_SPEED;
		break;
	case 'e':
		g_eye_x += CAMERA_EYE_SPEED;
		g_center_x += CAMERA_EYE_SPEED;
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
	case 't':
		g_r-=0.05;
		break;
	case 'T':
		g_r+=0.05;
		break;
	case 'g':
		g_g-=0.05;
		break;
	case 'G':
		g_g+=0.05;
		break;
	case 'b':
		g_b-=0.05;
		break;
	case 'B':
		g_b+=0.05;
		break;
	case ' ':
		World3D::Instance()->AddFunction();
		break;
	default:
		break;
	}
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

GLvoid MenuFuntion(int value)
{
	switch(value){
	case 1:
		glEnable(GL_DEPTH_TEST);
		break;
	case 2:
		glDisable(GL_DEPTH_TEST);
		break;

	case 11:
		glEnable(GL_CULL_FACE);
		break;
	case 22:
		glDisable(GL_CULL_FACE);
		break;

	case 111:
		glShadeModel(GL_FLAT);
		break;
	case 222:
		glShadeModel(GL_SMOOTH);
		break;

	case 333:World3D::Instance()->AddFunction();
		break;

	default:
		break;
	}
}