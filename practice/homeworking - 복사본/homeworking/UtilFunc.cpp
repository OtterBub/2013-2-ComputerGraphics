#include "UtilFunc.h"

bool LineLineCollision(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
	float den;
	float ua, ub;
	den = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);

	if(den){
		ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / den;
		ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / den;

		if(ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1){
			return true;
		} 
	} else {
		return false;
	}
	return false;
}

bool LineLineCollision(POINT point1, POINT point2, POINT point3, POINT point4){
	float den;
	float ua, ub;
	den = (point4.y - point3.y) * (point2.x - point1.x) - (point4.x - point3.x) * (point2.y - point1.y);

	if(den){
		ua = ((point4.x - point3.x) * (point1.y - point3.y) - (point4.y - point3.y) * (point1.x - point3.x)) / den;
		ub = ((point2.x - point1.x) * (point1.y - point3.y) - (point2.y - point1.y) * (point1.x - point3.x)) / den;

		if(ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1){
			return true;
		} 
	} else {
		return false;
	}
	return false;
}

POINT SRTconvertToPoint(POINT point, float scaleX, float scaleY, float angle, float trans_x, float trans_y){
	POINT result = point;

	result.x = result.x * scaleX;
	result.y = result.y * scaleY;

	float tempX = result.x;

	result.x = (cos(angle * (3.14/180)) * result.x) + (-sin(angle * (3.14/180)) * result.y) + trans_x;
	result.y = (sin(angle * (3.14/180)) * tempX) + (cos(angle * (3.14/180)) * result.y) + trans_y;

	return result;
}

POINT LineCrossPoint(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
	POINT result = {0, };
	
	float denominator = (y4 - y3)*(x2 - x1) - (x4 - x3) * (y2 - y1);
	
	float t = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
	float s = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);

	if(denominator == 0)
		return result;
	else {
		t = t / denominator;
		s = s / denominator;
	}

	if((t < 0 || t > 1) || ( s < 0 || t > 1 ))
		return result;
	else {
		result.x = x1 + t * (x2 - x1);
		result.y = y1 + t * (y2 - y1);
	}

	return result;
}

POINT LineCrossPoint(POINT point1, POINT point2, POINT point3, POINT point4){
	POINT result = {0, };
	
	float denominator = (point4.y - point3.y)*(point2.x - point1.x) - (point4.x - point3.x) * (point2.y - point1.y);
	
	float t = (point4.x - point3.x) * (point1.y - point3.y) - (point4.y - point3.y) * (point1.x - point3.x);
	float s = (point2.x - point1.x) * (point1.y - point3.y) - (point2.y - point1.y) * (point1.x - point3.x);

	if(denominator == 0)
		return result;
	else {
		t = t / denominator;
		s = s / denominator;
	}

	if( (t == 0) || (s ==0)){
		return result;
	}

	if((t < 0 || t > 1) || ( s < 0 || t > 1 ))
		return result;
	else {
		result.x = point1.x + t * (point2.x - point1.x);
		result.y = point1.y + t * (point2.y - point1.y);
	}

	return result;
}

void PointSorting(POINT* arr, int num)
{
	POINT* tmpArr = new POINT[num];
	float min_y = INT_MAX, max_y = -INT_MAX;
	float min_x = INT_MAX, max_x = -INT_MAX;
	bool ascend_x = false, ascend_y = false; 

	for(int i = 0; i < num; i++){
		if(arr[i].x > max_x)
			max_x = arr[i].x;
		if(arr[i].x < min_x)
			min_x = arr[i].x;

		if(arr[i].y > max_y)
			max_y = arr[i].y;
		if(arr[i].y < min_y)
			min_y = arr[i].y;
	}

	delete[] tmpArr;
}