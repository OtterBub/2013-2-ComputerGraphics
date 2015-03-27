#include "CallBackFunc.h"

World* world = new World();
int g_shape = 0;

#define COS 0
#define SIN 1
#define SPR 2
#define QUD 3

int g_x = 0;
int g_y = 0;
int g_state = 0;
float g_scale = 1;
float g_worldScale = 1;
float g_worldAngle = 0;
float g_modelAngle = 0;
float g_Shearing_y = 0;
float g_Shearing_x = 0;

GLvoid drawScene ( GLvoid )
{

	float m_s[4][4] = {
		{1.f, g_Shearing_x, 0.f, 0.f},
		{g_Shearing_y, 1.f, 0.f, 0.f},
		{0.f, 0.f, 1.f, 0.f},
		{0.f, 0.f, 0.f, 1.f}	
	};		// ¿­ ¿ì¼±

	glClearColor( 0.0f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );


	glRotated(g_worldAngle, 0.0, 0.0, 1.0);
	glScalef(g_worldScale, g_worldScale, 1.0);

	glTranslatef(g_x, g_y, 0.0);
	glRotatef(g_modelAngle, 0.0, 0.0, 1.0);
	glScalef(g_scale, g_scale, 1.0);
	
	glMultMatrixf(*m_s);

	const double s = 100;
	const double m = 100;

	static int j = -200;

	if(j > 200)
		j = -200;

	switch(g_shape){
	case COS:
		glColor4f(0.0, 1.0, 1.0, 1.0);
		glBegin(GL_LINE_STRIP);
		for(int i = -200; i < 200; i++)
		{
			glVertex2f((i) , (cos((double)i/s)*m));
		}
		glEnd();
		glColor4f(1.0, 0.0, 0.0, 1.0);
		glRectd((j) + 2, (cos((double)j/s)*m) + 2, (j) - 2, (cos((double)j/s)*m) - 2);
		break;
	case SIN:
		glColor4f(1.0, 1.0, 0.0, 1.0);
		glBegin(GL_LINE_STRIP);
		for(int i = -200; i < 200; i++)
		{
			glVertex2f((i) , (sin((double)i/s)*m));
		}
		glEnd();
		glColor4f(1.0, 1.0, 0.0, 1.0);
		glRectd((j) + 2, (sin((double)j/s)*m) + 2, (j) - 2, (sin((double)j/s)*m) - 2);
		break;

	case SPR:
		glColor4f(1.0, 0.0, 1.0, 1.0);
		//glBegin(GL_LINE_STRIP);
		for(float i = -30; i < 30; i+= 0.1)
		{
			glColor4f((i+30.f)/60.f, 0.0, 1.0, 1.0);
			glBegin(GL_LINE_STRIP);
			int x = cos((double)i) * 50;
			int y = -sin((double)i) * 50;
			glVertex2f(x + (i*10) , y);

			x = cos((double)(i+0.1)) * 50;
			y = -sin((double)(i+0.1)) * 50;
			glVertex2f(x + ((i+0.1)*10) , y);
			glEnd();
		}
		{
			static float j = -30;
			int x = cos((double)j) * 50;
			int y = -sin((double)j) * 50;

			glRectd((x + (j * 10)) + 2, y + 2, (x + (j * 10)) - 2, y - 2);	
			glRectd((+ (j * 10)) + 2, + 2, (+ (j * 10)) - 2, - 2);

			glBegin(GL_LINES);
			glVertex2f(x + (j * 10), y);
			glVertex2f(j * 10, 0);
			glEnd();

			j += 0.1;

			if(j > 30)
				j = -30;
		}
		//glEnd();
		break;

	case QUD:
		glColor4f(1.0, 0.0, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(-100, -100);
		glVertex2f(100, -100);
		glVertex2f(100, 100);
		glVertex2f(-100, 100);
		glEnd();
		break;

	default:
		break;
	}
	j++;

	glLoadIdentity();

	glRectd(2, 2, -2, -2);

	
	glutSwapBuffers();
}

GLvoid reshape ( int w, int h )
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();

	glOrtho(-((double)w/2), (double)w/2, -((double)h/2), (double)h/2, -1.0, 1.0);

	/*gluLookAt(0.0, 0.0, 0.0,
		0.0, 0.0, 1.0,
		0.0, 1.0, 0.0);*/

	glMatrixMode(GL_MODELVIEW);
}

GLvoid mouse(int button, int state, int x, int y)
{
	int r_y = HEIGHT - y;
	
}

GLvoid mouseMove(int x, int y)
{
	int r_y = HEIGHT - y;
	
	
}

GLvoid keyBoardFunc(unsigned char key, int x, int y)
{
	switch(key)
	{
	case '1':
		g_shape = COS;
		break;
	case '2':
		g_shape = SIN;
		break;
	case '3':
		g_shape = SPR;
		break;
	case '4':
		g_shape = QUD;
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
	case 'r':
		g_modelAngle++;
		break;
	case 'R':
		g_worldAngle++;
		break;
	case 'm':
		g_Shearing_x -= 0.1;
		break;
	case 'M':
		g_Shearing_x += 0.1;
		break;
	case 'n':
		g_Shearing_y -= 0.1;
		break;
	case 'N':
		g_Shearing_y += 0.1;
		break;
	case 's':
		g_worldScale -= 0.1;
		break;
	case 'S':
		g_worldScale += 0.1;
		break;
	case 'c':
		g_scale -= 0.1;
		break;
	case 'C':
		g_scale += 0.1;
		break;

	default:
		break;
	}
	printf("%c\n", key);
	glutPostRedisplay();
}

GLvoid timerFunc(int val)
{
	glutPostRedisplay();
	glutTimerFunc( 16, timerFunc, 1 );
}

GLvoid specialKeyBoardFunc(int key, int x, int y)
{
	// left : 100 / up : 101 / right : 102 / down : 103
	
}