#include "Pyramid.h"

void Pyramid::Draw(){
	Object3D::Draw();
	glScalef(scale, scale, scale);
	glPushMatrix();
	{
		glBegin(GL_QUADS);
		glColor3f(0, 0, 0);
		glVertex3f(-10, 0, -10);
		glColor3f(0, 0, 1);
		glVertex3f(-10, 0, 10);
		glColor3f(1, 0, 1);
		glVertex3f(10, 0, 10);
		glColor3f(1, 0, 0);
		glVertex3f(10, 0, -10);

		glColor3f(0, 0, 0);
		glVertex3f(-10, 0, -10);
		glColor3f(0, 0, 1);
		glVertex3f(-10, 0, 10);
		glColor3f(0, 1, 1);
		glVertex3f(-10, 20, 10);
		glColor3f(0, 1, 0);
		glVertex3f(-10, 20, -10);

		glColor3f(0, 0, 0);
		glVertex3f(-10, 0, -10);
		glColor3f(0, 1, 0);
		glVertex3f(-10, 20, -10);
		glColor3f(1, 1, 0);
		glVertex3f(10, 20, -10);
		glColor3f(1, 0, 0);
		glVertex3f(10, 0, -10);

		glColor3f(1, 0, 0);
		glVertex3f(10, 0, -10);
		glColor3f(1, 1, 0);
		glVertex3f(10, 20, -10);
		glColor3f(1, 1, 1);
		glVertex3f(10, 20, 10);
		glColor3f(1, 0, 1);
		glVertex3f(10, 0, 10);

		glColor3f(1, 0, 1);
		glVertex3f(10, 0, 10);
		glColor3f(1, 1, 1);
		glVertex3f(10, 20, 10);
		glColor3f(0, 1, 1);
		glVertex3f(-10, 20, 10);
		glColor3f(0, 0, 1);
		glVertex3f(-10, 0, 10);

		if(cover){
			glColor3f(0, 1, 0);
			glVertex3f(-10, 20, -10);
			glColor3f(0, 1, 1);
			glVertex3f(-10, 20, 10);
			glColor3f(1, 1, 1);
			glVertex3f(10, 20, 10);
			glColor3f(1, 1, 0);
			glVertex3f(10, 20, -10);
		}
		glEnd();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glRotatef(rotate, 0, 1, 0);
		glTranslatef(60, 40, 0);
		glColor3f(1, 1, 0);
		glutSolidSphere(10, 10, 10);
		glColor3f(0, 0, 1);
		glutWireSphere(10, 10, 10);

		glPushMatrix();
		{
			glRotatef(rotate * 2, 0, 1, 0);
			glTranslatef(20, 0, 0);
			glColor3f(0, 1.0, 1);
			glutSolidSphere(5, 10, 10);
			glColor3f(1, 0, 0);
			glutWireSphere(5, 10, 10);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void Pyramid::Update(){
	rotate = (int)(rotate + 1) % 360;
}