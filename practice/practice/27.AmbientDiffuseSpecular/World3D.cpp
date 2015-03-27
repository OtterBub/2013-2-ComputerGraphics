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

void World3D::AddObject(Object3D* object) {
	m_obj.push_back(object);
}

void World3D::AddLight(int lightNum) {
	glEnable(GL_LIGHTING);
	m_lightOn[lightNum]=true;
	switch(lightNum){
	case 0:
		glEnable(GL_LIGHT0);
		break;
	case 1:
		glEnable(GL_LIGHT1);
		break;
	case 2:
		glEnable(GL_LIGHT2);
		break;
	case 3:
		glEnable(GL_LIGHT3);
		break;
	case 4:
		glEnable(GL_LIGHT4);
		break;
	case 5:
		glEnable(GL_LIGHT5);
		break;
	case 6:
		glEnable(GL_LIGHT6);
		break;
	case 7:
		glEnable(GL_LIGHT7);
		break;
	default:
		break;
	}
}

void World3D::RemoveLight(int lightNum) {
	glEnable(GL_LIGHTING);
	m_lightOn[lightNum] = false;
	switch(lightNum){
	case 0:
		glDisable(GL_LIGHT0);
		break;
	case 1:
		glDisable(GL_LIGHT1);
		break;
	case 2:
		glDisable(GL_LIGHT2);
		break;
	case 3:
		glDisable(GL_LIGHT3);
		break;
	case 4:
		glDisable(GL_LIGHT4);
		break;
	case 5:
		glDisable(GL_LIGHT5);
		break;
	case 6:
		glDisable(GL_LIGHT6);
		break;
	case 7:
		glDisable(GL_LIGHT7);
		break;
	default:
		break;
	}
}

void World3D::LightOnOff(int lightNum)
{
	if(m_lightOn[lightNum]){
		switch(lightNum){
		case 0:
			glDisable(GL_LIGHT0);
			break;
		case 1:
			glDisable(GL_LIGHT1);
			break;
		case 2:
			glDisable(GL_LIGHT2);
			break;
		case 3:
			glDisable(GL_LIGHT3);
			break;
		case 4:
			glDisable(GL_LIGHT4);
			break;
		case 5:
			glDisable(GL_LIGHT5);
			break;
		case 6:
			glDisable(GL_LIGHT6);
			break;
		case 7:
			glDisable(GL_LIGHT7);
			break;
		default:
			break;
		}
		m_lightOn[lightNum] = false;
	} else {
		switch(lightNum){
		case 0:
			glEnable(GL_LIGHT0);
			break;
		case 1:
			glEnable(GL_LIGHT1);
			break;
		case 2:
			glEnable(GL_LIGHT2);
			break;
		case 3:
			glEnable(GL_LIGHT3);
			break;
		case 4:
			glEnable(GL_LIGHT4);
			break;
		case 5:
			glEnable(GL_LIGHT5);
			break;
		case 6:
			glEnable(GL_LIGHT6);
			break;
		case 7:
			glEnable(GL_LIGHT7);
			break;
		default:
			break;
		}
		m_lightOn[lightNum] = true;
	}
}

void World3D::SetLightPos(int lightNum, float light_x, float light_y, float light_z, float light_infinit_local)
{
	GLfloat position[4];
	position[0] = light_x;
	position[1] = light_y;
	position[2] = light_z;
	position[3] = light_infinit_local;

	switch(lightNum){
	case 0:
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		break;
	case 1:
		glLightfv(GL_LIGHT1, GL_POSITION, position);
		break;
	case 2:
		glLightfv(GL_LIGHT2, GL_POSITION, position);
		break;
	case 3:
		glLightfv(GL_LIGHT3, GL_POSITION, position);
		break;
	case 4:
		glLightfv(GL_LIGHT4, GL_POSITION, position);
		break;
	case 5:
		glLightfv(GL_LIGHT5, GL_POSITION, position);
		break;
	case 6:
		glLightfv(GL_LIGHT6, GL_POSITION, position);
		break;
	case 7:
		glLightfv(GL_LIGHT7, GL_POSITION, position);
		break;
	default:
		break;
	}
}

void World3D::SetLightColor(int lightNum, GLenum pname , float light_R, float light_G, float light_B, float light_A)
{
	GLfloat color[4];
	color[0] = light_R;
	color[1] = light_G;
	color[2] = light_B;
	color[3] = light_A;

	switch(lightNum){
	case 0:
		glLightfv(GL_LIGHT0, pname, color);
		break;
	case 1:
		glLightfv(GL_LIGHT1, pname, color);
		break;
	case 2:
		glLightfv(GL_LIGHT2, pname, color);
		break;
	case 3:
		glLightfv(GL_LIGHT3, pname, color);
		break;
	case 4:
		glLightfv(GL_LIGHT4, pname, color);
		break;
	case 5:
		glLightfv(GL_LIGHT5, pname, color);
		break;
	case 6:
		glLightfv(GL_LIGHT6, pname, color);
		break;
	case 7:
		glLightfv(GL_LIGHT7, pname, color);
		break;
	default:
		break;
	}
}

void World3D::AddFunction(){
	for(std::vector<Object3D*>::iterator it = m_obj.begin(); it != m_obj.end(); it++)
	{
		glPushMatrix();
		(*it)->AddFuntion();
		glPopMatrix();
	}
}