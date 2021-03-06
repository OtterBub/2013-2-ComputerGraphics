#ifndef __WORLD_H__
#define __WORLD_H__

#include "Object.h"

class World
{
public:
	void draw();
	void addObject(Object* object);
	void createObject();
	void allMoveToPoint(GLfloat x, GLfloat y);
	void allClear();
	void allPlusVelocity();
	void allMinorVelocity();
	
private :
	std::vector<Object*> obj;
};

#endif // __WORLD_H__