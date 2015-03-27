#ifndef __CHAR_H__
#define __CHAR_H__

#include "Object3D.h"
#include "MainCharState.h"

class Mainchar : public Object3D{
private:
	State<Mainchar>* m_pJumpState;
	State<Mainchar>* m_pMoveState;
	float width, height;
	float m_Scale;
	bool m_bJump;
	bool m_bDead;

public:
	Mainchar() { 
		m_pJumpState = JumpStop::Instance();
		m_pMoveState = MoveDown::Instance();
		m_bJump = false;
		m_bDead = false;
		m_Scale = 1.0f;
	}

	void ChargeJumpState(State<Mainchar>* state){
		m_pJumpState->Exit(this);
		m_pJumpState = state;
		m_pJumpState->Enter(this);
	}
	void ChargeMoveState(State<Mainchar>* state){
		m_pMoveState = state;
	}
	
	void SetJump(bool set) { m_bJump = set; }
	bool GetJump() { return m_bJump; }

	void SetDead(bool set) { m_bDead = set; }
	bool GetDead() { return m_bDead; }

	virtual void Draw();
	virtual void Update();	
};


#endif //__CHAR_H__