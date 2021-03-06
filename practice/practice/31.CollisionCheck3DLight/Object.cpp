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

	m_scaleSpeed		= 0.1;
}

void Object::init(GLfloat x, GLfloat y, GLfloat size)
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

void Object::init(GLfloat x, GLfloat y, GLfloat width, GLfloat height)
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

void Object::setPosition(GLfloat x, GLfloat y) { 

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

void Object::setScale(GLboolean b, GLfloat Scale)
{
	m_boolRescale = b;
	m_rescale = Scale;
}	

void Object::setRescaleAnimation(GLboolean b, GLfloat Max_Scale, GLfloat Min_Scale, GLfloat Set_ScaleSpeed)
{
	m_boolAnimation = b;
	m_rescale = true;
	m_boolScaleAni = true;
	m_boolScalePlus = true;
	m_boolRescale = true;
	m_max_Scale = Max_Scale;
	m_min_Scale = Min_Scale;
	m_scaleSpeed = Set_ScaleSpeed;

}

void Object::setVelocity(GLboolean run, GLfloat vel_x, GLfloat vel_y)
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

	glTranslatef(m_x, m_y, 0.0);
	glScalef(m_rescale, m_rescale, 0.0);
}

void Object::addImpulse(GLfloat p_x, GLfloat p_y)
{
	
	m_vel_x += p_x;
	m_vel_y += p_y;
}

void Object::plusVelocity()
{
	if(m_vel_x == 0 && m_vel_y == 0)
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
	if(m_vel_x == 0 || m_vel_y == 0){
		m_vel_x = 0;
		m_vel_y = 0;
		return;
	}
	distCal(m_x + m_vel_x, m_y + m_vel_y);
	m_vel_x -= m_increase_x;
	m_vel_y -= m_increase_y;
}

void Object::distCal(GLfloat x, GLfloat y)
{
	m_obj_x = x;
	m_obj_y = y;

	GLfloat dist_x = (m_obj_x > m_x ? (m_obj_x - m_x) : (m_x - m_obj_x) );
	GLfloat dist_y = (m_obj_y > m_y ? (m_obj_y - m_y) : (m_y - m_obj_y) );

	m_increase_x = (dist_x > dist_y ? 1 : dist_x / dist_y);
	m_increase_y = (dist_x > dist_y ? dist_y / dist_x  : 1);

	if(m_obj_x < m_x)
		m_increase_x = -m_increase_x;

	if(m_obj_y < m_y)
		m_increase_y = -m_increase_y;

	//setPosition((m_x + m_increase_x), (m_y + m_increase_y));
}

void Object::moveToPoint(GLfloat x, GLfloat y)
{
	distCal(x, y);

	m_boolMoveToPoint = true;
	m_boolMove = false;

	if((m_x == m_obj_x) && (m_y == m_obj_y))
		m_boolMoveToPoint = false;

	//printf("m_x::%f m_y::%f // m_increase_x::%f m_increase_y::%f\n", m_x, m_y, m_increase_x, m_increase_y);
}

