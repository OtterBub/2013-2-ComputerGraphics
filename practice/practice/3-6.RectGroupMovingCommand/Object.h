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

	Object();

	void init(GLdouble x, GLdouble y, GLdouble size);
	void init(GLdouble x, GLdouble y, GLdouble width, GLdouble height);

	void setColor(GLfloat R, GLfloat G, GLfloat B, GLfloat A) ;	
	void setPosition(GLdouble x, GLdouble y);
	void setScale(GLboolean b, GLdouble Scale);
	void setRescaleAnimation(GLboolean b, GLdouble Max_Scale, GLdouble Min_Scale);
	void setVelocity(GLboolean run, GLdouble vel_x, GLdouble vel_y);
	void setVelocity(GLboolean run);
	void plusVelocity();
	void MinorVelocity();
	
	void addImpulse(GLdouble p_x, GLdouble p_y);
	void distCal(GLdouble x, GLdouble y);
	void moveToPoint(GLdouble x, GLdouble y);

	void runVelocity();
	virtual void draw();
	virtual void runAnimation();

	GLdouble getX() { return m_x; }
	GLdouble getY() { return m_y; }

protected:

	GLdouble m_rescale;
	GLdouble m_max_Scale;
	GLdouble m_min_Scale;

	GLboolean m_boolMove;
	GLboolean m_boolMoveToPoint;
	GLboolean m_boolRescale;

	GLboolean m_boolAnimation;
	GLboolean m_boolScaleAni;
	GLboolean m_boolScalePlus;

	GLboolean m_boolColorAni;

	GLdouble reScale_left;
	GLdouble reScale_right;
	GLdouble reScale_bottom;
	GLdouble reScale_top;

	GLfloat m_R;
	GLfloat m_G;
	GLfloat m_B;
	GLfloat m_A;
	
private:

	GLdouble m_width;
	GLdouble m_height;
	GLdouble m_left;
	GLdouble m_right;
	GLdouble m_bottom;
	GLdouble m_top;

	GLdouble m_x;
	GLdouble m_y;

	GLdouble m_vel_x;
	GLdouble m_vel_y;
	GLdouble m_obj_x;
	GLdouble m_obj_y;
	GLdouble m_increase_x;
	GLdouble m_increase_y;

	GLboolean m_set_Color;
};

class RectObject : public Object
{
public:

	RectObject();
	RectObject(GLdouble x, GLdouble y, GLdouble size);
	RectObject(GLdouble x, GLdouble y, GLdouble width, GLdouble height);
	virtual void draw();
};

#endif //__OBJECT_H__