#ifndef __WORLD_H__
#define __WORLD_H__

#include "Object.h"
#include <vector>
#include <memory>

class World
{
public:
	~World();
	static World* GetInstance();

	void Init();
	void Draw();
	void Update();

	void AddObject( std::shared_ptr<Object> obj );

private:
	World();
	World( const World& other );

	std::vector < std::shared_ptr<Object> > mObjectVec;

};


#endif