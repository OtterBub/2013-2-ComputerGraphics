#ifndef __OBJECT3D_H__
#define __OBJECT3D_H__

#include <iostream>
#include <vector>

#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <cstdlib>
#include <ctime>

#define SNOW		2000
#define GROUNDSNOW	2001

class Object3D{
protected:
	struct _point {
		float x, y, z;
	} point;

	float angle;
	float scale;
	int type;	

public:
	Object3D(){point.x = 0; point.y = 0; point.z = 0; angle = 0; type = 0; scale = 1;}
	Object3D(float _x, float _y, float _z) {
		point.x = _x;
		point.y = _y;
		point.z = _z;
		angle = 0.0;
		type = 0;
		scale = 1;
	}

	Object3D(float _x, float _y, float _z, float _scale) {
		point.x = _x;
		point.y = _y;
		point.z = _z;
		angle = 0.0;
		type = 0;
		scale = _scale;
	}

	virtual ~Object3D() {};
	
	virtual void Draw();
	virtual void Update() = 0;
	virtual void AddFuntion() {}

	void ObjectControlPosition(float add_x, float add_y, float add_z);

	void ObjectControlAngle(float add_angle);

	void SetObjectPosition(float add_x, float add_y, float add_z);

	_point GetPoint() {return point;}
	int GetType() {return type;}
};


#endif //__OBJECT3D_H__