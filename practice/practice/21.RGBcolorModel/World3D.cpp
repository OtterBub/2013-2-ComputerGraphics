#include "World3D.h"

World3D* World3D::Instance(){
	static World3D instance;
	return &instance;
}

void World3D::Draw(){
	for(std::vector<Object3D*>::iterator it = m_obj.begin(); it != m_obj.end(); it++)
	{
		glPushMatrix();
		(*it)->Draw();
		glPopMatrix();
	}
}

void World3D::Update(){
	if(!m_update)
		return;
	for(std::vector<Object3D*>::iterator it = m_obj.begin(); it != m_obj.end(); it++)
	{
		(*it)->Update();
	}
}

void World3D::AddObject(Object3D* object){
	m_obj.push_back(object);
}

void World3D::AddFunction(){
	for(std::vector<Object3D*>::iterator it = m_obj.begin(); it != m_obj.end(); it++)
	{
		glPushMatrix();
		(*it)->AddFuntion();
		glPopMatrix();
	}
}