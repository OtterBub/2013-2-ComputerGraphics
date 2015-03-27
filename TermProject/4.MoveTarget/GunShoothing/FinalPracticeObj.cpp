#include "FinalPracticeObj.h"

// ----------- MiracleCube Class Func -------------

MiracleCube::MiracleCube(TKpoint setPosition) :
	Object(setPosition)
{}
MiracleCube::~MiracleCube(){}

void MiracleCube::draw()
{
	Object::draw();

	glPushMatrix(); {	
		glRotatef(m_angle, 0, 1, 0);
		glColor4f(1, 1, 1, 1);
		glutSolidCube(25);

		glLineWidth(2);
		glColor4f(0, 0, 0, 1);
		glutWireCube(25);

	} glPopMatrix();

	glEnable(GL_BLEND);

	glPushMatrix(); {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
		glColor4f(0, 0, 1, 0.8);
		glRotatef(45, 1, 0, 0);
		glRotatef(45, 0, 0, 1);
		glutSolidCube(50);

	} glPopMatrix();

	glLineWidth(1);

	glDisable(GL_BLEND);

	if(m_picking) {
		drawStrokeText(0, 200, 0, 0.3, "Picking!");
	}

}
void MiracleCube::update()
{
	m_angle++;
}

// ----------- Pond Class Func -------------

Pond::Pond(TKpoint setPosition) :
	Object(setPosition)
{
	m_pondSize = 50;
	m_SurfaceHeight = 0;
	m_bWave= true;
}
Pond::~Pond(){}

void Pond::draw()
{
	Object::draw();

	float tempScale = 5;

	glTranslatef(0, 10, 0);

	glPushMatrix();
	glColor4f(0, 0.5, 0.5, 1);
	glTranslatef(-60, 0, 0);
	glScalef(1, 1, tempScale);
	glutSolidCube(20);
	glColor4f(1, 1, 0, 1);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glColor4f(0, 0.5, 0.5, 1);
	glScalef(1, 1, tempScale);
	glTranslatef(+60, 0, 0);
	glutSolidCube(20);
	glColor4f(1, 1, 0, 1);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glColor4f(0, 0.5, 0.5, 1);
	glScalef(tempScale, 1, 1);
	glTranslatef(0, 0, 60);
	glutSolidCube(20);
	glColor4f(1, 1, 0, 1);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glColor4f(0, 0.5, 0.5, 1);
	glScalef(tempScale, 1, 1);
	glTranslatef(0, 0, -60);
	glutSolidCube(20);
	glColor4f(1, 1, 0, 1);
	glutWireCube(20);
	glPopMatrix();

	float ctrlpoints[3][3][3] = {
		{{-m_pondSize, -m_SurfaceHeight/2, -m_pondSize},		{0, m_SurfaceHeight, -m_pondSize},		{m_pondSize, -m_SurfaceHeight/2, -m_pondSize}},

		{{-m_pondSize, -m_SurfaceHeight, 0},				{0, m_SurfaceHeight/2, 0},				{m_pondSize, -m_SurfaceHeight, 0}},

		{{-m_pondSize, -m_SurfaceHeight/2, m_pondSize},		{0, m_SurfaceHeight, m_pondSize},		{m_pondSize, -m_SurfaceHeight/2, m_pondSize}}
	};

	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);

	glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);

	glColor3f(0.0, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 10, 0, 10);

	glLineWidth(2);
	glColor3f(0.5, 0.0, 0.0);
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);

	glDisable(GL_MAP2_VERTEX_3);

	glLineWidth(1);

	if(m_picking) {
		drawStrokeText(0, 200, 0, 0.3, "Picking!");
	}
}
void Pond::update()
{
	if(m_bWave)
		m_SurfaceHeight++;
	else
		m_SurfaceHeight--;

	if(m_SurfaceHeight > 25)
		m_bWave = false;
	else if(m_SurfaceHeight < -25)
		m_bWave = true;
}

// ----------- Hammock Class Func -------------

Hammock::Hammock(TKpoint setPosition) :
	Object(setPosition)
{
	m_swingRight = true;
}
Hammock::~Hammock(){}

