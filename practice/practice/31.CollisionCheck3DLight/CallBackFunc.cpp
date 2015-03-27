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
float g_x;
float g_y;
float g_z;

double g_eye_x = 0, g_eye_y = 300, g_eye_z = 800;
double g_center_x, g_center_y, g_center_z = -1;
double g_up_x, g_up_y, g_up_z;
double g_w, g_h;

double g_r = 0.3, g_g = 0.3, g_b = 0.5;

bool g_init = true;

double g_light_x = 0, g_light_y = 1, g_light_z = 0;

Ball* myBall = WORLD->AddBall(new Ball(-100, 100, 10));

inline void init(){
	if(!g_init)
		return;
	else
		g_init = false;

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	//WORLD->AddObject(new Pyramid(0, 1, 0, 2));
	WORLD->AddBall(new Ball(10, 50, 100, 5));

	CollisionBox temp;
	temp.Max.x = 310;
	temp.Max.y = 300;
	temp.Max.z = 300;

	temp.Min.x = 301;
	temp.Min.y = 1;
	temp.Min.z = -300;

	WORLD->AddWall(new Wall(temp));

	temp.Max.x = 300;
	temp.Max.y = 300;
	temp.Max.z = -301;

	temp.Min.x = -300;
	temp.Min.y = 1;
	temp.Min.z = -310;

	WORLD->AddWall(new Wall(temp));

	temp.Max.x = -301;
	temp.Max.y = 300;
	temp.Max.z = 300;

	temp.Min.x = -310;
	temp.Min.y = 1;
	temp.Min.z = -300;

	WORLD->AddWall(new Wall(temp));

	temp.Max.x = 300;
	temp.Max.y = 310;
	temp.Max.z = 300;

	temp.Min.x = -300;
	temp.Min.y = 301;
	temp.Min.z = -300;

	WORLD->AddWall(new Wall(temp));

	temp.Max.x = 300;
	temp.Max.y = 10;
	temp.Max.z = 300;

	temp.Min.x = -300;
	temp.Min.y = 0;
	temp.Min.z = -300;

	WORLD->AddWall(new Wall(temp, false));

	temp.Max.x = 300;
	temp.Max.y = 300;
	temp.Max.z = 310;

	temp.Min.x = -300;
	temp.Min.y = 1;
	temp.Min.z = 300;

	WORLD->AddWall(new Wall(temp)) ->SetMode(GL_LINE_LOOP);

	/*for(int i = 0; i < 10; i++) {
		temp.Max.x = i * 10;
		temp.Max.y = i * 20;
		temp.Max.z = rand()% 10;

		temp.Min = temp.Max;

		temp.Min.x -= 30 + rand() % 10;
		temp.Min.y -= 10;
		temp.Min.z -= 30 + rand() % 10;
		WORLD->AddWall(new Wall(temp));
	}*/

	for(int i = 0; i < 5; i++) {
		temp.Max.x = (rand() % 500) - 200;
		temp.Max.y = 40;
		temp.Max.z = (rand() % 500) - 200;

		temp.Min = temp.Max;

		temp.Min.x -= 30 + rand() % 10;
		temp.Min.y -= 39;
		temp.Min.z -= 30 + rand() % 10;
		WORLD->AddWall(new Wall(temp));
	}

	for(int i = 0; i < 5; i++) {
		temp.Max.x = (rand() % 500) - 200;
		temp.Max.y = 20;
		temp.Max.z = (rand() % 500) - 200;

		temp.Min = temp.Max;

		temp.Min.x -= 30 + rand() % 10;
		temp.Min.y -= 19;
		temp.Min.z -= 30 + rand() % 10;
		WORLD->AddWall((Wall*)(new ColorWall(temp)));
	}
	//GLfloat gray[] = {0.75f, 0.75f, 0.75f, 1.0f};
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);

	WORLD->AddLight(0);
	WORLD->SetLightColor(0, GL_DIFFUSE, 1, 1, 1, 1);
	WORLD->SetLightColor(0, GL_SPECULAR, 1, 1, 1, 1);

	glEnable(GL_COLOR_MATERIAL);
	GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 30);
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

	/*glPushMatrix();
	{
		glTranslatef(g_light_x, g_light_y, g_light_z);
		
		GLfloat position[] = {0, 1, 0, 1};
		GLfloat white_color[] = {1, 1, 1, 1};
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, white_color);
		
		glColor3f(0, 0, 1);
		glutSolidSphere(10, 10, 10);
	}
	glPopMatrix();*/
	WORLD->SetLightPos(0, myBall->GetPoint().x, myBall->GetPoint().y + 15, myBall->GetPoint().z, 1);
	WORLD->SetLightColor(0, GL_DIFFUSE, myBall->getR(), myBall->getG(), myBall->getB(), 1);
	WORLD->SetLightColor(0, GL_SPECULAR, myBall->getR(), myBall->getG(), myBall->getB(), 1);
	
	// Draw 3DWorld
	WORLD->Draw();
	glLoadIdentity();
	glutSwapBuffers();
}

GLvoid timerFunc(int val)
{
	WORLD->Update();

	glutPostRedisplay();
	glutTimerFunc( 16, timerFunc, 1 );
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

double pre_x, pre_y;

GLvoid mouse(int button, int state, int x, int y)
{
	int r_y = HEIGHT - y;
	//printf("mouse x : %d, y : %d\n", x, y);

	pre_x = x;
	pre_y = y;

	if(state == GLUT_DOWN) {
		switch (button)	{
		case GLUT_LEFT_BUTTON:
			break;

		case GLUT_RIGHT_BUTTON:
			break;		

		default:
			break;
		}
	}
}

GLvoid mouseMove(int x, int y)
{
	int r_y = HEIGHT - y;

	//printf("%f, %f \n", x - pre_x, y - pre_y);

	g_y += (float)(x - pre_x) / 10.0f;
	g_x += (float)(y - pre_y) / 10.0f;

	pre_x = x;
	pre_y = y;
}

#define CAMERA_EYE_SPEED 10

GLvoid keyBoardFunc(unsigned char key, int x, int y)
{
	static bool init = true;
	switch(key)
	{
	case '1':
		WORLD->AddBall(new Ball(0, 100, 0,
			rand()%12 - 6 + ((float)rand() / RAND_MAX), rand()%12 - 6 + ((float)rand() / RAND_MAX), rand()%12 - 6 + ((float)rand() / RAND_MAX)));
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
		//g_center_z -= CAMERA_EYE_SPEED;
		break;
	case 's':
		g_eye_z += CAMERA_EYE_SPEED;
		//g_center_z += CAMERA_EYE_SPEED;
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
	case 'i':
		myBall->AddVelocity(0, 0, -0.1);
		break;
	case 'k':
		myBall->AddVelocity(0, 0, 0.1);
		break;
	case 'j':
		myBall->AddVelocity(-0.1, 0, 0);
		break;
	case 'l':
		myBall->AddVelocity(0.1, 0, 0);
		break;
	case 'n':
		myBall->AddVelocity(0, 3, 0);
		break;
	case ' ':
		WORLD->AddFunction();
		break;
	case 'o':
		g_light_x -= CAMERA_EYE_SPEED;
		break;
	case 'O':
		g_light_x += CAMERA_EYE_SPEED;
		break;
	case 'p':
		g_light_y -= CAMERA_EYE_SPEED;
		break;
	case 'P':
		g_light_y += CAMERA_EYE_SPEED;
		break;
	case '[':
		g_light_z -= CAMERA_EYE_SPEED;
		break;
	case '{':
		g_light_z += CAMERA_EYE_SPEED;
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

	default:
		break;
	}
}