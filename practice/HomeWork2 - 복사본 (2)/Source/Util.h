#ifndef UTIL_H
#define UTIL_H

#include <gl\glut.h>

struct _point {
	float x, y, z;
};

struct CollisionBox {
	struct _point Min;
	struct _point Max;
};

bool CollisionCheck(CollisionBox A, CollisionBox B);
void drawStrokeText(char *string, float x, float y, float z, float scale);

#endif // UTIL_H