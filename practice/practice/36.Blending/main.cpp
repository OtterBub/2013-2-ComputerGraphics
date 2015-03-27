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

double g_eye_x = 0, g_eye_y = 300, g_eye_z = 1000;
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
	int iSrc_alpha;
	int iDst_alpha;

public:
	BoxObject(float _x, float _y, float _z,
		float _r, float _g, float _b, float _a,
		int _iSrc, int _iDst)
	{
		m_point.x = _x;
		m_point.y = _y;
		m_point.z = _z;

		m_color.r = _r;
		m_color.g = _g;
		m_color.b = _b;
		m_color.a = _a;

		m_size = 20;
		iSrc_alpha = _iSrc;
		iDst_alpha = _iDst;
	}


	~BoxObject() {}

	void Draw() {

		glEnable(GL_BLEND);

		glPushMatrix();

		glBlendFunc(iSrc_alpha, iDst_alpha);
		glColor4f(m_color.r, m_color.g, m_color.b, 1);

		glTranslatef(m_point.x, m_point.y, m_point.z);
		glutSolidSphere(50, 10, 10);

		glColor4f(1-m_color.r, 1-m_color.g, 1-m_color.b, 0.5);

		glPopMatrix();

		glPushMatrix();

		glTranslatef(m_point.x + 20, m_point.y + 20, m_point.z);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(50, 50, 10, 10);

		glPopMatrix();


		glPushMatrix();
		glColor4f(0, 1, 1, 0.5);
		glTranslatef(m_point.x - 20, m_point.y - 20, m_point.z);
		glRotatef(-90, 1, 0, 0);
		glutSolidTeapot(50);

		glPopMatrix();

		glDisable(GL_BLEND);

		char text[100];

		switch(iSrc_alpha)
		{
		case GL_ONE:
			strcpy(text, "( GL_ONE, ");
			break;

		case GL_ZERO:
			strcpy(text, "( GL_ZERO, ");
			break;

		case GL_SRC_ALPHA:
			strcpy(text, "( GL_SRC_ALPHA, ");
			break;

		case GL_SRC_COLOR:
			strcpy(text, "( GL_SRC_COLOR, ");
			break;

		case GL_ONE_MINUS_SRC_ALPHA:
			strcpy(text, "( GL_ONE_MINUS_SRC_ALPHA, ");
			break;

		case GL_ONE_MINUS_SRC_COLOR:
			strcpy(text, "( GL_ONE_MINUS_SRC_COLOR, ");
			break;

		case GL_ONE_MINUS_DST_COLOR:
			strcpy(text, "( GL_ONE_MINUS_DST_COLOR, ");
			break;

		case GL_ONE_MINUS_DST_ALPHA:
			strcpy(text, "( GL_ONE_MINUS_DST_ALPHA, ");
			break;

		default:
			break;
		}

		switch(iDst_alpha)
		{
		case GL_ONE:
			strcpy(&text[strlen(text)], "GL_ONE )");
			break;

		case GL_ZERO:
			strcpy(&text[strlen(text)], "GL_ZERO )");
			break;

		case GL_SRC_ALPHA:
			strcpy(&text[strlen(text)], "GL_SRC_ALPHA )");
			break;

		case GL_SRC_COLOR:
			strcpy(&text[strlen(text)], "GL_SRC_COLOR )");
			break;

		case GL_ONE_MINUS_SRC_ALPHA:
			strcpy(&text[strlen(text)], "GL_ONE_MINUS_SRC_ALPHA )");
			break;

		case GL_ONE_MINUS_SRC_COLOR:
			strcpy(&text[strlen(text)], "GL_ONE_MINUS_SRC_COLOR )");
			break;

		case GL_ONE_MINUS_DST_COLOR:
			strcpy(&text[strlen(text)], "GL_ONE_MINUS_DST_COLOR )");
			break;

		case GL_ONE_MINUS_DST_ALPHA:
			strcpy(&text[strlen(text)], "GL_ONE_MINUS_DST_ALPHA )");
			break;

		default:
			break;
		}

		drawStrokeText(text, m_point.x - 150, m_point.y-100, m_point.z, 0.12);

	}
};

BoxObject* BlendObj[10];

bool g_init = true;

inline void init() {
	if(!g_init)
		return;
	g_init = false;

	static float GAP = 450;

	BlendObj[0] = 
		new BoxObject(-GAP, 300, 0, 
		1, 1, 0.5, 1,
		GL_ONE, GL_ZERO);

	BlendObj[1] = 
		new BoxObject(0, 300, 0, 
		1, 1, 0.5, 1,
		GL_ZERO, GL_ONE);

	BlendObj[2] = 
		new BoxObject(GAP, 300, 0, 
		1, 1, 0.5, 1,
		GL_ONE, GL_ONE);


	BlendObj[3] = 
		new BoxObject(-GAP, 0, 0, 
		1, 1, 0.5, 1,
		GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	BlendObj[4] = 
		new BoxObject(0, 0, 0, 
		1, 1, 0.5, 1,
		GL_SRC_ALPHA, GL_ONE);

	BlendObj[5] = 
		new BoxObject(GAP, 0, 0, 
		1, 1, 0.5, 1,
		GL_ZERO, GL_SRC_COLOR);

	BlendObj[6] = 
		new BoxObject(-GAP, -300, 0, 
		1, 1, 0.5, 1,
		GL_ONE_MINUS_DST_COLOR, GL_ZERO);

	BlendObj[7] = 
		new BoxObject(0, -300, 0, 
		1, 1, 0.5, 1,
		GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);

	BlendObj[8] = 
		new BoxObject(GAP, -300, 0, 
		1, 1, 0.5, 1,
		GL_ONE, GL_ONE);

}

GLvoid drawScene(GLvoid)
{
	init();
	glEnable(GL_DEPTH_TEST);
	glClearColor( 0.0f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	
	// Global View
	gluLookAt(g_eye_x, g_eye_y, g_eye_z,
		g_center_x, g_center_y, g_center_z,
		0.0, 1.0, 0.0);

	glRotatef(g_x, 1.0, 0.0, 0.0);
	glRotatef(g_y, 0.0, 1.0, 0.0);
	glRotatef(g_z, 0.0, 0.0, 1.0);
	
	/*glPushMatrix();
	{
		glColor4f(1, 1, 1, 1);
		glutSolidCube(100);
		glColor4f(0, 0, 0, 1);
		glutWireCube(100);
	}
	glPopMatrix();*/

	/*glPushMatrix();
	{
		glTranslatef(100, 0, 0);
		glColor4f(1, 1, 0, 1);
		glutSolidCube(100);
		glColor4f(0, 0, 1, 1);
		glutWireCube(100);
	}
	glPopMatrix();*/

	for(int i = 0; i < 9; i++)
		BlendObj[i]->Draw();

	glLoadIdentity();
	glutSwapBuffers();
}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-(w), (w), -(h), (h), -10, 2000);

	g_center_y = g_eye_y = 150;
	g_center_x = g_eye_x = 0;
	g_x = 0;
	g_y = 0;
	g_z = 0;

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