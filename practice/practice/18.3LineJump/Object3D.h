#ifndef __OBJECT3D_H__
#define __OBJECT3D_H__

#include <iostream>
#include <vector>

#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <cstdlib>
#include <ctime>

class Object3D{
protected:
	struct _point {
		float x, y, z;
	} point;

	float angle;
	
public:
	Object3D(){point.x = 0; point.y = 0; point.z = 0; angle = 0;}
	
	virtual void Draw() = 0;
	virtual void Update() = 0;

	void ObjectControlPosition(float add_x, float add_y, float add_z);

	void ObjectControlAngle(float add_angle);

	_point GetPoint() {return point;}
};


#endif //__OBJECT3D_H__