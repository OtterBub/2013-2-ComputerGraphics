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
	for(std::vector<GroundSnow>::iterator it = m_groundsnow.begin(); it != m_groundsnow.end(); it++)
	{
		glPushMatrix();
		it->Draw();
		glPopMatrix();
	}
}

void World3D::Update(){
	if(!m_update)
		return;

	bool remove = false;
	bool create = true;
	float _x, _z;

	for(std::vector<Object3D*>::iterator it = m_obj.begin(); it != m_obj.end(); )
	{
		(*it)->Update();
		if(((*it)->GetPoint().y <= 0) && ((*it)->GetType() == SNOW)){
			_x = (*it)->GetPoint().x;
			_z = (*it)->GetPoint().z;
			it = m_obj.erase(it);
			remove = true;
		}
		else it++;
	}

	if(remove){
		for(std::vector<GroundSnow>::iterator it = m_groundsnow.begin(); it != m_groundsnow.end(); it++ )
		{
			if((it->GetPoint().x - 10 < _x) && (it->GetPoint().x + 10 > _x) &&
				(it->GetPoint().z - 10 < _z) && (it->GetPoint().z + 10 > _z)){
				it->addColor();
				create = false;
			}
		}
		if(create)
			m_groundsnow.push_back(GroundSnow(_x, 1, _z));
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