#include "BoxStageObject.h"

// --------------- Ball ---------------

void Ball::Draw()
{
	Object3D::Draw();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glBindTexture(GL_TEXTURE_2D, textures[1]);

	//if(!m_onlyLine){
		glColor3f(r, g, b);
		glutSolidSphere(10, 10, 10);
	
	/*glColor3f(1 - r, 1 - g, 1 -b);
	glutWireSphere(10, 10, 10);*/

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

	if(m_bTeleport){
		char display[100];
		sprintf(display, "%.1f%%", (((clock() - m_teleportTime) / (float)2000) * 100 ));
		drawStrokeText(display, 0, 15, 0, 0.10);
	}

	if(m_debug){
		char debug[100];
		sprintf(debug, "vel(%.2f, %.2f, %.2f)", m_velocity.x, m_velocity.y, m_velocity.z);
		drawStrokeText(debug, 0, 40, 0, 0.10);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
		glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
		glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
		glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
		glEnd();	

		glBegin(GL_LINE_LOOP);
		glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
		glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
		glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
		glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
		glEnd();	

		glBegin(GL_LINE_LOOP);
		glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
		glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
		glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
		glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
		glEnd();	

		glBegin(GL_LINE_LOOP);
		glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
		glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
		glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
		glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
		glEnd();	

		glBegin(GL_LINE_LOOP);
		glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
		glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
		glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
		glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
		glEnd();	

		glBegin(GL_LINE_LOOP);
		glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
		glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
		glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
		glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
		glEnd();
	}
}
void Ball::Update()
{
	ObjectControlPosition(m_velocity.x, m_velocity.y, m_velocity.z);

	m_CollisionBox.Max.x = point.x + 10;
	m_CollisionBox.Min.x = point.x - 10;

	m_CollisionBox.Max.y = point.y + 10;
	m_CollisionBox.Min.y = point.y - 10;

	m_CollisionBox.Max.z = point.z + 10;
	m_CollisionBox.Min.z = point.z - 10;

	if(m_bTeleport) {
		if(2000 < clock() - m_teleportTime)
			m_bTeleport = false;
	}
}

void Ball::SetTeleportState(bool _set) 
{ 
	m_bTeleport = _set; 

	if(_set)
		m_teleportTime = clock();
}

bool Ball::Bound(CollisionBox Box)
{
	bool reval = false;
	CollisionBox temp = m_CollisionBox;

	temp.Max.x += m_velocity.x;
	temp.Min.x += m_velocity.x;

	if(CollisionCheck(temp, Box)){
		m_velocity.x = -(m_velocity.x / 2);
		reval = true;
	}

	temp = m_CollisionBox;

	temp.Max.y += m_velocity.y;
	temp.Min.y += m_velocity.y;

	if(CollisionCheck(temp, Box)){
		m_velocity.y = -(m_velocity.y / 2);
		reval = true;
	}

	temp = m_CollisionBox;

	temp.Max.z += m_velocity.z;
	temp.Min.z += m_velocity.z;

	if(CollisionCheck(temp, Box)){
		m_velocity.z = -(m_velocity.z / 2);
		reval = true;
	}

	return reval;
}

void Ball::AddVelocity(float _x, float _y, float _z)
{
	if((m_velocity.x + _x <= m_MaxVelocity) && (m_velocity.x + _x >= -m_MaxVelocity)) {
		m_velocity.x += _x;
	} else if ( m_velocity.x < 0) {
		m_velocity.x = -m_MaxVelocity;
	} else if ( m_velocity.x > 0) {
		m_velocity.x = m_MaxVelocity;
	}

	if((m_velocity.y + _y <= m_MaxVelocity) && (m_velocity.y + _y >= -m_MaxVelocity)) {
		m_velocity.y += _y;
	} else if ( m_velocity.y < 0) {
		m_velocity.y = -m_MaxVelocity;
	} else if ( m_velocity.y > 0) {
		m_velocity.y = m_MaxVelocity;
	}

	if((m_velocity.z + _y <= m_MaxVelocity) && (m_velocity.z + _y >= -m_MaxVelocity)) {
		m_velocity.z += _z;
	} else if ( m_velocity.z < 0) {
		m_velocity.z = -m_MaxVelocity;
	} else if ( m_velocity.z > 0) {
		m_velocity.z = m_MaxVelocity;
	}
}

void Ball::SetVelocity(float _x, float _y, float _z)
{
	m_velocity.x = _x;
	m_velocity.y = _y;
	m_velocity.z = _z;
}

void Ball::ColorChange(float _r, float _g, float _b) 
{
	r = _r;
	g = _g;
	b = _b;
}

// --------------- Wall ---------------
#define WALL_MODE GL_LINE_LOOP
//#define WALL_MODE GL_POLYGON
void Wall::Draw()
{
	
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(m_mode);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0.0, 0.0);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glTexCoord2f(1.0, 0.0);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glTexCoord2f(1.0, 1.0);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glTexCoord2f(0.0, 1.0);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	if(textures[1] != NULL)
		glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(m_mode);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0.0, 0.0);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glTexCoord2f(1.0, 0.0);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glTexCoord2f(1.0, 1.0);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glTexCoord2f(0.0, 1.0);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	if(textures[2] != NULL)
		glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(m_mode);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0, 0.0);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glTexCoord2f(1.0, 0.0);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glTexCoord2f(1.0, 1.0);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glTexCoord2f(0.0, 1.0);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();
	
	if(textures[3] != NULL)
		glBindTexture(GL_TEXTURE_2D, textures[3]);
	glBegin(m_mode);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0.0, 0.0);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glTexCoord2f(1.0, 0.0);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glTexCoord2f(1.0, 1.0);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glTexCoord2f(0.0, 1.0);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glEnd();

	if(textures[4] != NULL)
		glBindTexture(GL_TEXTURE_2D, textures[4]);
	glBegin(m_mode);
	glNormal3f(1, 0, 0);
	glTexCoord2f(0.0, 0.0);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glTexCoord2f(1.0, 0.0);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glTexCoord2f(1.0, 1.0);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glTexCoord2f(0.0, 1.0);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	if(textures[5] != NULL)
		glBindTexture(GL_TEXTURE_2D, textures[5]);
	glBegin(m_mode);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0.0, 0.0);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glTexCoord2f(1.0, 0.0);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glTexCoord2f(1.0, 1.0);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glTexCoord2f(0.0, 1.0);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glEnd();	

	glDisable(GL_TEXTURE_2D);

	glColor3f(1, 1, 1);
	glBegin(WALL_MODE);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(WALL_MODE);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(WALL_MODE);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(WALL_MODE);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(WALL_MODE);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(WALL_MODE);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glEnd();
}
void Wall::Update()
{
	
}

// --------------- COLWALL ------------

void ColorWall::Draw()
{
	
	glBegin(m_mode);
	glNormal3f(0, 0, -1);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(m_mode);
	glNormal3f(-1, 0, 0);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(m_mode);
	glNormal3f(0, 1, 0);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();

	glBegin(m_mode);
	glNormal3f(0, -1, 0);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glEnd();

	glBegin(m_mode);
	glNormal3f(1, 0, 0);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(m_mode);
	glNormal3f(0, 0, 1);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glEnd();	


	glColor3f(1, 1, 1);
	glBegin(WALL_MODE);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(WALL_MODE);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(WALL_MODE);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(WALL_MODE);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(WALL_MODE);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(WALL_MODE);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glEnd();
}
void ColorWall::Update()
{
	
}