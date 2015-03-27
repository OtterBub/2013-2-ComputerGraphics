#ifndef BOXSTAGE_H
#define BOXSTAGE_H

#include "World3D.h"
#include "BoxStageObject.h"

class BoxStage : public World3D{
private:

	BoxStage() { }
	~BoxStage() {}
	BoxStage(const BoxStage&);
	BoxStage& operator=(const BoxStage&);

	std::vector<Ball*> m_ball;
	std::vector<Wall*> m_wall;

public:
	static BoxStage* Instance(){
		static BoxStage instance;
		return &instance;
	}

	void Draw();
	void Update();
	void AddFunction();

	Ball* AddBall(Ball* obj);
	Wall* AddWall(Wall* obj);
};

#endif // BOXSTAGE_H