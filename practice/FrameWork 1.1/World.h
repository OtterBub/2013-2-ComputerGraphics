#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <vector>

#include "Object.h"

class World{
private:
	std::vector<Object*> m_objVec;
	
	World();
	World(const World&);
	const World operator=(const World&);

public:

	~World();

	static World& Instance();

	virtual void draw();
	virtual void update();
};

#endif // WORLD_H