#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <iostream>
#include <vector>

#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <cstdlib>
#include <ctime>

class Object{
public:

	Object()
	{
		m_width = 0;
		m_height = 0;

		m_x = 0;
		m_y = 0;

		m_left = 0;
		m_right = 0;
		m_bottom = 0;
		m_top = 0;

		m_rescale = 1.0f;
		m_boolRescale = false;
		m_boolAnimation = false;
	}

	void setColor(GLfloat R, GLfloat G, GLfloat B, GLfloat A) { m_R = R; m_G = G; m_B = B; m_A = A; m_set_Color = true;};
	
	void setPosition(GLdouble x, GLdouble y) { 
		m_x = x;
		m_y = y;

		m_left = m_x - (m_width / 2);
		m_right = m_left + m_width;
		m_bottom = m_y - (m_height / 2);
		m_top = m_bottom + m_height; 
	}

	void setScale(GLboolean b, GLdouble Scale)
	{
		m_boolRescale = b;
		m_rescale = Scale;
	}
	
	virtual void draw() {
		if(m_set_Color)
			glColor4f(m_R, m_G, m_B, m_A);
		if(!m_boolRescale)
			m_rescale = 1;
	}

	virtual void runAnimation()
	{
	}

	void setRescaleAnimation(GLboolean b, GLdouble Max_Scale, GLdouble Min_Scale)
	{
		m_boolAnimation = b;
		m_rescale = true;
		m_boolScalePlus = true;
		m_boolRescale = true;
		m_max_Scale = Max_Scale;
		m_min_Scale = Min_Scale;
	}

	GLdouble getX() { return m_x; }
	GLdouble getY() { return m_y; }

protected:
	GLdouble m_width;
	GLdouble m_height;
	GLdouble m_left;
	GLdouble m_right;
	GLdouble m_bottom;
	GLdouble m_top;

	GLdouble m_x;
	GLdouble m_y;

	GLdouble m_rescale;
	GLdouble m_max_Scale;
	GLdouble m_min_Scale;

	GLboolean m_boolRescale;
	GLboolean m_boolAnimation;
	GLboolean m_boolScaleAni;
	GLboolean m_boolScalePlus;
	GLboolean m_boolColorAni;

	GLfloat m_R;
	GLfloat m_G;
	GLfloat m_B;
	GLfloat m_A;
	
private:	

	GLboolean m_set_Color;
};

class RectObject : public Object
{
public:

	RectObject() {
		Object::Object();
	}

	RectObject(GLdouble x, GLdouble y, GLdouble size)
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

	RectObject(GLdouble x, GLdouble y, GLdouble width, GLdouble height)
	{
		m_width = width;
		m_height = height;

		m_x = x;
		m_y = y;

		m_left = m_x - (m_width / 2);
		m_right = m_left + m_width;
		m_bottom = m_y - (m_height / 2);
		m_top = m_bottom + m_height;

		setRescaleAnimation(true, 2.0f, 0.3f);
		m_boolAnimation  = true;
	}

	void draw(){
		
		Object::draw();

		if(m_boolAnimation)
			runAnimation();

		glBegin( GL_POLYGON );
		
		GLdouble reScale_left = m_x - ((m_width * m_rescale) / 2);
		GLdouble reScale_right = m_left + ((m_width * m_rescale) / 2);
		GLdouble reScale_bottom = m_y - ((m_height * m_rescale) / 2);
		GLdouble reScale_top = m_bottom + ((m_height * m_rescale) / 2);

		glVertex2d( reScale_left , reScale_bottom );
		glVertex2d( reScale_right, reScale_bottom );
		glVertex2d( reScale_right, reScale_top );
		glVertex2d( reScale_left, reScale_top );
		glEnd();

		glLineWidth(3.0);
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

	virtual void runAnimation()
	{

		if(m_boolScaleAni)
		{
			if(m_boolScalePlus){
				m_rescale += 0.1f;
			}
			else{
				m_rescale -= 0.1f;
			}
			if(m_rescale >= m_max_Scale)
			{
				m_boolScalePlus = false;
			}
			else if(m_rescale <= m_min_Scale){
				m_boolScalePlus = true;
			}
		}	
	}
};

#endif //__OBJECT_H__
