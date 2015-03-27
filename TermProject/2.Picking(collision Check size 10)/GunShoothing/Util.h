#ifndef UTIL_H
#define UTIL_H

#include <Windows.h>
#include <gl\glut.h>
#include <iostream>
#include <cstdio>

typedef struct _TKpoint {
	float x, y, z;
} TKpoint;

struct CollisionBox {
	TKpoint Min;
	TKpoint Max;
};

bool CollisionCheck(CollisionBox A, CollisionBox B);
void drawStrokeText(char *string, float x, float y, float z, float scale);

void drawStrokeText(float x, float y, float z, float scale, char *fmt, ...);

void TKMultMatrix(float m1[][4], float m2[][4]);

GLubyte* LoadDIBitmap(const char *filename, BITMAPINFO **info);

POINT SRTconvertToPoint(POINT point, float scaleX, float scaleY, float angle, float trans_x, float trans_y);
TKpoint MatrixRealConvert(TKpoint point, float modelview[16]);

#endif // UTIL_H