#ifndef UTIL_H
#define UTIL_H

#include <Windows.h>
#include <gl\glut.h>
#include <iostream>
#include <cstdio>

struct _point {
	float x, y, z;
};

struct CollisionBox {
	struct _point Min;
	struct _point Max;
};

bool CollisionCheck(CollisionBox A, CollisionBox B);
void drawStrokeText(char *string, float x, float y, float z, float scale);

GLubyte* LoadDIBitmap(const char *filename, BITMAPINFO **info);

#endif // UTIL_H