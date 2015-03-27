#include "GunShoothingObject.h"

// ------------------ Target ------------------------
Target::Target(TKpoint setPosition) :
	Object(setPosition)
{
	m_shootable = false;
}

Target::~Target() {

}

void Target::draw() {
	Object::draw();
	TEXTURE.drawTextureBegin(TEXTURE_TARGET);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-50, 0, 0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(50, 0, 0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(50, 100, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-50, 100, 0);
	glEnd();

	TEXTURE.drawTextureEnd();

	if(m_picking) {
		drawStrokeText(0, 200, 0, 0.3, "Picking!");
	}
}

void Target::update() {

}

bool Target::pickingCheck(TKpoint pick) {
	if(abs(m_viewPosition.x - pick.x) < 25 &&
		abs((m_viewPosition.y + 50) - pick.y) < 25)
		return true;

	return false;
}

// ------------------ Particle ------------------------

Particle::Particle(TKpoint setPosition){

}
Particle::~Particle() {

}

void Particle::draw() {
	Object::draw();

}
void Particle::update() {

}

bool Particle::pickingCheck(TKpoint pick) {
	return false;
}

// ------------------ Pillar ------------------------

Pillar::Pillar(TKpoint setPosition) :
	Object(setPosition)
{

}
Pillar::~Pillar() {

}

void Pillar::draw() {
	Object::draw();
	
	glPushMatrix();
	glTranslatef(0, 0, 30);
	TEXTURE.drawTextureBegin(TEXTURE_CRACK_PILLAR);

	for(int i = 0; i < 4; i++){
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-30, 0, 0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(30, 0, 0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(30, 200, 0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-30, 200, 0);
		glEnd();
		glRotatef(90, 0, 1, 0);
		glTranslatef(30, 0, 30);
	}

	TEXTURE.drawTextureEnd();
	glPopMatrix();
	
}
void Pillar::update() {

	m_picking = false;
}

bool Pillar::pickingCheck(TKpoint pick) {
	if( (m_viewPosition.x - 30 < pick.x) && (m_viewPosition.x + 30 > pick.x) &&
		(m_viewPosition.y < pick.y) && (m_viewPosition.y + 200 > pick.y)){
			return true;
	}
	return false;
}