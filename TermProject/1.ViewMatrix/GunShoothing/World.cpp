#include "World.h"

World::World()
{

}

World::~World()
{

}

World& World::Instance()
{
	static World instance;
	return instance;
}

Object* World::addObejct(Object* obj)
{
	m_objVec.push_back(obj);

	return obj;
}

Object* World::addBlendObejct(Object* obj)
{
	m_BlendObjVec.push_back(obj);

	return obj;
}

void World::draw()
{
	std::vector<Object*>::iterator it = m_objVec.begin();

	for(it ; it != m_objVec.end(); it++) {
		glColor4f(1, 1, 1, 1);
		glPushMatrix();
		(*it)->draw();
		glPopMatrix();
	}

	it = m_BlendObjVec.begin();

	for(it ; it != m_BlendObjVec.end(); it++) {
		glColor4f(1, 1, 1, 1);
		glPushMatrix();
		(*it)->draw();
		glPopMatrix();
	}
}

void World::update()
{
	std::vector<Object*>::iterator it = m_objVec.begin();

	for(it ; it != m_objVec.end(); it++) {
		(*it)->update();
	}

	it = m_BlendObjVec.begin();

	for(it ; it != m_BlendObjVec.end(); it++) {
		(*it)->update();
	}
}