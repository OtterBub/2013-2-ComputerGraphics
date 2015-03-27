#ifndef __DRAWSYSTEM_H__
#define __DRAWSYSTEM_H__

#include "World.h"
#define WORLD_INST World::GetInstance()

class DrawSystem
{
public:
	DrawSystem();
	~DrawSystem();
	bool Init();
	bool Run();

	static GLvoid DrawScene( GLvoid );
	static GLvoid Reshape( int w, int h );

private:

};

#endif