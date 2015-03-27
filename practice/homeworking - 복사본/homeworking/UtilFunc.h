#ifndef __UTILFUNC_H__
#define __UTILFUNC_H__

#include "Object.h"

bool LineLineCollision(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
bool LineLineCollision(POINT point1, POINT point2, POINT point3, POINT point4);

POINT SRTconvertToPoint(POINT point, float scaleX, float scaleY, float angle, float trans_x, float trans_y);

POINT LineCrossPoint(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
POINT LineCrossPoint(POINT point1, POINT point2, POINT point3, POINT point4);
void PointSorting(POINT* arr, int num);

bool ObjectLineCollision(Object obj1, Object obj2);

#endif //__UTILFUNC_H__