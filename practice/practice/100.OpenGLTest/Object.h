#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <iostream>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>

class Object
{
public:
	Object();
	~Object();
	virtual void Draw() = 0;
	virtual void Update() = 0;

private:

};

#endif