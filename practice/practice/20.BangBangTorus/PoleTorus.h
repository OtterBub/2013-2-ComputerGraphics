#include "Object3D.h"
#include "State.h"

class Torus;

// State of Torus

class MoveDown : public State<Torus>{
private:
	MoveDown() {};
	MoveDown(const MoveDown&);
	MoveDown operator=(const MoveDown&);
public:
	static MoveDown* Instance() {
		static MoveDown instance;
		return &instance;
	}

	virtual void Enter(Torus* obj);
	virtual void Execute(Torus* obj);
	virtual void Exit(Torus* obj);
};

class DownEnd : public State<Torus>{
private:
	DownEnd() {};
	DownEnd(const DownEnd&);
	DownEnd operator=(const DownEnd&);
public:
	static DownEnd* Instance() {
		static DownEnd instance;
		return &instance;
	}

	virtual void Enter(Torus* obj);
	virtual void Execute(Torus* obj);
	virtual void Exit(Torus* obj);
};

class StateEnd : public State<Torus>{
private:
	StateEnd() {};
	StateEnd(const StateEnd&);
	StateEnd operator=(const StateEnd&);
public:
	static StateEnd* Instance() {
		static StateEnd instance;
		return &instance;
	}

	virtual void Enter(Torus* obj);
	virtual void Execute(Torus* obj);
	virtual void Exit(Torus* obj);
};

// Torus

class Torus : public Object3D{
private:
	State<Torus>* m_state;
	float m_x;
	float m_scale_y;
	float m_scale_x;
	int m_Timer;
public:
	Torus() { m_state = MoveDown::Instance(); };
	Torus(float _x, float _y, float _z) 
		: Object3D(_x, _y, _z) { m_state = MoveDown::Instance(); m_x = 30; m_scale_x = 1.0; m_scale_y = 1.0; }

	virtual void Draw();
	virtual void Update();
	float GetTorusX() { return m_x; }
	void ControlTorusX(float add_x) { m_x += add_x; }

	float GetTorusScale() { return m_scale_x; }
	void ControlTorusScale(float add_scale) { m_scale_x += add_scale; m_scale_y -= add_scale; }

	void SetTimer(int _timer) { m_Timer = _timer; }
	int GetTimer() { return m_Timer; }

	void ChangeState(State<Torus>* _state) { 
		m_state->Exit(this);
		m_state = _state; 
		m_state->Enter(this);
	}
};

// Pole

class Pole : public Object3D{
public:
	Pole() {}
	Pole(float _x, float _y, float _z) : Object3D(_x, _y, _z) {}
	virtual void Draw();
	virtual void Update();
};