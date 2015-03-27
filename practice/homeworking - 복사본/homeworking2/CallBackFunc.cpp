#include "CallBackFunc.h"

#define TRIANGLE	0
#define RECTANGLE	1



World* world = new World();



struct Wall{
	POINT point[4];
	GLfloat x[4];
	GLfloat y[4];
};

struct TRI{
	POINT point[3];
	GLfloat x;
	GLfloat y;
	GLfloat scaleX;
	GLfloat scaleY;
	GLfloat width;
	GLfloat height;
	GLint	angle;

};

void print2f(GLfloat (*arr)[2], int vertexNum, int BeginMode = GL_POLYGON) {
	glBegin(GL_POLYGON);
	for(int i = 0; i < vertexNum; i++){
		glVertex2fv(arr[i]);
	}
	glEnd();
}

TRI tri;

float g_scaleX = 1, g_scaleY = 1;
int g_angle = 0;

GLvoid drawScene ( GLvoid )
{
	glClearColor( 0.0f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	GLfloat mviewMat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mviewMat);
	static Wall wall;
	static TRI GoalTRI;
	static bool init = 1;

	if(init){
		init = 0;
		tri.x = 100;
		tri.y = 100;
		tri.scaleX = 1;
		tri.scaleY = 1;
		tri.angle = 0;
		tri.width = 100;
		tri.height = 50;

		GoalTRI = tri;

		GoalTRI.angle = rand() % 360;
		GoalTRI.scaleX = rand() % 3 + 1;
		GoalTRI.scaleY = rand() % 3 + 1;
		//GoalTRI.x = 


	}	

	wall.point[0].x = -200;
	wall.point[0].y = -200;

	wall.point[1].x = 200;
	wall.point[1].y = -200;

	wall.point[2].x = 200;
	wall.point[2].y = 200;

	wall.point[3].x = -200;
	wall.point[3].y = 200;

	static float wallAngle = 0;
	for(int i = 0; i < 4; i++){
		float tempx = wall.point[i].x;
		wall.point[i].x = ((cos(wallAngle * (3.14/180)) * wall.point[i].x) + (-sin(wallAngle * (3.14/180)) * wall.point[i].y));
		wall.point[i].y = ((sin(wallAngle * (3.14/180)) * tempx) + (cos(wallAngle * (3.14/180)) * wall.point[i].y));
	}

	for(int i = 0; i < 4; i++){
		wall.point[i].x = wall.point[i].x + 400;
		wall.point[i].y = wall.point[i].y + 300;
	}

	float tri_x[3] = {- 50.f,+ 50.f, 0.0f};
	float tri_y[3] = {0.0f, 0.0f, + 50.f};
	POINT tempPT[3];
	for(int i = 0; i < 3; i++){
		tempPT[i].x = tri_x[i];
		tempPT[i].y = tri_y[i];
	}

	for(int i = 0; i < 3; i++){
		tri.point[i] = SRTconvertToPoint(tempPT[i], tri.scaleX, tri.scaleY, tri.angle, tri.x, tri.y);
	}

	for(int i = 0; i < 3; i++){
		int k = i+1;
		if(k >= 3)
			k = 0;
		for( int j = 0; j < 3; j++){

			if(LineLineCollision(tri.point[i], tri.point[k], wall.point[j], wall.point[j+1]))
				printf("collision!\n");
		}
	}

	for(int i = 0; i < 3; i++){
		tri.point[i].areaBit = 0;
		if(tri.point[i].x < wall.point[0].x){
			tri.point[i].areaBit |= 0x0001;
		}
		if(tri.point[i].x > wall.point[1].x){
			tri.point[i].areaBit |= 0x0010;
		}

		if(tri.point[i].y < wall.point[1].y){
			tri.point[i].areaBit |= 0x0100;
		}

		if(tri.point[i].y > wall.point[2].y){
			tri.point[i].areaBit |= 0x1000;
		}

		printf("%d point::areabit %04x \n", i, tri.point[i].areaBit);
		printf("%d point::(%f, %f) \n", i, tri.point[i].x, tri.point[i].y);
	}

	POINT temp[20] = {0, };
	int ClippingCount = 0;
	for(int i = 0; i < 3; i++){
		int k = i+1;
		if(k >= 3)
			k = 0;
		unsigned short tempAreaBit = 0;
		unsigned short CalAreaBit = 0;
		tempAreaBit = (tri.point[i].areaBit & tri.point[k].areaBit);
		CalAreaBit = (tri.point[i].areaBit | tri.point[k].areaBit);
		if(tempAreaBit){
			continue;
		}

		if(CalAreaBit == 0x0000){
			temp[ClippingCount++] = tri.point[i];
			temp[ClippingCount++] = tri.point[k];
		} else {

			if(tri.point[i].areaBit == 0x0000){
				temp[ClippingCount++] = tri.point[i];
			}

			for(int j = 0; j < 4; j++){
				int z = j+1;
				if(z >= 4)
					z = 0;
				temp[ClippingCount] = LineCrossPoint(tri.point[i], tri.point[k], wall.point[j], wall.point[z]);
				if(temp[ClippingCount].x || temp[ClippingCount].y){
					ClippingCount++;
				}
			}

			if(tri.point[k].areaBit == 0x0000){
				temp[ClippingCount++] = tri.point[k];
			}
		}

	}


	glPushMatrix();
	{
		/*glColor3f(1, 0, 1);
		glBegin(GL_POLYGON);
		for(int i = 0; i < 4; i++)
		{
		glVertex2f(wall.point.x[i], wall.point.y[i]);
		}
		glEnd();*/
		glColor3f(1, 0, 0);
		glBegin(GL_LINE_STRIP);
		for(int i = 0; i < 4; i++)
		{
			glVertex2f(wall.point[i].x, wall.point[i].y);
		}
		glEnd();

	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(tri.x, tri.y, 0.0);
		glRotatef(tri.angle, 0.0, 0.0, 1.0f);
		glScalef(tri.scaleX, tri.scaleY, 1.0);

		glColor3f(0, 1, 0);
		glBegin(GL_POLYGON);
		glVertex2f(- 50.f, 0.0);
		glVertex2f(+ 50.f, 0.0);
		glVertex2f(0.0, + 50.f);
		glEnd();

		glColor3f(0, 1, 1);
		glBegin(GL_LINE_LOOP);
		glVertex2f(- 50.f, 0.0);
		glVertex2f(+ 50.f, 0.0);
		glVertex2f(0.0, + 50.f);
		glEnd();

		/*glGetFloatv(GL_MODELVIEW_MATRIX, mviewMat);
		for(int i = 0; i < 4; i++){
		printf("%f %f %f %f \n", mviewMat[(i)], mviewMat[(i)+4], mviewMat[(i)+8], mviewMat[(i)+12]);
		}
		printf("\n\n");

		printf("cos(%d)::%lf sin(%d)::%lf\n\n", g_angle, cos(g_angle * (3.14/180)), g_angle, sin(g_angle * (3.14/180)), g_angle);*/
	}
	glPopMatrix();

	glLoadIdentity();
	glLineWidth(1);
	glColor3f(1.0f, 0, 0);
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < 3; i++) {
		glVertex2f(tri.point[i].x, tri.point[i].y);
	}
	glEnd();

	glLineWidth(3);
	glBegin(GL_POLYGON);
	for(int i = 0; i < ClippingCount; i++)
		glVertex2f(temp[i].x, temp[i].y);
	glEnd();

	world->draw();
	glutSwapBuffers();
}

