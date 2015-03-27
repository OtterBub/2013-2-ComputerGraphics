#include "World.h"
#include "Rectangle.h"

World* World::GetInstance()
{
	static World* instance = new World();
	return instance;
}

World::World()
{
}

World::~World()
{
}

void World::Init()
{
	std::shared_ptr< Rectangle > temp = std::shared_ptr< Rectangle >( new Rectangle() );
	temp->SetPosition( 0, 0 );
	temp->SetSize( 1 );
	temp->SetColor( 0.5, 0.5, 0.5 );
	AddObject( temp );

}

void World::Draw()
{
	for( std::shared_ptr<Object> it : mObjectVec )
	{
		it->Draw();
	}
}

void World::Update()
{
	for( std::shared_ptr<Object> it : mObjectVec )
	{
		it->Update();
	}
}

void World::AddObject( std::shared_ptr<Object> obj )
{
	mObjectVec.push_back( obj );
}