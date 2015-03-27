#include "BoxStageObject.h"

// --------------- Ball ---------------

void Ball::Draw()
{
	Object3D::Draw();
	
	glColor3f(r, g, b);
	glutWireSphere(10, 10, 10);
	
	if(m_debug){
		char debug[100];
		sprintf(debug, "vel(%.2f, %.2f, %.2f)", m_velocity.x, m_velocity.y, m_velocity.z);
		drawStrokeText(debug, 0, 15, 0, 0.10);
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
}

bool Ball::Bound(CollisionBox Box)
{
	bool reval = false;
	CollisionBox temp = m_CollisionBox;

	temp.Max.x += m_velocity.x;
	temp.Min.x += m_velocity.x;

	if(CollisionCheck(temp, Box)){
		m_velocity.x = -m_velocity.x;
		reval = true;
	}

	temp = m_CollisionBox;

	temp.Max.y += m_velocity.y;
	temp.Min.y += m_velocity.y;

	if(CollisionCheck(temp, Box)){
		m_velocity.y = -m_velocity.y;
		reval = true;
	}

	temp = m_CollisionBox;

	temp.Max.z += m_velocity.z;
	temp.Min.z += m_velocity.z;

	if(CollisionCheck(temp, Box)){
		m_velocity.z = -m_velocity.z;
		reval = true;
	}

	return reval;
}

// --------------- Wall ---------------
#define WALL_MODE GL_LINE_LOOP
//#define WALL_MODE GL_POLYGON
void Wall::Draw()
{
	
	glBegin(m_mode);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(m_mode);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(m_mode);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(m_mode);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(m_mode);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(m_mode);
	glColor3f(r, g, b);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glColor3f(r, g, b);
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
void Wall::Update()
{
	
}