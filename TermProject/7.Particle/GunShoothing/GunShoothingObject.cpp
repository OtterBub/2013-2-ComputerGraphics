#include "GunShoothingObject.h"

// ------------------ Target ------------------------
Target::Target(TKpoint setPosition) :
	Object(setPosition)
{
	m_start_position = m_position;
	m_end_position = m_position;
	m_movingSpeed = 0;
	m_moveState = movingState::PLAY;
	
	m_timer = 0;

	m_autoReverse = false;
	m_shootable = false;
}

Target::~Target() {

}

void Target::set_end_position(TKpoint set_end) {
	m_end_position = set_end;
	m_movingSpeed = 1;
}
void Target::set_end_position(TKpoint set_end, float speed) {
	m_end_position = set_end;
	m_movingSpeed = speed;
}

void Target::moveReversing(bool _auto, int timer) {
	m_autoReverse = _auto;
	m_timer = timer;
}

void Target::playMoving() {
	TKpoint unitVector;

	unitVector = getUnitVector(m_position, m_end_position);

	if( !( (abs(unitVector.x) == 0) && (abs(unitVector.y) == 0) && (abs(unitVector.z) == 0) ) ){

		addPosition(unitVector.x * m_movingSpeed, unitVector.y * m_movingSpeed, unitVector.z * m_movingSpeed);

	} else if ( m_autoReverse ) {
		m_moveState = movingState::REVERSE;
	}
}

void Target::reverseMoving() {
	TKpoint unitVector;

	unitVector = getUnitVector(m_position, m_start_position);

	if( !( (abs(unitVector.x) == 0) && (abs(unitVector.y) == 0) && (abs(unitVector.z) == 0) ) ){

		addPosition(unitVector.x * m_movingSpeed, unitVector.y * m_movingSpeed, unitVector.z * m_movingSpeed);

	} else if ( m_autoReverse ) {
		m_moveState = movingState::PLAY;
	}
}

void Target::draw() {
	Object::draw();
	TEXTURE.drawTextureBegin(TEXTURE_TARGET);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-25, 0, 0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(25, 0, 0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(25, 50, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-25, 50, 0);
	glEnd();

	TEXTURE.drawTextureEnd();

	if(m_picking) {
		drawStrokeText(0, 200, 0, 0.3, "Picking!");
	}
}

void Target::update() {
	if(m_picking) {
		m_destroy = true;
	}
	switch(m_moveState) {
	case movingState::PLAY :
		playMoving();
		break;
	case movingState::REVERSE :
		reverseMoving();
		break;
	default:
		break;
	}
}

bool Target::pickingCheck(TKpoint pick) {
	if(abs(m_viewPosition.x - pick.x) < 25 &&
		abs((m_viewPosition.y + 25) - pick.y) < 25){
		return true;
	}

	return false;
}

// ------------------ Particle ------------------------

Particle::Particle(TKpoint setPosition) :
	Object(setPosition)
{
	m_vel.x = rand() % 20 - 10;
	m_vel.y = rand() % 5;
	m_vel.z = rand() % 20 - 10;
}
Particle::~Particle() {

}

void Particle::draw() {
	Object::draw();
	glColor4f(0.8, 0.5, 0, 1);
	glutSolidCube(10);
	glLineWidth(2);
	glColor4f(1, 1, 1, 1);
	glutSolidCube(10);
	glLineWidth(1);
}
void Particle::update() {
	if(m_position.y < 1)
		m_destroy = true;

	m_vel.y -= 0.2;
	m_vel.x /= 1.1;
	m_vel.z /= 1.1;

	m_position.x += m_vel.x;
	m_position.y += m_vel.y;
	m_position.z += m_vel.z;
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

	
	glPopMatrix();
	TEXTURE.drawTextureEnd();
}
void Pillar::update() {

	m_picking = false;
}

bool Pillar::pickingCheck(TKpoint pick) {
	if( (m_viewPosition.x - 25 < pick.x) && (m_viewPosition.x + 25 > pick.x) &&
		(m_viewPosition.y < pick.y) && (m_viewPosition.y + 200 > pick.y)){
			return true;
	}
	return false;
}

// ------------------ IronBarrel ------------------------

IronBarrel::IronBarrel(TKpoint setPosition) :
	Object(setPosition)
{
}
IronBarrel::~IronBarrel() {
}

void IronBarrel::draw() {
	
	Object::draw();

	glPushMatrix();
	
	for(int j = 0; j < 2; j++) {
		glPushMatrix();

		glTranslatef(0, 0, 30);
		TEXTURE.drawTextureBegin(TEXTURE_BARREL);

		for(int i = 0; i < 4; i++){
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-40, 0, 0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(40, 0, 0);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(40, 80, 0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(-40, 80, 0);
			glEnd();
			glRotatef(90, 0, 1, 0);
			glTranslatef(40, 0, 40);
		}

		TEXTURE.drawTextureEnd();
		glPopMatrix();
		glRotatef(45, 0, 1, 0);
	}
	glPopMatrix();

}
void IronBarrel::update() {
}
bool IronBarrel::pickingCheck(TKpoint pick) {

	return false;
}