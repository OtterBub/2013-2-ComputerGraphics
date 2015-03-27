#ifndef ROLLERCOSTER_H
#define ROLLERCOSTER_H

#include "Object3D.h"
#include "Util.h"
#include "Spline.h"
#include <vector>
#include <math.h>
#include <algorithm>

class SplineCurve : public Object3D {
private:
	std::vector<_point> pointList;
	std::vector<_point> drawPoint;
	std::vector<_point> clickPoint;

	bool m_first;

public:
	SplineCurve() : Object3D() { m_first = true;}
	void AddPoint(float _x, float _y, float _z);
	void AddSplineCureve(_point p[4]);
	void Draw();
	void Update();

	void setFirst(bool _b) { m_first = _b; }
	std::vector<_point>& getAllVertex() { return pointList; };
};

class RollerCosater : public Object3D {
private:
	SplineCurve& Rail;
	std::vector<_point>& pointList;

	std::vector<_point>::iterator previousPoint;
	std::vector<_point>::iterator currentPoint;
	std::vector<_point>::iterator nextPoint;

	int currentTime;
	float currentSpeed;

	float sinValue;

	bool m_reverse;
	bool m_init;
	
	_point vector;

public:
	RollerCosater(SplineCurve& _Rail) :
		Rail(_Rail),
		pointList(Rail.getAllVertex())
	{
		previousPoint = currentPoint = pointList.begin();
		nextPoint = previousPoint + 1;

		point = *currentPoint;

		currentTime = clock();

		vector.x = 0;
		vector.y = 0;
		vector.z = 0;
		currentSpeed = 0;

		m_init = false;
		m_reverse = false;
		sinValue = 0;
	}
	void Draw();
	void Update();
};
#endif // ROLLERCOSTER_H