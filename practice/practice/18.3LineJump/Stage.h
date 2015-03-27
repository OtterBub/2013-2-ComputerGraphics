#ifndef __STAGE_H__
#define __STAGE_H__

#include "World3D.h"
#include "Object3D.h"
#include "Char.h"

class Ground : public Object3D{
	float width, height;
	float ghost;
public:
	Ground(){
		point.x = 0;
		point.y = 0;
		point.z = 0;
	}
	Ground(float x, float y, float z){
		point.x = x;
		point.y = y;
		point.z = z;
		ghost = 0;
	}
	void Draw();
	void Update();
};

#define GROUND_SIZE 300.0f

class Stage : public World3D{
private:
	Stage() { init = true; }
	Stage(const Stage&);
	Stage& operator=(const Stage&);
	Mainchar* m_Main;
	std::vector<Ground*> m_ground;
	bool init;
public:
	~Stage(){ }
	static Stage* Instance(){
		static Stage instance;
		return &instance;
	}
	void SetChar(Mainchar* main) { m_Main = main; }
	void Draw();
	void Update();
};


#endif