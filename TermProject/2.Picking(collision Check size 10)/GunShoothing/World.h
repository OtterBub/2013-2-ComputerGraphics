#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <vector>

#include "Object.h"

#define WORLD World::Instance()

class World{
private:
	std::vector<Object*> m_objVec;
	std::vector<Object*> m_BlendObjVec;
	
	World();
	World(const World&);
	const World operator=(const World&);

public:

	~World();

	static World& Instance();

	Object* addObejct(Object* obj);
	Object* addBlendObejct(Object* obj);

	void pickingCheck(float x, float y);

	virtual void draw();
	virtual void update();
	virtual void debugDraw();
};

#endif // WORLD_H