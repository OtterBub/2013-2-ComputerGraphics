#ifndef BOXSTAGE_H
#define BOXSTAGE_H

#include "World3D.h"
#include "PortalWall.h"

class BoxStage : public World3D{
private:

	BoxStage() { }
	~BoxStage() {}
	BoxStage(const BoxStage&);
	BoxStage& operator=(const BoxStage&);

	std::vector<Ball*> m_ball;
	std::vector<Wall*> m_wall;
	std::vector<PortalWall*> m_portal;

	std::vector<PortalWall*> m_Wallportal;

public:
	static BoxStage* Instance(){
		static BoxStage instance;
		return &instance;
	}

	void Draw();
	void Update();
	void AddFunction();
	void AddFunctionWall();

	Ball* AddBall(Ball* obj);
	Wall* AddWall(Wall* obj);
	PortalWall* AddPortal(PortalWall* obj);
	PortalWall* AddWallPortal(PortalWall* obj);
};

#endif // BOXSTAGE_H