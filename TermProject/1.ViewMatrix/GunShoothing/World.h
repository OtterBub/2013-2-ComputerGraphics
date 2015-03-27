#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <vector>

#include "Object.h"

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

	virtual void draw();
	virtual void update();
};

#endif // WORLD_H