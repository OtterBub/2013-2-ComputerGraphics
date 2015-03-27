#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <vector>

#include <list>

#include "Object.h"

#define WORLD World::Instance()

class World{
protected:
	std::vector<Object*> m_objVec;
	std::vector<Object*> m_BlendObjVec;

	std::list<Object*> m_collisionObjList;
	
	World();
	World(const World&);
	const World operator=(const World&);

public:

	~World();

	static World& Instance();

	Object* addObejct(Object* obj);
	Object* addBlendObejct(Object* obj);
	void removeAllObject();

	void pickingCheck(TKpoint pick);

	virtual void draw();
	virtual void update();
	virtual void debugDraw();
};

#endif // WORLD_H