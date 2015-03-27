#ifndef __PYRAMID_H__
#define __PYRAMID_H__

#include "Object3D.h"

class Pyramid : public Object3D{
private:
	float rotate;
	float scale;
	bool cover;
public:
	Pyramid() { 
		rotate = rand() % 360;
		scale = 1;
		cover = true;
	}
	Pyramid(float _x, float _y, float _z) 
		: Object3D(_x, _y, _z) {
			scale = 1;
			cover = true;
	}
	Pyramid(float _x, float _y, float _z, float _scale)
		: Object3D(_x, _y, _z) {
			scale = _scale;
			cover = true;
	}

	void Draw();
	void Update();
	void AddFuntion() {
		if(cover)
			cover = false;
		else
			cover = true;
	}
};

#endif //__PYRAMID_H__