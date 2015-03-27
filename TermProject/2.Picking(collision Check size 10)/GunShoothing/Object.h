#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "Util.h"

class Object {
protected:
	TKpoint m_position;

	TKpoint m_viewPosition;

	CollisionBox m_collisionBox;
	
	bool m_picking;

	float m_scale;

	float m_angleX;
	float m_angleY;
	float m_angleZ;

	float m_modelMatrix[16];

	GLubyte *pBytes;
	BITMAPINFO *info;
	unsigned int* m_textures;

public:

	Object();
	Object(TKpoint setPosition);

	virtual ~Object();
	void init();

	void addTexture(char* filename[], int textureNum);

	void setPosition(TKpoint setPos) { m_position = setPos; }
	void setScale(float _scale) { m_scale = _scale; }
	void setRotate(float angleX, float angleY, float angleZ) {
		m_angleX = angleX;	m_angleY = angleY;	m_angleZ = angleZ; }
	void setPicking(bool _set) { m_picking = _set; }

	TKpoint getPosition() { return m_position; }
	TKpoint getViewPosition() { return m_viewPosition; }
	float getScale() { return m_scale; }
	float getAngleX() { return m_angleX; }
	float getAngleY() { return m_angleY; }
	float getAngleZ() { return m_angleZ; }
	bool getPicking() { return m_picking; }

	virtual void draw();
	virtual void debugDraw();
	virtual void update() = 0;
};

#endif // OBJECT_H