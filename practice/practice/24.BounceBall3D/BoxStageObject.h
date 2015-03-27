#ifndef BOXSTAGE_OBJECT_H
#define BOXSTAGE_OBJECT_H

#include "Object3D.h"
#include "Util.h"

class Ball : public Object3D {
private:
	_point m_velocity;
	float r, g, b;
	bool m_debug;
	
public:
	Ball() { type = objectTypeID::BALL; }
	Ball(float _x, float _y, float _z)
		: Object3D(_x, _y, _z){
			type = objectTypeID::BALL;
			m_velocity.x = 2;
			m_velocity.y = 2;
			m_velocity.z = -2;

			r = 0.5;
			g = 0.5;
			b = 1;
			m_debug = false;
	}
	Ball(float _x, float _y, float _z, float _scale)
		: Object3D(_x, _y, _z, _scale){
			type = objectTypeID::BALL;
			m_velocity.x = 2;
			m_velocity.y = 0;
			m_velocity.z = 0;
			m_debug = false;
	}

	Ball(float _x, float _y, float _z,
		float vel_x, float vel_y, float vel_z)
		: Object3D(_x, _y, _z){
			type = objectTypeID::BALL;
			m_velocity.x = vel_x;
			m_velocity.y = vel_y;
			m_velocity.z = vel_z;
			r = 1;
			g = 1;
			b = 1;
			m_debug = false;
	}

	~Ball() {}

	bool Bound(CollisionBox Box);

	void Draw();
	void Update();
	void AddFuntion() {
		if(m_debug)
			m_debug = false;
		else
			m_debug = true;
	}
};

class Wall : public Object3D{
private:
	int m_mode;
	float r, g, b;

public:
	Wall() { type = objectTypeID::WALL; }

	Wall(CollisionBox Box){
		m_CollisionBox = Box;
		type = objectTypeID::WALL;
		m_mode = GL_POLYGON;
		r = 0.5;
		g = 0.5;
		b = 0.5;
	}

	~Wall() {}

	void Draw();
	void Update();
	void SetMode(int mode) { m_mode = mode; }
	void SetRGB(float _r, float _g, float _b) { 
		r = _r; 
		g = _g;
		b = _b;
	}
};

#endif // BOXSTAGE_OBJECT_H