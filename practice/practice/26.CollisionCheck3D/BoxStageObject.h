#ifndef BOXSTAGE_OBJECT_H
#define BOXSTAGE_OBJECT_H

#include "Object3D.h"
#include "Util.h"

class Ball : public Object3D {
private:
	_point m_velocity;
	float r, g, b;
	float m_MaxVelocity;
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
			m_CollisionBox.Max.x = point.x + 10;
			m_CollisionBox.Min.x = point.x - 10;

			m_CollisionBox.Max.y = point.y + 10;
			m_CollisionBox.Min.y = point.y - 10;

			m_CollisionBox.Max.z = point.z + 10;
			m_CollisionBox.Min.z = point.z - 10;
			m_MaxVelocity = 5;
	}
	Ball(float _x, float _y, float _z, float _scale)
		: Object3D(_x, _y, _z, _scale){
			type = objectTypeID::BALL;
			m_velocity.x = 2;
			m_velocity.y = 0;
			m_velocity.z = 0;
			r = g = b = 0;
			m_debug = false;
			m_CollisionBox.Max.x = point.x + 10;
			m_CollisionBox.Min.x = point.x - 10;

			m_CollisionBox.Max.y = point.y + 10;
			m_CollisionBox.Min.y = point.y - 10;

			m_CollisionBox.Max.z = point.z + 10;
			m_CollisionBox.Min.z = point.z - 10;
			m_MaxVelocity = 5;
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
			m_CollisionBox.Max.x = point.x + 10;
			m_CollisionBox.Min.x = point.x - 10;

			m_CollisionBox.Max.y = point.y + 10;
			m_CollisionBox.Min.y = point.y - 10;

			m_CollisionBox.Max.z = point.z + 10;
			m_CollisionBox.Min.z = point.z - 10;
			m_MaxVelocity = 5;
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
	void AddVelocity(float _x, float _y, float _z){
		if((m_velocity.x + _x <= m_MaxVelocity) && (m_velocity.x + _x >= -m_MaxVelocity)) {
			m_velocity.x += _x;
		} else if ( m_velocity.x < 0) {
			m_velocity.x = -m_MaxVelocity;
		} else if ( m_velocity.x > 0) {
			m_velocity.x = m_MaxVelocity;
		}

		if((m_velocity.y + _y <= m_MaxVelocity) && (m_velocity.y + _y >= -m_MaxVelocity)) {
			m_velocity.y += _y;
		} else if ( m_velocity.y < 0) {
			m_velocity.y = -m_MaxVelocity;
		} else if ( m_velocity.y > 0) {
			m_velocity.y = m_MaxVelocity;
		}

		if((m_velocity.z + _y <= m_MaxVelocity) && (m_velocity.z + _y >= -m_MaxVelocity)) {
			m_velocity.z += _z;
		} else if ( m_velocity.z < 0) {
			m_velocity.z = -m_MaxVelocity;
		} else if ( m_velocity.z > 0) {
			m_velocity.z = m_MaxVelocity;
		}
	}
};

class Wall : public Object3D{
private:
	int m_mode;
	float r, g, b;
	bool colorChange;

public:
	Wall() { type = objectTypeID::WALL; }

	Wall(CollisionBox Box){
		m_CollisionBox = Box;
		type = objectTypeID::WALL;
		m_mode = GL_POLYGON;
		r = 0.5;
		g = 0.5;
		b = 0.5;
		colorChange = true;
	}

	Wall(CollisionBox Box, bool _changeColor){
		m_CollisionBox = Box;
		type = objectTypeID::WALL;
		m_mode = GL_POLYGON;
		r = 0.5;
		g = 0.5;
		b = 0.5;
		colorChange = _changeColor;
	}
	~Wall() {}

	void Draw();
	void Update();
	void SetMode(int mode) { m_mode = mode; }
	void SetRGB(float _r, float _g, float _b) { 
		if(colorChange){
			r = _r; 
			g = _g;
			b = _b;
		}
	}
};

#endif // BOXSTAGE_OBJECT_H