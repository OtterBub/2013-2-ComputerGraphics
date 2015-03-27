#ifndef PORTALWALL_H
#define PORTALWALL_H

#include "BoxStageObject.h"
#include "Util.h"

enum PotalPosition {
	LEFT,
	RIGHT,
	FRONT,
	BACK,
	TOP,
	BOTTOM,
	DEFALLT
};

class PortalWall : public Object3D {
private:
	int m_mode;
	float r, g, b;
	bool colorChange;
	int portalType;
	
	bool colorTwinkle;
	int colorChangeTime;
public:
	PortalWall(CollisionBox Box){
		m_CollisionBox = Box;
		type = objectTypeID::PORTAL;
		m_mode = GL_POLYGON;
		r = 0.5;
		g = 0.5;
		b = 0.5;
		colorChange = true;
		
		_point lineLength;
		lineLength.x = (m_CollisionBox.Max.x - m_CollisionBox.Min.x);
		lineLength.y = (m_CollisionBox.Max.y - m_CollisionBox.Min.y);
		lineLength.z = (m_CollisionBox.Max.z - m_CollisionBox.Min.z);

		point.x = (lineLength.x / 2) + m_CollisionBox.Min.x;
		point.y = (lineLength.y / 2) + m_CollisionBox.Min.y;
		point.z = (lineLength.z / 2) + m_CollisionBox.Min.z;

		portalType = DEFALLT;
		colorTwinkle = false;
		colorChangeTime = clock();
	}

	PortalWall(CollisionBox Box, int wallType){
		m_CollisionBox = Box;
		type = objectTypeID::PORTAL;
		m_mode = GL_POLYGON;
		r = 0.5;
		g = 0.5;
		b = 0.5;
		colorChange = true;
		
		_point lineLength;
		lineLength.x = (m_CollisionBox.Max.x - m_CollisionBox.Min.x);
		lineLength.y = (m_CollisionBox.Max.y - m_CollisionBox.Min.y);
		lineLength.z = (m_CollisionBox.Max.z - m_CollisionBox.Min.z);

		point.x = (lineLength.x / 2) + m_CollisionBox.Min.x;
		point.y = (lineLength.y / 2) + m_CollisionBox.Min.y;
		point.z = (lineLength.z / 2) + m_CollisionBox.Min.z;

		portalType = wallType;
		colorTwinkle = false;
		colorChangeTime = clock();
	}

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

	int GetWallType() { return portalType; }
};

#endif // PORTALWALL_H