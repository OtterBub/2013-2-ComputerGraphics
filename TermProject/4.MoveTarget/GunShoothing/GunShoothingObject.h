#ifndef GUNSHOOTHINGOBJECT_H
#define GUNSHOOTHINGOBJECT_H

#include "Object.h"
#include "TextureManager.h"

class Target : public Object {
private:

	enum movingState{
		STOP,
		PLAY,
		REVERSE
	} ;

	TKpoint m_start_position;
	TKpoint m_end_position;
	float m_movingSpeed;
	int m_timer;

	bool m_autoReverse;
	bool m_shootable;
	int m_moveState;

public:
	Target(TKpoint setPosition);
	~Target();

	void set_end_position(TKpoint set_end);
	void set_end_position(TKpoint set_end, float speed);

	void moveReversing(bool _auto, int timer);
	void playMoving();
	void reverseMoving();

	void draw();
	void update();
	bool pickingCheck(TKpoint pick);
};

class Particle : public Object {
private:

public:
	Particle(TKpoint setPosition);
	~Particle();

	void draw();
	void update();
	bool pickingCheck(TKpoint pick);
};

class Pillar : public Object {
private:

public:
	Pillar(TKpoint setPosition);
	~Pillar();
	
	void draw();
	void update();
	bool pickingCheck(TKpoint pick);
};


#endif // GUNSHOOTHINGOBJECT_H