void Object::runAnimation()
{
	if(m_boolScaleAni)
	{
		if(m_boolScalePlus) {
			m_rescale += m_scaleSpeed;
		}
		else {
			m_rescale -= m_scaleSpeed;
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

RectObject::RectObject(GLfloat x, GLfloat y, GLfloat size)
{
	init(x, y, size);
}

RectObject::RectObject(GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	init(x, y, width, height);
}

void RectObject::draw(){

	Object::draw();

	glBegin( GL_POLYGON );

	glVertex2d( -5 , -5 );
	glVertex2d( 5, -5 );
	glVertex2d( 5, 5 );
	glVertex2d( -5, 5 );
	glEnd();

	glLineWidth(2.0);
	glColor4d( 1.0f - m_R, 1.0f - m_G, 1.0f - m_B, 1.0f );

	glBegin( GL_LINE_STRIP );
	glVertex2d( -5 , -5 );
	glVertex2d( 5, -5 );
	glVertex2d( 5, 5 );
	glVertex2d( -5, 5 );
	glEnd();
}

//---------------------- CircleObject -----------------------------------

CircleObject::CircleObject(GLfloat x, GLfloat y, GLfloat radius)
{
	init(x, y, radius);
	point_num = 2 + rand() % 40;
	inc = 0;
}

CircleObject::CircleObject(GLfloat x, GLfloat y, GLfloat radius_x, GLfloat radius_y)
{
	init(x, y, radius_x, radius_y);
	point_num = 2 + rand() % 40;
	inc = 0;
}

void CircleObject::draw()
{
	Object::draw();
	float x, y;
	float degreeMul = 360 / ((float)point_num);
	inc += 0.8;
	//glBegin(GL_LINES);
	//setScale(true, 1);

	for(int i = 0; i <= point_num; i++){			
		x = cos(((i*degreeMul) + inc) * 3.14/180) * ( reScale_right - reScale_left );
		y = -sin(((i*degreeMul) + inc) * 3.14/180) * ( reScale_top - reScale_bottom );

		glBegin(GL_POLYGON);
		glVertex2f(x - 3, y - 3);
		glVertex2f(x + 3, y - 3);
		glVertex2f(x + 3, y + 3);
		glVertex2f(x - 3, y + 3);
		glEnd();


	}
}

//---------------------- MorpingObject -----------------------------------

MorpingObject::MorpingObject(GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	init(x, y, width, height);
	point_num = 48;
	morpingTime = 1000;
	currentTime = clock();
	point_move = rand() % 360;
	point_move_time = 0;

	position_x = new float[point_num];
	position_y = new float[point_num];

	/*for(int i = 0; i < point_num; i++){			
			position_x[i] = cos(((i*degreeMul) + point_move) * 3.14/180) * ( reScale_right - reScale_left );
			position_y[i] = -sin(((i*degreeMul) + point_move) * 3.14/180) * ( reScale_top - reScale_bottom );
	}*/

	morping_step = true;
}

MorpingObject::~MorpingObject(){
	
	
}

void MorpingObject::draw()
{
	Object::draw();
	
	degreeMul = 360 / ((float)point_num);
	
	
	point_move+= 0.5;

	if(morping_step){

		for(int i = 0; i < point_num; i++){			
			position_x[i] = cos(((i*degreeMul) + point_move) * 3.14/180) * ( reScale_right - reScale_left );
			position_y[i] = -sin(((i*degreeMul) + point_move) * 3.14/180) * ( reScale_top - reScale_bottom );
		}

		/*for(int i = 0; i <= point_num; i+=2){	
			if( i > point_num )
				i = point_num;
			position_x[i] = cos(((i*degreeMul) ) * 3.14/180) * ( reScale_right - reScale_left );
			position_y[i] = -sin(((i*degreeMul) ) * 3.14/180) * ( reScale_top - reScale_bottom );
		}*/
		morping_step = false;
	}


	if(point_num >= 4){
		for(int i = 0; i < point_num; i++){	
			if((i % 2) == 0){
				position_x[i] = cos(((i*degreeMul) + point_move) * 3.14/180) * ( reScale_right - reScale_left );
				position_y[i] = -sin(((i*degreeMul) + point_move) * 3.14/180) * ( reScale_top - reScale_bottom );
			} else {
				position_x[i] = cos(((i*degreeMul) + point_move_time) * 3.14/180) * ( reScale_right - reScale_left );
				position_y[i] = -sin(((i*degreeMul) + point_move_time) * 3.14/180) * ( reScale_top - reScale_bottom );
			}
		}
	} else if (point_num >= 4) {

		position_x[0] = cos(((0*degreeMul) + point_move) * 3.14/180) * ( reScale_right - reScale_left );
		position_y[0] = -sin(((0*degreeMul) + point_move) * 3.14/180) * ( reScale_top - reScale_bottom );		

	}
	/*position_x[0] = cos(((0*degreeMul) + point_move) * 3.14/180) * ( reScale_right - reScale_left );
	position_y[0] = -sin(((0*degreeMul) + point_move) * 3.14/180) * ( reScale_top - reScale_bottom );
			   
	position_x[2] = cos(((2*degreeMul) + point_move) * 3.14/180) * ( reScale_right - reScale_left );
	position_y[2] = -sin(((2*degreeMul) + point_move) * 3.14/180) * ( reScale_top - reScale_bottom );

	position_x[4] = cos(((4*degreeMul) + point_move) * 3.14/180) * ( reScale_right - reScale_left );
	position_y[4] = -sin(((4*degreeMul) + point_move) * 3.14/180) * ( reScale_top - reScale_bottom );*/

	glBegin(GL_POLYGON);
	for(int i = point_num - 1; i >= 0; i--){			
		glVertex2f(position_x[i], position_y[i]);
	}
	glEnd();

	glLineWidth(2.0);
	glColor4d( 1.0f - m_R, 1.0f - m_G, 1.0f - m_B, 1.0f );

	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < point_num; i++){			
		glVertex2f(position_x[i], position_y[i]);
	}
	glEnd();

	if((((1*degreeMul)) + point_move_time ) <= (((0*degreeMul) + point_move) ) && (point_num >= 4)){
		currentTime = clock();
		point_move_time = point_move;

		point_num /= 2;
		morping_step = true;
	} else if( point_num == 3 ) {
		
		if(morpingTime <=  clock() - currentTime){
			currentTime = clock();
			point_move_time = point_move;
			point_num = 48;
			morping_step = true;
		}
	}
}