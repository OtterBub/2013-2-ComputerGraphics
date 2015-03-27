#include "Char.h"

void Mainchar::Draw(){
	Object3D::Draw();
	const float OBJSIZE = 80;

	if(m_bDead){
		if(m_Scale > 0)
		m_Scale-= 0.01;
	}
	glPushMatrix();

	glScalef(m_Scale, m_Scale, m_Scale);
	glTranslatef(0.0, OBJSIZE / 1.5, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glutWireCube(OBJSIZE);

	static int angle = 0;
	angle-= 5;
	glPushMatrix();
	{
		glTranslatef(OBJSIZE / 2, -(OBJSIZE / 1.5), OBJSIZE / 2);
		glPushMatrix();
		glRotatef(angle, 1.0, 0.0, 0.0);
		glutWireSphere(OBJSIZE / 4, 10, 10);
		glPopMatrix();

		glTranslatef(0.0, 0.0, - OBJSIZE);
		glRotatef(angle, 1.0, 0.0, 0.0);
		glutWireSphere(OBJSIZE / 4, 10, 10);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-OBJSIZE / 2, -(OBJSIZE / 1.5), OBJSIZE / 2);
		glPushMatrix();
		glRotatef(angle, 1.0, 0.0, 0.0);
		glutWireSphere(OBJSIZE / 4, 10, 10);
		glPopMatrix();

		glTranslatef(0.0, 0.0, - OBJSIZE);
		glRotatef(angle, 1.0, 0.0, 0.0);
		glutWireSphere(OBJSIZE / 4, 10, 10);
	}
	glPopMatrix();

	glPopMatrix();
	static float explo = 1;
	if(m_bDead){
		glPushMatrix();
		{
			glutWireSphere(explo += 1.0, 10, 10);
		}
		glPopMatrix();
	} else {
		explo = 1;
	}
}

void Mainchar::Update(){
	m_pJumpState->Execute(this);
	m_pMoveState->Execute(this);
}