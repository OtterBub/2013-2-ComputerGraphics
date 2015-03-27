#include "World.h"

void World::draw()
{
	for(auto it = obj.begin(); it != obj.end(); it++) {	
		(*it)->draw();		
	}
}

void World::addObject(Object* object)
{
	obj.push_back(object);
}

void World::allMoveToPoint(GLfloat x, GLfloat y)
{
	for(auto it = obj.begin(); it != obj.end(); it++) {
		(*it)->moveToPoint(x, y);
	}
}

void World::allClear()
{
	obj.clear();
}

void World::allPlusVelocity()
{
	for( auto it = obj.begin(); it != obj.end(); it++) {
		(*it)->plusVelocity();
	}
}

void World::allMinorVelocity()
{
	for( auto it = obj.begin(); it != obj.end(); it++) {
		(*it)->MinorVelocity();
	}
}