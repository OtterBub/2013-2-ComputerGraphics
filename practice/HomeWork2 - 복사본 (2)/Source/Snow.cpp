#include "Snow.h"

void Snow::Draw() 
{
	Object3D::Draw();

	switch(type)
	{
	case SNOW:
		glColor3f(1, 1, 1);
		glutWireSphere(2.5, 4, 4);
		glColor3f(0, 0, 0);
		glutSolidSphere(2.5, 4, 4);
		break;
	case RAIN:
		glPushMatrix();
		glScalef(1, 2, 1);
		glColor3f(1, 1, 1);
		glutWireCube(2.5);
		glColor3f(0, 0, 0);
		glutSolidCube(2.5);
		glPopMatrix();
		break;
	default:
		glPushMatrix();
		glScalef(1, 2, 1);
		glColor3f(1, 1, 1);
		glutWireCube(2.5);
		glColor3f(0, 0, 0);
		glutSolidCube(2.5);
		glPopMatrix();
		break;
	}

}

void Snow::Update()
{
	
	switch(type)
	{
	case SNOW:
		point.y --;
		break;
	case RAIN:
		point.y -= 3;
		break;
	default:
		point.y -= 3;
		break;
	}
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