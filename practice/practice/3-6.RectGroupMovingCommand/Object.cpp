#include "Object.h"

Object::Object()
{
	m_width				= 0;
	m_height			= 0;
	m_left				= 0;
	m_right				= 0;
	m_bottom			= 0;
	m_top				= 0;

	m_x					= 0;
	m_y					= 0;

	m_rescale			= 0;
	m_max_Scale			= 0;
	m_min_Scale			= 0;

	m_vel_x				= 0;
	m_vel_y				= 0;
	m_boolMove			= 0;
	m_boolMoveToPoint	= 0;

	m_boolRescale		= 0;
	m_boolAnimation		= 0;
	m_boolScaleAni		= 0;
	m_boolScalePlus		= 0;
	m_boolColorAni		= 0;

	m_R					= 0;
	m_G					= 0;
	m_B					= 0;
	m_A					= 1;
}

void Object::init(GLdouble x, GLdouble y, GLdouble size)
{
	m_width = size;
	m_height = size;

	m_x = x;
	m_y = y;

	m_left = m_x - (m_width / 2);
	m_right = m_left + m_width;
	m_bottom = m_y - (m_height / 2);
	m_top = m_bottom + m_height;
}

void Object::init(GLdouble x, GLdouble y, GLdouble width, GLdouble height)
{
	m_width = width;
	m_height = height;

	m_x = x;
	m_y = y;

	m_left = m_x - (m_width / 2);
	m_right = m_left + m_width;
	m_bottom = m_y - (m_height / 2);
	m_top = m_bottom + m_height;
}

void Object::setColor(GLfloat R, GLfloat G, GLfloat B, GLfloat A) { m_R = R; m_G = G; m_B = B; m_A = A; m_set_Color = true;};

void Object::setPosition(GLdouble x, GLdouble y) { 

	if(m_boolMoveToPoint) {
		if((m_x >= m_obj_x - 2) && (m_x <= m_obj_x + 2) &&
			(m_y >= m_obj_y - 2) && (m_y <= m_obj_y + 2)) {
			m_boolMoveToPoint = false;
			m_boolMove = true;
		}
	}

	m_x = x;
	m_y = y;

	m_left = m_x - (m_width / 2);
	m_right = m_left + m_width;
	m_bottom = m_y - (m_height / 2);
	m_top = m_bottom + m_height; 
}

void Object::setScale(GLboolean b, GLdouble Scale)
{
	m_boolRescale = b;
	m_rescale = Scale;
}	

void Object::setRescaleAnimation(GLboolean b, GLdouble Max_Scale, GLdouble Min_Scale)
{
	m_boolAnimation = b;
	m_rescale = true;
	m_boolScaleAni = true;
	m_boolScalePlus = true;
	m_boolRescale = true;
	m_max_Scale = Max_Scale;
	m_min_Scale = Min_Scale;
}

void Object::setVelocity(GLboolean run, GLdouble vel_x, GLdouble vel_y)
{
	m_vel_x = vel_x;
	m_vel_y = vel_y;
	m_boolMove = run;

	if(m_boolMove == false) {
		m_vel_x = 0;
		m_vel_y = 0;
	}
}

void Object::setVelocity(GLboolean run)
{
	m_boolMove = run;
}

void Object::runVelocity()
{
	m_x += m_vel_x;
	m_y += m_vel_y;

	if((reScale_left <= 0) && (m_vel_x < 0))
		m_vel_x = -(m_vel_x);
	else if((reScale_right >= 800) && (m_vel_x > 0))
		m_vel_x = -(m_vel_x);

	if((reScale_top >= 600) && (m_vel_y > 0))
		m_vel_y = -(m_vel_y);
	else if((reScale_bottom <= 0) && (m_vel_y < 0))
		m_vel_y = -(m_vel_y);

	setPosition(m_x, m_y);
}

void Object::draw() {
	glColor4f(m_R, m_G, m_B, m_A);

	if(!m_boolRescale)
		m_rescale = 1;

	if(m_boolAnimation)
		runAnimation();	

	if(m_boolMove)
		runVelocity();

	if(m_boolMoveToPoint)
		setPosition((m_x + m_increase_x), (m_y + m_increase_y));
	

	reScale_left = m_x - ((m_width * m_rescale) / 2);
	reScale_right = m_x + ((m_width * m_rescale) / 2);
	reScale_bottom = m_y - ((m_height * m_rescale) / 2);
	reScale_top = m_y + ((m_height * m_rescale) / 2);
}

