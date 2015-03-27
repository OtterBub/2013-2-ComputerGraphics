#include "Stage.h"

#define MAIN_COLLISION_RECT 15

bool RectCollision(Mainchar* main, Ground* ground){
	if(main->GetPoint().x - MAIN_COLLISION_RECT < ground->GetPoint().x + 50 &&
		main->GetPoint().x + MAIN_COLLISION_RECT > ground->GetPoint().x - 50 &&
		main->GetPoint().z - MAIN_COLLISION_RECT < ground->GetPoint().z + 400 &&
		main->GetPoint().z + MAIN_COLLISION_RECT > ground->GetPoint().z - 400){
			return true;
	}
	return false;
}

void Ground::Draw(){

	Object3D::Draw();
	glColor3f(1.0, 1.0, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(-50, 0.0, 400);
	glVertex3f(+50, 0.0, 400);
	glVertex3f(+50, 0.0, -400);
	glVertex3f(-50, 0.0, -400);
	glEnd();

	glColor3f(1.0, 0.5, 0.5);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-50, 0.0, 400);
	glVertex3f(+50, 0.0, 400);
	glVertex3f(+50, 0.0, -400);
	glVertex3f(-50, 0.0, -400);
	glEnd();
}

void Ground::Update(){
	this->ObjectControlPosition(0.0, 0.0, 5.0);
}

void Stage::Draw(){

	glColor3f(0.5, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-GROUND_SIZE, 0.0, -GROUND_SIZE);
	glVertex3f(GROUND_SIZE, 0.0, -GROUND_SIZE);
	glVertex3f(GROUND_SIZE, 0.0, GROUND_SIZE);
	glVertex3f(-GROUND_SIZE, 0.0, GROUND_SIZE);
	glEnd();
	for(std::vector<Ground*>::iterator it = m_ground.begin(); it != m_ground.end(); it++){
		glPushMatrix();
		(*it)->Draw();
		glPopMatrix();
	}
	World3D::Draw();
	glPushMatrix();
	m_Main->Draw();
	glPopMatrix();
	
	glBegin(GL_LINE_LOOP);
	glVertex3f(m_Main->GetPoint().x - MAIN_COLLISION_RECT, m_Main->GetPoint().y, m_Main->GetPoint().z + MAIN_COLLISION_RECT);
	glVertex3f(m_Main->GetPoint().x + MAIN_COLLISION_RECT, m_Main->GetPoint().y, m_Main->GetPoint().z + MAIN_COLLISION_RECT);
	glVertex3f(m_Main->GetPoint().x + MAIN_COLLISION_RECT, m_Main->GetPoint().y, m_Main->GetPoint().z - MAIN_COLLISION_RECT);
	glVertex3f(m_Main->GetPoint().x - MAIN_COLLISION_RECT, m_Main->GetPoint().y, m_Main->GetPoint().z - MAIN_COLLISION_RECT);
	glEnd();
}

void Stage::Update(){

	static bool timerInit = true;
	if(!(m_Main->GetDead())){
		timerInit = true;
		static int CreateTimer = 2000;
		static int CurrentTimer = clock();
		static int ran = 0;
		if(init){
			init = false;
			ran = 0;
			m_ground.push_back(new Ground(0, 0, -400));
			m_ground.push_back(new Ground(0, 0, -1000));
		}
		if(CreateTimer < (clock() - CurrentTimer)){
			CurrentTimer = clock();
			
			if(rand() % 2)
				ran --;
			else if(rand() % 2)
				ran ++;
		
			m_ground.push_back(new Ground(100 * ran, 0, -1000));
		}
		for(std::vector<Ground*>::iterator it = m_ground.begin(); it != m_ground.end(); it++){
			(*it)->Update();
		}

		static bool Collision = false;
		Collision = false;
		for(std::vector<Ground*>::iterator it = m_ground.begin(); it != m_ground.end(); it++){
		
			if(RectCollision(m_Main, *it)){
				Collision = true;
				break;
			}
		}
		
		for(std::vector<Ground*>::iterator it = m_ground.begin(); it != m_ground.end();){
			if ((*it)->GetPoint().z > 700){
				it = m_ground.erase(it);
			} else {
				it++;
			}
		}
		World3D::Update();
		m_Main->Update();
		if(!Collision && !(m_Main->GetJump()))
			m_Main->SetDead(true);

	} else {

		m_ground.clear();

		static int InitTimer = 3500;
		static int CurrentTimer = clock();
		if(timerInit){
			CurrentTimer = clock();
			timerInit = false;
		}
		if(InitTimer < (clock() - CurrentTimer)){
			CurrentTimer = clock();
			*m_Main = Mainchar::Mainchar();
			init = true;
		}
	}

	

	
}