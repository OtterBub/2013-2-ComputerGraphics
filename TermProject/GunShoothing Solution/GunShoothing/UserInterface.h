#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Util.h"
#include "CallBackFunction.h"
#include "World.h"

// UserInterface Class Define
#define UI UserInterface::Instance()

// UserInterface Class
class UserInterface {
private:

	int m_capacity;
	int m_score;
	int m_stage;
	int m_scene;
	int m_shotEnemy;

	UserInterface(const UserInterface&);
	UserInterface operator=(const UserInterface&);

	UserInterface()
	{
		m_capacity = 0;
		m_score = 0;
		m_stage = 0;
		m_scene = 0;
	}

	~UserInterface() {
	}

public:
	
	static UserInterface& Instance() {
		static UserInterface instance;
		return instance;
	}
	void initScene() { m_scene = 0; m_shotEnemy = 0; }
	void setStage(int set) { WORLD.removeAllObject(); GLOBAL.g_init = false; m_stage = set; initScene(); }
	void addShotNum() { m_shotEnemy++; }
	void draw();
	void update();
};

#endif //USERINTERFACE_H