#include <iostream>
#include <vector>

#include <gl/glut.h>

void drawScene();
void Reshape(int w, int h);
void mouseFunc(int button, int state, int x, int y);

class point{
private:
	float x;
	float y;
	float z;
public:
	point(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
};

// ------------------------------------ 곡선 그려주는 Class ----------------------------------

class CubicCurve {
private:
	std::vector<point*> pointVector;
	bool curveDraw;

public:
	CubicCurve() { curveDraw  = false; }

	void addPoint(point* newPoint) {
		pointVector.push_back(newPoint);
	}

	void CurveDrawOnOff() {
		curveDraw = !curveDraw;
	}

	void draw() {
		glColor3f(0, 0, 1);
		for(std::vector<point*>::iterator it = pointVector.begin(); it != pointVector.end(); it++) {

			glPushMatrix();
			glTranslatef( (*it)->getX(), (*it)->getY(), (*it)->getZ() );
			glutSolidCube(5);
			glPopMatrix();
		}

		if(curveDraw) {
			int index = 0;
			GLfloat ctrlpoints[100][3];
			// 배열에 내가 찍은 점을 넣어주는 부분
			for(std::vector<point*>::iterator it = pointVector.begin(); it != pointVector.end(); it++) {

				ctrlpoints[index][0] = (*it)->getX();
				ctrlpoints[index][1] = (*it)->getY();
				ctrlpoints[index][2] = (*it)->getZ();
				index++;
			}

			glColor3f(1, 0, 0);
			glEnable(GL_MAP1_VERTEX_3);

			// 점 갯수에 따라 for루프 돌려 그려주는 부분
			// size() 함수는 현재 점 갯수를 나타내준다.
			for(int i = 0; i < ((float)pointVector.size() / 3.0f) - 1; i++) 
			{
				glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[i * 3][0]);

				glBegin(GL_LINE_STRIP);
				for(int i = 0; i <= 30; i++){
					glEvalCoord1f((GLfloat)i / 30.0f);
				}
				glEnd();
			}
			glDisable(GL_MAP1_VERTEX_3);
		}
	}
};

// ------------------------------------ 곡선 Class End ----------------------------------

CubicCurve g_curve;

int main()
{
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize(800, 600);
	glutCreateWindow("Cubic Curve");

	glutMouseFunc( mouseFunc );

	glutDisplayFunc( drawScene );
	glutReshapeFunc( Reshape );

	glutMainLoop();

	return 0;
}

void drawScene()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor( 1, 1, 1, 1);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	
	g_curve.draw(); // 곡선 그려주기

	glLoadIdentity();
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, h, 0, -1, 100);

	glMatrixMode(GL_MODELVIEW);
}

void mouseFunc(int button, int state, int x, int y)
{
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN){ // 곡선 그려주는 점 찍기
			printf("(%.2f %.2f) \n", (float)x, (float)y);
			g_curve.addPoint(new point((float)x, (float)y, 0));
			glutPostRedisplay();
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if(state == GLUT_DOWN) // 곡선 그리기 on/off
			g_curve.CurveDrawOnOff();
		glutPostRedisplay();
		break;
	default:
		break;
	}
}