#ifndef FIREWORK_H
#define FIREWORK_H

#include "Object3D.h"
#include "BoxStage.h"

class Firework : public Object3D {
private:
	float size;
	_point startPoint, endPoint;
	int count;
	int startTime;
	bool explo;

	float r, g, b;
public:
	Firework(_point _startPoint, _point _endPoint) :
		Object3D()
	{
		startPoint = _startPoint;
		endPoint = _endPoint;
		
		point.z = -300;
		point.y = 0;
		point.x = 0;
		count = 0;
		startTime = clock();
		explo = false;
		size = 100;

		r = rand() / (float)RAND_MAX;
		g = rand() / (float)RAND_MAX;
		b = rand() / (float)RAND_MAX;
	}
	void Draw();
	void Update();

};

#endif // FIREWORK_H