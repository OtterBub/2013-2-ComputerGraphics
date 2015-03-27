#include "Snow.h"

void Snow::Draw() 
{
	Object3D::Draw();

	/*glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex3f(-2.5, -2.5, 0);
	glVertex3f(+2.5, -2.5, 0);
	glVertex3f(+2.5, +2.5, 0);
	glVertex3f(-2.5, +2.5, 0);
	glEnd();*/

	glColor3f(1, 1, 1);
	glutWireSphere(2.5, 4, 4);
	glColor3f(0, 0, 0);
	glutSolidSphere(2.5, 4, 4);
}

void Snow::Update()
{
	point.y --;
}

void GroundSnow::Draw()
{
	Object3D::Draw();
	glColor3f(color, color, color);
	//glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(-5, 0, +5);
	glVertex3f(+5, 0, +5);
	glVertex3f(+5, 0, -5);
	glVertex3f(-5, 0, -5);
	glEnd();
}

void GroundSnow::Update()
{

}