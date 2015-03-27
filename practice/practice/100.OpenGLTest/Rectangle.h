#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "Object.h"

class Rectangle : public Object
{
public:
	Rectangle();
	~Rectangle();
	void Draw();
	void Update();

	void SetColor( GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f );
	void SetColor( GLfloat* color );
	void SetPosition( GLfloat x, GLfloat y );
	void SetSize( GLfloat size );

private:
	GLfloat mX, mY;
	GLfloat mSize;
	GLfloat mColor[4];
};

#endif