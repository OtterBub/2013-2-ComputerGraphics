#include "Rectangle.h"

Rectangle::Rectangle()
{
	mX = 0, mY = 0;
	mSize = 5;
	//memcpy_s( mColor, sizeof( GLfloat ) * 4, nullptr, sizeof( GLfloat ) * 4 );
}

Rectangle::~Rectangle()
{
}

void Rectangle::Draw()
{
	GLfloat lLeft, lRight, lTop, lBottom;
	lLeft = mX - ( mSize / 2.f );
	lRight = mX + ( mSize / 2.f );
	lTop = mY + ( mSize / 2.f );
	lBottom = mY - ( mSize / 2.f );

	glColor4fv( mColor );
	glBegin( GL_POLYGON );
	glVertex2f( lLeft, lTop );
	glVertex2f( lLeft, lBottom );
	glVertex2f( lRight, lBottom );
	glVertex2f( lRight, lTop );
	glEnd();
}

void Rectangle::Update()
{

}

void Rectangle::SetColor( GLfloat r, GLfloat g, GLfloat b, GLfloat a )
{
	mColor[0] = r;
	mColor[1] = g;
	mColor[2] = b;
	mColor[3] = a;
}

void Rectangle::SetColor( GLfloat* color )
{
	memcpy_s( mColor, sizeof( GLfloat ) * 4, color, sizeof( GLfloat ) * 4 );
}

void Rectangle::SetPosition( GLfloat x, GLfloat y )
{
	mX = x; mY = y;
}

void Rectangle::SetSize( GLfloat size )
{
	mSize = size;
}