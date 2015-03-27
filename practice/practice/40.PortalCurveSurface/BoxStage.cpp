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

	for( std::vector<PortalWall*>::iterator portal_it = m_Wallportal.begin(); portal_it != m_Wallportal.end(); portal_it++) {
		(*portal_it)->Draw();
	}

	for( std::vector<PortalWall*>::iterator portal_it = m_portal.begin(); portal_it != m_portal.end(); portal_it++) {
		(*portal_it)->Draw();
	}
}

void BoxStage::Update()
{
	World3D::Update();

	for( std::vector<Wall*>::iterator it = m_wall.begin(); it != m_wall.end(); it++) {
		(*it)->Update();
	}

	for( std::vector<Ball*>::iterator it = m_ball.begin(); it != m_ball.end(); it++) {
		(*it)->AddVelocity(0, -0.1, 0);
	}

	for( std::vector<Ball*>::iterator ball_it = m_ball.begin(); ball_it != m_ball.end(); ball_it++) {
		for( std::vector<Wall*>::iterator wall_it = m_wall.begin(); wall_it != m_wall.end(); wall_it++ ){
			switch((*wall_it)->GetType()) {
			case objectTypeID::WALL :
				if((*ball_it)->Bound((*wall_it)->GetCollisionBox())) {
					(*wall_it)->SetRGB((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
				}
				break;
			case objectTypeID::COLORWALL:
				if(CollisionCheck((*ball_it)->GetCollisionBox(), (*wall_it)->GetCollisionBox())) {
					(*ball_it)->ColorChange((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
					(*wall_it)->SetRGB((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
				}
				break;
			default:
				break;
			}
		}

		for( std::vector<PortalWall*>::iterator portal_it = m_portal.begin(); portal_it != m_portal.end(); portal_it++) {
			_point objPos = (*ball_it)->GetPoint();
			CollisionBox temp;
			temp.Max = objPos;
			temp.Min = objPos;

			if((*ball_it)->getTeleportState() == false){
				if(CollisionCheck(temp, (*portal_it)->GetCollisionBox())) {
					int index = rand() % m_portal.size();
					while(m_portal[index] == (*portal_it)) { index = rand() % m_portal.size(); }
					_point randPortalPos = m_portal[index] -> GetPoint();

					(*ball_it)->SetObjectPosition(randPortalPos.x, randPortalPos.y, randPortalPos.z);
					(*ball_it)->SetTeleportState(true);
				}
			}
		}

		for( std::vector<PortalWall*>::iterator portal_it = m_Wallportal.begin(); portal_it != m_Wallportal.end(); portal_it++) {
			_point objPos = (*ball_it)->GetPoint();
			CollisionBox temp;
			temp.Max = objPos;
			temp.Min = objPos;

			if((*ball_it)->getTeleportState() == false){
				if(CollisionCheck(temp, (*portal_it)->GetCollisionBox())) {
					
					int index = rand() % m_Wallportal.size();

					while(m_Wallportal[index] == (*portal_it) || 
						m_Wallportal[index]->GetWallType() == PotalPosition::BOTTOM) 
					{ index = rand() % m_Wallportal.size(); }

					_point randPortalPos = m_Wallportal[index] -> GetPoint();

					(*ball_it)->SetObjectPosition(randPortalPos.x, randPortalPos.y, randPortalPos.z);
					(*ball_it)->SetTeleportState(true);

					_point tempVel = (*ball_it)->getVelocity();

					switch(m_Wallportal[index]->GetWallType()) 
					{
					case PotalPosition::TOP :
						(*ball_it)->SetVelocity(tempVel.x, 0, tempVel.z);
						printf("TOP\n");
						break;
					case PotalPosition::RIGHT :
						(*ball_it)->SetVelocity(-3, tempVel.y, tempVel.z / 2);
						printf("RIGHT\n");
						break;
					case PotalPosition::LEFT :
						(*ball_it)->SetVelocity(3, tempVel.y, tempVel.z / 2);
						printf("LEFT\n");
						break;
					case PotalPosition::FRONT :
						(*ball_it)->SetVelocity(tempVel.x / 2, tempVel.y, -3);
						printf("FRONT\n");
						break;
					case PotalPosition::BACK :
						(*ball_it)->SetVelocity(tempVel.x / 2, tempVel.y, +3);
						printf("RIGHT\n");
						break;
					}
				}
			}
		}
	}
	for( std::vector<PortalWall*>::iterator portal_it = m_Wallportal.begin(); portal_it != m_Wallportal.end(); portal_it++) {
		(*portal_it)->Update();
	}

	for( std::vector<PortalWall*>::iterator portal_it = m_portal.begin(); portal_it != m_portal.end(); portal_it++) {
		(*portal_it)->Update();
	}

	for( std::vector<Ball*>::iterator it = m_ball.begin(); it != m_ball.end(); it++) {
		(*it)->Update();
	}
}

void BoxStage::AddFunction()
{
	World3D::AddFunction();

	for( std::vector<Ball*>::iterator it = m_ball.begin(); it != m_ball.end(); it++) {
		(*it)->AddFuntion();
	}

}

void BoxStage::AddFunctionWall()
{

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

PortalWall* BoxStage::AddPortal(PortalWall* obj)
{
	m_portal.push_back(obj);
	return obj;
}

PortalWall* BoxStage::AddWallPortal(PortalWall* obj)
{
	m_Wallportal.push_back(obj);
	return obj;
}