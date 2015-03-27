#include "Pyramid.h"

void Pyramid::Draw(){
	Object3D::Draw();

	glEnable(GL_TEXTURE_2D);

	glScalef(scale, scale, scale);
	glPushMatrix();
	for(int i = 0; i < 4; i++){
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glRotatef(90 * i, 0, 1.0, 0);
		glBegin(GL_POLYGON);

		glTexCoord2f(0.5, 1.0);
		glColor3f(1.0, 0.0, 0.0);
		glNormal3f(0, 0, 1);
		glVertex3f(0, 60, 0);
		glTexCoord2f(0.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(-30, 0, 30);
		glTexCoord2f(1.0, 0.0);
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
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glColor3f(1, 1, 1);
		glRotatef(rotate, 0, 1, 0);
		glTranslatef(60, 40, 0);
		//glColor3f(1, 1, 0);
		glutSolidSphere(10, 10, 10);
		//glColor3f(0, 0, 1);
		glutWireSphere(10, 10, 10);

		glPushMatrix();
		{
			glRotatef(rotate * 2, 0, 1, 0);
			glTranslatef(20, 0, 0);
			//glColor3f(0, 1.0, 1);
			glutSolidSphere(5, 10, 10);
			//glColor3f(1, 0, 0);
			glutWireSphere(5, 10, 10);
		}
		glPopMatrix();
		
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Pyramid::Update(){
	rotate = (int)(rotate + 1) % 360;
}