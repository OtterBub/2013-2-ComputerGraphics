#include "Object3D.h"

void Object3D::Draw(){

	glTranslatef(point.x, point.y, point.z);
	glRotatef(angle, 0, 1, 0);
}

void Object3D::ObjectControlPosition(float add_x, float add_y, float add_z){
	point.x += add_x;
	point.y += add_y;
	point.z += add_z;
}

void Object3D::SetObjectPosition(float _x, float _y, float _z){
	point.x = _x;
	point.y = _y;
	point.z = _z;
}

void Object3D::ObjectControlAngle(float add_angle){
	angle += add_angle;
}