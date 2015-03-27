#include "MainCharState.h"
#include "Char.h"

void JumpStop::Enter(Mainchar* obj) {
	obj->SetJump(false);
}
void JumpStop::Execute(Mainchar* obj) {
	
}
void JumpStop::Exit(Mainchar* obj) {
	
}

void JumpUp::Enter(Mainchar* obj) {
	
}
void JumpUp::Execute(Mainchar* obj) {
	obj->ObjectControlPosition(0.0, 5.0, 0.0);
	if(obj->GetPoint().y > 100){
		obj->ChargeJumpState(JumpDown::Instance());
	}
}
void JumpUp::Exit(Mainchar* obj) {
	
}

void JumpDown::Enter(Mainchar* obj) {
	
}

void JumpDown::Execute(Mainchar* obj) {
	obj->ObjectControlPosition(0.0, -5.0, 0.0);
	if(obj->GetPoint().y <= 0) {
		obj->ChargeJumpState(JumpStop::Instance());
	}
}
void JumpDown::Exit(Mainchar* obj) {
	
}

void JumpRight::Enter(Mainchar* obj) {
	obj->SetJump(true);
	JumpPower = 10;
}
void JumpRight::Execute(Mainchar* obj) {
	JumpPower -= 0.5;
	obj->ObjectControlPosition(0.0, JumpPower, 0.0);
	obj->ObjectControlPosition(2.0, 0.0, 0.0);
	if(obj->GetPoint().y <= 0){
		obj->ChargeJumpState(JumpStop::Instance());
	}
}
void JumpRight::Exit(Mainchar* obj) {
}

void JumpLeft::Enter(Mainchar* obj) {
	obj->SetJump(true);
	JumpPower = 10;
}
void JumpLeft::Execute(Mainchar* obj) {
	JumpPower -= 0.5;
	obj->ObjectControlPosition(0.0, JumpPower, 0.0);
	obj->ObjectControlPosition(-2.0, 0.0, 0.0);
	if(obj->GetPoint().y <= 0){
		obj->ChargeJumpState(JumpStop::Instance());
	}
}
void JumpLeft::Exit(Mainchar* obj) {
}

void MoveDown::Enter(Mainchar* obj) {
	
}
void MoveDown::Execute(Mainchar* obj) {
	obj->ObjectControlPosition(0.0, 0.0, 5.0);	
	if(obj->GetPoint().z > 200){
		obj->ChargeMoveState(MoveUp::Instance());
	}
}
void MoveDown::Exit(Mainchar* obj) {
	
}

void MoveUp::Enter(Mainchar* obj){
}
void MoveUp::Execute(Mainchar* obj){
	obj->ObjectControlPosition(0.0, 0.0, -5.0);	
	if(obj->GetPoint().z < -200){
		obj->ChargeMoveState(MoveDown::Instance());
	}
}
void MoveUp::Exit(Mainchar* obj){
}