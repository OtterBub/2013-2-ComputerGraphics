#ifndef SNOW_H
#define SNOW_H

#include "Object3D.h"

class Snow : public Object3D {
private:
public:
	Snow() {}
	Snow(float _x, float _y, float _z) 
		: Object3D(_x, _y, _z)
	{
		type = SNOW;
	}

	~Snow() {}
	void Draw();
	void Update();
};

class GroundSnow : public Object3D {
private:
	float color;
public:
	GroundSnow() {}
	GroundSnow(float _x, float _y, float _z)
		: Object3D(_x, _y, _z)
	{
		color = 0;
		type = GROUNDSNOW;	
	}
	~GroundSnow() {}
	void Draw();
	void Update();
	void addColor() { 
		if(color < 1)
			color += 0.3; 
		else if(color > 1)
			color = 1;
	}
};

#endif // SNOW_H