GLvoid reshape ( int w, int h )
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, w, 0, h, -1.0, 1.0);

	/*gluLookAt(0.0, 0.0, 0.0,
	0.0, 0.0, 1.0,
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
	

}

GLvoid keyBoardFunc(unsigned char key, int x, int y)
{
	const int objSpeed = 3;
	switch(key)
	{
	case 'a':
		tri.x-=objSpeed;
		break;
	case 'd':
		tri.x+=objSpeed;
		break;
	case 'w':
		tri.y+=objSpeed;
		break;
	case 's':
		tri.y-=objSpeed;
		break;
	case 't':
		tri.scaleX--;
		break;
	case 'T':
		tri.scaleX++;
		break;
	case 'g':
		tri.scaleY--;
		break;
	case 'G':
		tri.scaleY++;
		break;
	case 'r':
		tri.angle++;
		break;
	default:
		break;
	}
}

GLvoid timerFunc(int val)
{
	glutPostRedisplay();
	glutTimerFunc( 16, timerFunc, 1 );
}

GLvoid specialKeyBoardFunc(int key, int x, int y)
{
	// left : 100 / up : 101 / right : 102 / down : 103
	switch(key)
	{
	case 101:
		world->allPlusVelocity();
		break;
	case 103:
		world->allMinorVelocity();
		break;
	}
	printf("%d\n", key);
}