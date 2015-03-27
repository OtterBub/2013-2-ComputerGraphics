#include "Pyramid.h"

void Pyramid::Draw(){
	Object3D::Draw();
	glScalef(scale, scale, scale);
	glPushMatrix();
	for(int i = 0; i < 4; i++){
		glRotatef(90 * i, 0, 1.0, 0);
		glBegin(GL_POLYGON);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0, 60, 0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(-30, 0, 30);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(+30, 0, 30);
		glEnd();

		glColor3f(1.0, 0.0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 60, 0);
		glVertex3f(-30, 0, 30);
		glVertex3f(+30, 0, 30);
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