void Hammock::draw()
{
	Object::draw();

	glColor4f(0, 1, 0.5, 1);
	glutSolidSphere(10, 10, 10);

	glColor4f(0, 0, 0.5, 1);
	glBegin(GL_LINES);

	glVertex3f(0, 0, 0);
	glVertex3f(-20, -50, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(+20, -50, 0);

	glEnd();

	glColor4f(1, 1, 0, 1);
	glTranslatef(0, -50, 0);
	glScalef(2, 0.5, 1);
	glutWireCube(20);

	glColor4f(0.5, 0.5, 0.5, 1);
	glScalef(0.5, 2, 1);
	glTranslatef(0, 10, 0);
	glutSolidSphere(10, 10, 10);
	glTranslatef(0, 10, 0);
	glutSolidSphere(5, 10, 10);

	if(m_picking) {
		drawStrokeText(0, 200, 0, 0.3, "Picking!");
	}

}
void Hammock::update()
{
	if(m_swingRight)
		m_angleZ++;
	else
		m_angleZ--;

	if(m_angleZ > 30)
		m_swingRight = false;
	else if(m_angleZ < -30)
		m_swingRight = true;
}

// ----------- Kid Class Func -------------

Kid::Kid(TKpoint setPosition) :
	Object(setPosition)
{
	TKpoint temp = {0, };
	
	m_state = kidState::ORIGIN;
	m_velocity = temp;
	m_jump = false;
}
Kid::~Kid(){}

void Kid::ChangeState() {

	switch(m_state) {
	case kidState::ORIGIN :
		m_state = 1 + rand() % 4;
		break;
	case kidState::RIGHT :
	case kidState::LEFT :
	case kidState::DOWN :
	case kidState::UP :
		m_state = kidState::ORIGIN;
	default:
		break;
	}
}

void Kid::Jump(int dir)
{
	switch(dir) {
	case kidState::ORIGIN :
		m_velocity.x = -m_velocity.x;
		m_velocity.z = -m_velocity.z;
		break;
	case kidState::RIGHT :
		m_velocity.z = 0;
		m_velocity.x = 1;
		break;
	case kidState::LEFT :
		m_velocity.z = 0;
		m_velocity.x = -1;
		break;
	case kidState::DOWN :
		m_velocity.x = 0;
		m_velocity.z = 1;
		break;
	case kidState::UP :
		m_velocity.x = 0;
		m_velocity.z = -1;
		break;
	default:
		break;
	}
	m_velocity.y = 3;
	m_jump = true;
}

void Kid::draw()
{
	Object::draw();
	glRotatef(-90, 1, 0, 0);
	glutWireCone(25, 50, 10, 10);
}
void Kid::update()
{
	m_position.x += m_velocity.x;
	m_position.y += m_velocity.y;
	m_position.z += m_velocity.z;

	m_velocity.y -= 0.1;

	if( m_velocity.y < 0 ) {
		m_jump = false;
	}
	if( m_position.y <= 0 ) {
		m_position.y = 0;
		ChangeState();
		Jump(m_state);
	}
}


// ----------- Ground Class Func -------------

Ground::Ground(TKpoint setPosition) :
	Object(setPosition)
{}
Ground::~Ground(){}

void Ground::draw()
{
	Object::draw();

	TEXTURE.drawTextureBegin(TEXTURE_GROUND);

	glBegin(GL_POLYGON);

	glColor4f(1, 1, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-m_groundSize, 0, -m_groundSize);
	glTexCoord2f(0, 0);
	glVertex3f(-m_groundSize, 0, +m_groundSize);
	glTexCoord2f(1, 1);
	glVertex3f(+m_groundSize, 0, +m_groundSize);
	glTexCoord2f(0, 1);
	glVertex3f(+m_groundSize, 0, -m_groundSize);

	glEnd();

	TEXTURE.drawTextureEnd();
}
void Ground::update()
{
	
}

// ----------- Wall Class Func -------------

Wall::Wall(TKpoint setPosition) :
	Object(setPosition)
{
	m_wallSize = 50;
}
Wall::~Wall()
{
}

void Wall::draw()
{
	Object::draw();

	TEXTURE.drawTextureBegin(TEXTURE_STONE_WALL);
	//TEXTURE.drawTextureBegin(TEXTURE_CRACK_PILLAR);
	
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-m_wallSize, 0, 0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(m_wallSize, 0, 0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(m_wallSize, m_wallSize, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-m_wallSize, m_wallSize, 0);

	glEnd();

	TEXTURE.drawTextureEnd();

	if(m_picking) {
		drawStrokeText(0, 200, 0, 0.3, "Picking!");
	}
}
void Wall::update()
{
}