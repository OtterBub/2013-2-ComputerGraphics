#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <iostream>
#include <vector>

#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <cstdlib>
#include <ctime>

typedef struct _POINT{
	GLfloat x;
	GLfloat y;
}POINT;

class Object{
public:

	Object();

	void init(GLfloat x, GLfloat y, GLfloat size);
	void init(GLfloat x, GLfloat y, GLfloat width, GLfloat height);

	void setColor(GLfloat R, GLfloat G, GLfloat B, GLfloat A) ;	
	void setPosition(GLfloat x, GLfloat y);
	void setScale(GLboolean b, GLfloat Scale);
	void setRescaleAnimation(GLboolean b, GLfloat Max_Scale, GLfloat Min_Scale);
	void setVelocity(GLboolean run, GLfloat vel_x, GLfloat vel_y);
	void setVelocity(GLboolean run);
	void plusVelocity();
	void MinorVelocity();
	
	void addImpulse(GLfloat p_x, GLfloat p_y);
	void distCal(GLfloat x, GLfloat y);
	void moveToPoint(GLfloat x, GLfloat y);

	void runVelocity();
	virtual void draw();
	virtual void runAnimation();

	GLfloat getX() { return m_x; }
	GLfloat getY() { return m_y; }

protected:

	GLfloat m_rescale;
	GLfloat m_max_Scale;
	GLfloat m_min_Scale;

	GLboolean m_boolMove;
	GLboolean m_boolMoveToPoint;
	GLboolean m_boolRescale;

	GLboolean m_boolAnimation;
	GLboolean m_boolScaleAni;
	GLboolean m_boolScalePlus;

	GLboolean m_boolColorAni;

	GLfloat reScale_left;
	GLfloat reScale_right;
	GLfloat reScale_bottom;
	GLfloat reScale_top;

	GLfloat m_R;
	GLfloat m_G;
	GLfloat m_B;
	GLfloat m_A;
	
private:

	GLfloat m_width;
	GLfloat m_height;
	GLfloat m_left;
	GLfloat m_right;
	GLfloat m_bottom;
	GLfloat m_top;

	GLfloat m_x;
	GLfloat m_y;

	GLfloat m_vel_x;
	GLfloat m_vel_y;
	GLfloat m_obj_x;
	GLfloat m_obj_y;
	GLfloat m_increase_x;
	GLfloat m_increase_y;

	GLboolean m_set_Color;
};

class RectObject : public Object
{
public:
	RectObject();
	RectObject(GLfloat x, GLfloat y, GLfloat size);
	RectObject(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
	virtual void draw();
};

class CircleObject : public Object
{
public:
	CircleObject();
	CircleObject(GLfloat x, GLfloat y, GLfloat radius);
	CircleObject(GLfloat x, GLfloat y, GLfloat radius_x, GLfloat radius_y);
	virtual void draw();
private:
	int point_num;
	float inc;
};

class AnyObject : public Object
{
public:
	AnyObject();
	AnyObject(GLfloat* arr_float, int set_shape, int vertex_num);
	virtual void draw();

private:
	enum SHAPE{
		LINE = GL_LINE,
		STRIP = GL_LINE_STRIP 
	};
	unsigned int m_shape;
	std::vector<POINT> point;
};
#endif //__OBJECT_H__