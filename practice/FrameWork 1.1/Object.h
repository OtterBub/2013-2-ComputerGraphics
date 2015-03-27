#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "Util.h"

class Object {
private:
	TKpoint m_position;
	
	float m_scale;

	float m_angleX;
	float m_angleY;
	float m_angleZ;

	GLubyte *pBytes;
	BITMAPINFO *info;
	unsigned int* textures;

public:

	Object();
	Object(TKpoint setPosition);

	~Object();
	void init();

	void addTexture(const char* filename[], int textureNum);

	void setPosition(TKpoint setPos) { m_position = setPos; }
	void setScale(float _scale) { m_scale = _scale; }
	void setRotate(float angleX, float angleY, float angleZ) {
		m_angleX = angleX;
		m_angleY = angleY;
		m_angleZ = angleZ;
	}

	TKpoint getPosition() { return m_position; }
	float getScale() { return m_scale; }
	float getAngleX() { return m_angleX; }
	float getAngleY() { return m_angleY; }
	float getAngleZ() { return m_angleZ; }

	virtual void draw();
	virtual void update() = 0;
};

#endif // OBJECT_H