#include "PoleTorus.h"

void Torus::Draw(){
	Object3D::Draw();
	glTranslatef(m_x, 0, 0);
	glScalef(m_scale_y, m_scale_x, m_scale_y);
	glRotatef(90, 1.0, 0, 0);
	glColor3f(0.0, 1.0, 0.5);
	glutSolidTorus(10, 50, 10, 10);
	glColor3f(1.0, 0.0, 0.5);
	glutWireTorus(10, 50, 10, 10);
}

void Torus::Update(){
	if(m_state != NULL)
		m_state->Execute(this);
}

void MoveDown::Enter(Torus* obj) {
	obj->Torus::Torus(obj->GetPoint().x, 300, obj->GetPoint().z);

}
void MoveDown::Execute(Torus* obj){
	obj->ObjectControlPosition(0, -1, 0);
	obj->ObjectControlAngle(5);
	if(obj->GetPoint().y <= 10)
		obj->ChangeState(DownEnd::Instance());
}
void MoveDown::Exit(Torus* obj) {
	obj->SetTimer(clock());
}

void DownEnd::Enter(Torus* obj) {
}
void DownEnd::Execute(Torus* obj){
	if(obj->GetTorusX() > 0)
		obj->ControlTorusX(-1);
	if(obj->GetTorusScale() > 0.1)
		obj->ControlTorusScale(-0.01);

	/*if(1000 < clock() - obj->GetTimer())
		obj->ChangeState(MoveDown::Instance());	*/
}

void DownEnd::Exit(Torus* obj) {
}



void Pole::Draw(){
	Object3D::Draw();
	
	glColor3f(0.5, 0.0, 0.5);
	glTranslatef(0, 150, 0);
	glScalef(1.0, 60, 1.0);
	glutWireCube(5);
	glPopMatrix();

	glPushMatrix();
	std::vector<Torus*>::iterator it;
	for( it = m_torus.begin(); it != m_torus.end(); it++){
		glPushMatrix();
		(*it)->Draw();
		glPopMatrix();
	}
}

void Pole::Update(){

	if(m_torus.size() >= 12)
		return;

	CurrentTorus->Update();
	if(CurrentTorus->GetPoint().y <= (21 * m_torus.size())){
		addTorus();
	}
}
