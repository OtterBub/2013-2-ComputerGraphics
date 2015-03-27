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

void World::removeAllObject() {
	m_objVec.clear();
	m_BlendObjVec.clear();
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

void World::debugDraw()
{
	std::vector<Object*>::iterator it = m_objVec.begin();

	for(it ; it != m_objVec.end(); it++) {
		glColor4f(1, 1, 1, 1);
		glPushMatrix();
		(*it)->debugDraw();
		glPopMatrix();
	}

	it = m_BlendObjVec.begin();

	for(it ; it != m_BlendObjVec.end(); it++) {
		glColor4f(1, 1, 1, 1);
		glPushMatrix();
		(*it)->debugDraw();
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

void World::pickingCheck(TKpoint pick) {
	std::vector<Object*>::iterator it = m_objVec.begin();
	for(it ; it != m_objVec.end(); it++) {
		if((*it)->pickingCheck(pick)) {
			m_collisionObjList.push_back(*it);
		}
	}

	it = m_BlendObjVec.begin();

	for(it ; it != m_BlendObjVec.end(); it++) {
		if((*it)->pickingCheck(pick)) {
			m_collisionObjList.push_back(*it);
		}
	}

	std::list<Object*>::iterator it_l = m_collisionObjList.begin();
	if(it_l != m_collisionObjList.end()) {
		Object* temp = NULL;
		float z_depth_min;
		temp = *it_l;
		temp->getViewPosition().z;
		
		z_depth_min = temp->getViewPosition().z;

		for(it_l; it_l != m_collisionObjList.end(); it_l++) {
			if(z_depth_min < (*it_l)->getViewPosition().z) {
				temp = *it_l;
			}
		}

		(temp)->setPicking(true);
	}

	m_collisionObjList.clear();
}