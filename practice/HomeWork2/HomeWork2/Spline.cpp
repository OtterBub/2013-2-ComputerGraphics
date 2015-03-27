#include "Spline.h"

_point CubicBezierCurve(_point p[4], float t)
{
	_point b[4];
	_point result = {0,};
	b[0].x = pow((1 - t), 3) * p[0].x;
	b[0].y = pow((1 - t), 3) * p[0].y;
	b[0].z = pow((1 - t), 3) * p[0].z;

	b[1].x = 3 * (pow((1 - t), 2)) * t * p[1].x;
	b[1].y = 3 * (pow((1 - t), 2)) * t * p[1].y;
	b[1].z = 3 * (pow((1 - t), 2)) * t * p[1].z;

	b[2].x = 3 * (1 - t) * pow(t, 2) * p[2].x;
	b[2].y = 3 * (1 - t) * pow(t, 2) * p[2].y;
	b[2].z = 3 * (1 - t) * pow(t, 2) * p[2].z;
	
	b[3].x = pow(t, 3) * p[3].x;
	b[3].y = pow(t, 3) * p[3].y;
	b[3].z = pow(t, 3) * p[3].z;


	for(int i = 0; i < 4; i++) {
		result.x += b[i].x;
		result.y += b[i].y;
		result.z += b[i].z;
	}

	return result;
}