void Object::addImpulse(GLdouble p_x, GLdouble p_y)
{
	
	m_vel_x += p_x;
	m_vel_y += p_y;
}

void Object::plusVelocity()
{
	if(m_vel_x == 0 || m_vel_y == 0)
	{
		m_vel_x = 1 + rand() % 2;

		if(rand() % 2)
			m_vel_x = -m_vel_x;

		m_vel_y = 1 + rand() % 2;

		if(rand() % 2)
			m_vel_y = -m_vel_y;
	}
	distCal(m_x + m_vel_x, m_y + m_vel_y);
	m_vel_x += m_increase_x;
	m_vel_y += m_increase_y;
}
void Object::MinorVelocity()
{
	if(m_vel_x == 0 || m_vel_y == 0)
		return;
	distCal(m_x + m_vel_x, m_y + m_vel_y);
	m_vel_x -= m_increase_x;
	m_vel_y -= m_increase_y;
}

void Object::distCal(GLdouble x, GLdouble y)
{
	m_obj_x = x;
	m_obj_y = y;

	GLdouble dist_x = (m_obj_x > m_x ? (m_obj_x - m_x) : (m_x - m_obj_x) );
	GLdouble dist_y = (m_obj_y > m_y ? (m_obj_y - m_y) : (m_y - m_obj_y) );

	m_increase_x = (dist_x > dist_y ? 1 : dist_x / dist_y);
	m_increase_y = (dist_x > dist_y ? dist_y / dist_x  : 1);

	if(m_obj_x < m_x)
		m_increase_x = -m_increase_x;

	if(m_obj_y < m_y)
		m_increase_y = -m_increase_y;

	//setPosition((m_x + m_increase_x), (m_y + m_increase_y));
}

void Object::moveToPoint(GLdouble x, GLdouble y)
{
	distCal(x, y);

	m_boolMoveToPoint = true;
	m_boolMove = false;

	if((m_x == m_obj_x) && (m_y == m_obj_y))
		m_boolMoveToPoint = false;

	printf("m_x::%f m_y::%f // m_increase_x::%f m_increase_y::%f\n", m_x, m_y, m_increase_x, m_increase_y);
}

void Object::runAnimation()
{
	if(m_boolScaleAni)
	{
		if(m_boolScalePlus) {
			m_rescale += 0.1f;
		}
		else {
			m_rescale -= 0.1f;
		}

		if(m_rescale >= m_max_Scale) {
			m_boolScalePlus = false;
		}
		else if(m_rescale <= m_min_Scale) {
			m_boolScalePlus = true;
		}
	}	
}

//---------------------- RectObject -----------------------------------

RectObject::RectObject() {
	Object::Object();
}

RectObject::RectObject(GLdouble x, GLdouble y, GLdouble size)
{
	init(x, y, size);
}

RectObject::RectObject(GLdouble x, GLdouble y, GLdouble width, GLdouble height)
{
	init(x, y, width, height);
}

void RectObject::draw(){

	Object::draw();

	glBegin( GL_POLYGON );

	glVertex2d( reScale_left , reScale_bottom );
	glVertex2d( reScale_right, reScale_bottom );
	glVertex2d( reScale_right, reScale_top );
	glVertex2d( reScale_left, reScale_top );
	glEnd();

	glLineWidth(2.0);
	glColor4d( 1.0f - m_R, 1.0f - m_G, 1.0f - m_B, 1.0f );

	glBegin( GL_LINES );
	glVertex2d( reScale_left, reScale_bottom);
	glVertex2d( reScale_right, reScale_bottom );

	glVertex2d( reScale_right, reScale_bottom );
	glVertex2d( reScale_right, reScale_top );

	glVertex2d( reScale_right, reScale_top );
	glVertex2d( reScale_left, reScale_top );

	glVertex2d( reScale_left, reScale_top );
	glVertex2d( reScale_left, reScale_bottom);
	glEnd();
}

