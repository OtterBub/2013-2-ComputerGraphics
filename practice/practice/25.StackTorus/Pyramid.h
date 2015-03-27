#ifndef __PYRAMID_H__
#define __PYRAMID_H__

#include "Object3D.h"

class Pyramid : public Object3D{
private:
	float rotate;

public:
	Pyramid() { 
		rotate = rand() % 360; 
	}
	Pyramid(float _x, float _y, float _z) 
		: Object3D(_x, _y, _z) {

	}

	void Draw();
	void Update();
};

#endif //__PYRAMID_H__