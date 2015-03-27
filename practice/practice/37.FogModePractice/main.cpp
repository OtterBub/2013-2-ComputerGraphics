#include <iostream>
#include <ctime>
#include <cstdlib>

#include <gl/glut.h>
#include <gl/GLU.h>
#include <gl/GL.h>

#define HEIGHT 600
#define WIDTH 800

#define FOG_MODE_LINEAR 10
#define FOG_MODE_EXP 11
#define FOG_MODE_EXP2 12
#define FOG_MODE_OFF 13

#define FOG_DENSITY_UP 20
#define FOG_DENSITY_DOWN 21

#define FOG_START_UP 30
#define FOG_START_DOWN 31

#define FOG_END_UP 40
#define FOG_END_DOWN 41

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void mouse(int button, int state, int x, int y);
void mouseMove(int x, int y);
void MenuFuntion(int flag);
void drawStrokeText(char *string, float x, float y, float z, float scale);

// -------------- Global View Control Value -----------------

double g_eye_x = 0, g_eye_y = 300, g_eye_z = 800;
double g_center_x, g_center_y, g_center_z = -1;

float g_x;
float g_y;
float g_z;

// -------------- Global Value -----------------

int g_iFogMode = GL_LINEAR;
float g_fFog_color[4] = {0.7, 0.7, 0.7, 1.0};
float g_fDensity = 0.01;
float g_fFogStart = -10.0;
float g_fFogEnd = 10.0;
float g_fAdd = 10;

struct TEKA_POINT {
	float x;
	float y;
	float z;
};

struct TEKA_COLOR {
	float r;
	float g;
	float b;
	float a;
};

class BoxObject {
private:
	TEKA_POINT m_point;
	TEKA_COLOR m_color;
	float m_size;
public:
	BoxObject(float _x, float _y, float _z){
		m_point.x = _x;
		m_point.y = _y;
		m_point.z = _z;

		m_color.r = 0;
		m_color.g = 0;
		m_color.b = 0;
		m_color.a = 1;

		m_size = 20;
	}

	BoxObject(float _x, float _y, float _z,
		float _r, float _g, float _b, float _a)
	{
		m_point.x = _x;
		m_point.y = _y;
		m_point.z = _z;

		m_color.r = _r;
		m_color.g = _g;
		m_color.b = _b;
		m_color.a = _a;

		m_size = 20;
	}

	BoxObject(float _x, float _y, float _z,
		float _r, float _g, float _b, float _a,
		float _size)
	{
		m_point.x = _x;
		m_point.y = _y;
		m_point.z = _z;

		m_color.r = _r;
		m_color.g = _g;
		m_color.b = _b;
		m_color.a = _a;

		m_size = _size;
	}

	~BoxObject() {}

	void Draw() {
		glPushMatrix();

		glColor4f(m_color.r, m_color.g, m_color.b, m_color.a);
		glutSolidCube(m_size);

		glColor4f(1.0 - m_color.r, 1.0 - m_color.g, 1.0 - m_color.b, m_color.a);
		glutWireCube(m_size);

		glPopMatrix();
	}
	void Update() {}
};

bool g_init = true;

inline void init() {
	if(!g_init)
		return;
	g_init = false;

}

GLvoid drawScene(GLvoid)
{

	glEnable(GL_DEPTH_TEST);
	glClearColor( 0.0f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	char text[100];
	sprintf(text, "Start : %.2f / End : %.2f / Add : %.2f", g_fFogStart, g_fFogEnd, g_fAdd);
	drawStrokeText(text, -0.5, -0.5, -1, 0.0003);

	sprintf(text, "Density : %.2f", g_fDensity);
	drawStrokeText(text, -0.5, -0.25, -1, 0.0003);

	glFogf(GL_FOG_MODE, g_iFogMode);
	glFogfv(GL_FOG_COLOR, g_fFog_color);
	GLfloat fogStartPos[3] = {-50, -50, -50};
	//glFogf(GL_FOG_START, g_fFogStart);
	glFogfv(GL_FOG_START, fogStartPos);
	GLfloat fogEndPos[3] = {50, 50, 50};
	//glFogf(GL_FOG_END, g_fFogEnd);
	glFogfv(GL_FOG_END, fogEndPos);
	glFogf(GL_FOG_DENSITY, g_fDensity);
	
	
	// Global View
	gluLookAt(g_eye_x, g_eye_y, g_eye_z,
		g_center_x, g_center_y, g_center_z,
		0.0, 1.0, 0.0);

	glRotatef(g_x, 1.0, 0.0, 0.0);
	glRotatef(g_y, 0.0, 1.0, 0.0);
	glRotatef(g_z, 0.0, 0.0, 1.0);
	
	glPushMatrix();
	{
		glColor4f(1, 1, 1, 1);
		glutSolidCube(100);
		glColor4f(0, 0, 0, 1);
		glutWireCube(100);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(100, 0, 0);
		glColor4f(1, 0, 0, 1);
		glutSolidCube(100);
		glColor4f(0, 0, 0, 1);
		glutWireCube(100);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-100, 0, 0);
		glColor4f(1, 1, 0, 1);
		glutSolidCube(100);
		glColor4f(0, 0, 0, 1);
		glutWireCube(100);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0, 0, 100);
		glColor4f(0, 1, 1, 1);
		glutSolidCube(100);
		glColor4f(0, 0, 0, 1);
		glutWireCube(100);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0, 0, -100);
		glColor4f(0, 1, 0, 1);
		glutSolidCube(100);
		glColor4f(0, 0, 0, 1);
		glutWireCube(100);
	}
	glPopMatrix();

	glLoadIdentity();
	glutSwapBuffers();
}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, w/h, 1.0, 2000.0f);

	glMatrixMode(GL_MODELVIEW);

}

void Keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case '1':
		g_fAdd+=1;
		break;

	case '2':
		g_fAdd-=1;
		break;

	default:
		break;
	}
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
void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(16, TimerFunction, 1);
}

void MenuFuntion(int flag)
{
	switch(flag)
	{
	case FOG_MODE_LINEAR:
		glEnable(GL_FOG);
		g_iFogMode = GL_LINEAR;
		break;

	case FOG_MODE_EXP:
		glEnable(GL_FOG);
		g_iFogMode = GL_EXP;
		break;

	case FOG_MODE_EXP2:
		glEnable(GL_FOG);
		g_iFogMode = GL_EXP2;
		break;
	case FOG_MODE_OFF:
		glDisable(GL_FOG);
		break;

	case FOG_DENSITY_UP:
		g_fDensity += 0.3;

		if(g_fDensity >= 1 )
			g_fDensity = 1;

		break;

	case FOG_DENSITY_DOWN:
		g_fDensity -= 0.3;

		if(g_fDensity <= 0 )
			g_fDensity = 0;

		break;

	
	case FOG_START_UP:
		g_fFogStart+=g_fAdd;
		break;
	case FOG_START_DOWN:
		g_fFogStart-=g_fAdd;
		break;

	case FOG_END_UP:
		g_fFogEnd+=g_fAdd;
		break;
	case FOG_END_DOWN:
		g_fFogEnd-=g_fAdd;
		break;

	default:
		break;
	}

}

void main(int argc, char *argv[])
{

	//윈도우 초기화 및 생성
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutCreateWindow("Fog Test");
	//필요한 콜백 함수 설정
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMotionFunc(mouseMove);
	glutMouseFunc(mouse);
	glutTimerFunc(100, TimerFunction, 1);

	// Add Popup Menu
	int FogModeMenu, FogDensityMenu, FogStartEndMenu;
	int MainMenu;

	FogModeMenu = glutCreateMenu( MenuFuntion );
	glutAddMenuEntry("LINEAR", FOG_MODE_LINEAR);
	glutAddMenuEntry("EXP", FOG_MODE_EXP);
	glutAddMenuEntry("EXP2", FOG_MODE_EXP2);
	glutAddMenuEntry("OFF", FOG_MODE_OFF);

	FogDensityMenu = glutCreateMenu( MenuFuntion );
	glutAddMenuEntry("UP", FOG_DENSITY_UP);
	glutAddMenuEntry("DOWN", FOG_DENSITY_DOWN);

	FogStartEndMenu = glutCreateMenu( MenuFuntion );
	glutAddMenuEntry("START_UP", FOG_START_UP);
	glutAddMenuEntry("START_DOWN", FOG_START_DOWN);

	glutAddMenuEntry("END_UP", FOG_END_UP);
	glutAddMenuEntry("END_DOWN", FOG_END_DOWN);

	MainMenu = glutCreateMenu( MenuFuntion );
	glutAddSubMenu("FOG_MODE", FogModeMenu);
	glutAddSubMenu("FOG_DENSITY", FogDensityMenu);
	glutAddSubMenu("FOG_START_END", FogStartEndMenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

}

void drawStrokeText(char *string, float x, float y, float z, float scale){
	char *c;
	glPushMatrix();
	{
		glTranslatef(x, y, z);
		glColor3f(1.0, 1.0, 1.0);
		//glScalef(0.09f, 0.08f, z);
		glScalef(scale, scale, scale);
		for(c = string; *c != '\0'; c++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();
}