#ifndef FINALPRACTICEOBJ_H
#define FINALPRACTICEOBJ_H

#include "Object.h"
#include "TextureManager.h"

class MiracleCube : public Object
{
private:
	float m_angle;
public:
	MiracleCube(TKpoint setPosition);
	~MiracleCube();

	void draw();
	void update();
};

class Pond : public Object
{
private:
	float m_pondSize;
	float m_SurfaceHeight;
	bool m_bWave;
public:
	Pond(TKpoint setPosition);
	~Pond();

	void setPondSize(float setSize) { m_pondSize = setSize; }

	void draw();
	void update();
};

class Hammock : public Object
{
private:
	bool m_swingRight;
public:
	Hammock(TKpoint setPosition);
	~Hammock();

	void draw();
	void update();
};

class Kid : public Object
{
private:
	enum kidState {
		ORIGIN,
		RIGHT,
		LEFT,
		DOWN,
		UP
	};

	int m_state;
	bool m_jump;
	TKpoint m_velocity;

public:
	Kid(TKpoint setPosition);
	~Kid();

	void ChangeState();
	void Jump(int dir);

	void draw();
	void update();
};

class Ground : public Object 
{
private:
	float m_groundSize;
public:
	Ground(TKpoint setPosition);
	~Ground();

	void setGroundSize(float setSize) { m_groundSize = setSize; }

	void draw();
	void update();
};

class Wall : public Object 
{
private:
	float m_wallSize;
public:
	Wall(TKpoint setPosition);
	~Wall();

	void setWallSize(float setSize) { m_wallSize = setSize; }

	void draw();
	void update();
};

#endif