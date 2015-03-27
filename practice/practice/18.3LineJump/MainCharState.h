#ifndef __MAINCHARSTATE_H__
#define __MAINCHARSTATE_H__

#include "State.h"

class Mainchar;

class JumpStop : public State<Mainchar>{
	JumpStop() {};
	JumpStop(const JumpStop&);
	JumpStop& operator=(const JumpStop&);
public:

	static JumpStop* Instance(){
		static JumpStop instance;
		return &instance;
	}

	void Enter(Mainchar* obj) ;
	void Execute(Mainchar* obj);
	void Exit(Mainchar* obj);
};

class JumpUp : public State<Mainchar>{
	JumpUp() {};
	JumpUp(const JumpUp&);
	JumpUp& operator=(const JumpUp&);
public:

	static JumpUp* Instance(){
		static JumpUp instance;
		return &instance;
	}

	void Enter(Mainchar* obj) ;
	void Execute(Mainchar* obj);
	void Exit(Mainchar* obj);
};

class JumpDown : public State<Mainchar>{
	JumpDown() {};
	JumpDown(const JumpDown&);
	JumpDown& operator=(const JumpDown&);
public:

	static JumpDown* Instance(){
		static JumpDown instance;
		return &instance;
	}

	void Enter(Mainchar* obj) ;
	void Execute(Mainchar* obj);
	void Exit(Mainchar* obj);
};

class JumpRight : public State<Mainchar>{
	float JumpPower;

	JumpRight() {};
	JumpRight(const JumpRight&);
	JumpRight& operator=(const JumpRight&);
public:

	static JumpRight* Instance(){
		static JumpRight instance;
		return &instance;
	}

	void Enter(Mainchar* obj) ;
	void Execute(Mainchar* obj);
	void Exit(Mainchar* obj);
};

class JumpLeft : public State<Mainchar>{
	float JumpPower;

	JumpLeft() {};
	JumpLeft(const JumpLeft&);
	JumpLeft& operator=(const JumpLeft&);
public:

	static JumpLeft* Instance(){
		static JumpLeft instance;
		return &instance;
	}

	void Enter(Mainchar* obj) ;
	void Execute(Mainchar* obj);
	void Exit(Mainchar* obj);
};



class MoveDown : public State<Mainchar>{
	MoveDown() {};
	MoveDown(const MoveDown&);
	MoveDown& operator=(const MoveDown&);
public:

	static MoveDown* Instance(){
		static MoveDown instance;
		return &instance;
	}

	void Enter(Mainchar* obj);
	void Execute(Mainchar* obj);
	void Exit(Mainchar* obj);
};

class MoveUp : public State<Mainchar>{
	MoveUp() {};
	MoveUp(const MoveUp&);
	MoveUp& operator=(const MoveUp&);
public:

	static MoveUp* Instance(){
		static MoveUp instance;
		return &instance;
	}

	void Enter(Mainchar* obj);
	void Execute(Mainchar* obj);
	void Exit(Mainchar* obj);
};

#endif //__MAINCHARSTATE_H__