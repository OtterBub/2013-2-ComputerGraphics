#ifndef GUNSHOOTHINGOBJECT_H
#define GUNSHOOTHINGOBJECT_H

#include "Object.h"
#include "TextureManager.h"

class Target : public Object {
private:
	bool m_shootable;

public:
	Target(TKpoint setPosition);
	~Target();

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