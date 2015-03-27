#include "BoxStage.h"

#define BOXSIZE 300

void BoxStage::Draw()
{
	World3D::Draw();

	for( std::vector<Ball*>::iterator it = m_ball.begin(); it != m_ball.end(); it++) {
		glPushMatrix();
		(*it)->Draw();
		glPopMatrix();
	}

	for( std::vector<Wall*>::iterator it = m_wall.begin(); it != m_wall.end(); it++) {
		glPushMatrix();
		(*it)->Draw();
		glPopMatrix();
	}

	for(std::vector<GroundSnow>::iterator it = m_groundsnow.begin(); it != m_groundsnow.end(); it++ )
	{
		glPushMatrix();
		it->Draw();
		glPopMatrix();
	}
}

void BoxStage::Update()
{
	World3D::Update();

	for( std::vector<Ball*>::iterator it = m_ball.begin(); it != m_ball.end(); it++) {
		(*it)->AddVelocity(0, -0.1, 0);
	}

	for( std::vector<Wall*>::iterator it = m_wall.begin(); it != m_wall.end(); it++) {
		(*it)->Update();
		for( std::vector<Ball*>::iterator b_it = m_ball.begin(); b_it != m_ball.end(); b_it++) {
			switch((*it)->GetType()){
			case objectTypeID::WALL:
				if((*b_it)->Bound((*it)->GetCollisionBox())) {
					(*it)->SetRGB((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
				}
				break;
			case objectTypeID::COLORWALL:
				if(CollisionCheck((*b_it)->GetCollisionBox(), (*it)->GetCollisionBox())) {
					(*b_it)->ColorChange((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
					(*it)->SetRGB((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
				}
				break;
			default:
				break;
			}
		}
	}

	for( std::vector<Ball*>::iterator it = m_ball.begin(); it != m_ball.end(); it++) {
		(*it)->Update();
	}

	bool remove = false;
	bool create = true;
	float _x, _z;

	for(std::vector<Object3D*>::iterator it = m_obj.begin(); it != m_obj.end(); )
	{

		if((*it)->GetPoint().y <= 10){
			switch((*it)->GetType())
			{
			case SNOW:
				_x = (*it)->GetPoint().x;
				_z = (*it)->GetPoint().z;
				it = m_obj.erase(it);
				remove = true;
				break;
			case RAIN:
				_x = (*it)->GetPoint().x;
				_z = (*it)->GetPoint().z;
				it = m_obj.erase(it);
				break;
			default:
				it++;
				break;
			}
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
			m_groundsnow.push_back(GroundSnow(_x, 11, _z));
	}
}

void BoxStage::AddFunction()
{
	World3D::AddFunction();

	for( std::vector<Ball*>::iterator it = m_ball.begin(); it != m_ball.end(); it++) {
		(*it)->AddFuntion();
	}

	for( std::vector<Wall*>::iterator it = m_wall.begin(); it != m_wall.end(); it++) {
		(*it)->AddFuntion();
	}

}

Ball* BoxStage::AddBall(Ball* obj)
{
	m_ball.push_back(obj);
	return obj;
}

Wall* BoxStage::AddWall(Wall* obj)
{
	m_wall.push_back(obj);
	return obj;
}