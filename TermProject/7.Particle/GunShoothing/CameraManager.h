#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "Util.h"
#include "GlobalValue.h"
#include <list>

#define CAMERA CamaraManager::Instance()

struct CameraNode{
	TKpoint movingPoint;
	bool autoSight;
	bool autoMove;
	bool staticSight;
};

class CamaraManager {
private:
	std::list<CameraNode> m_pointList;
	std::list<CameraNode>::iterator currentNode;
	TKpoint m_eye_pos;
	TKpoint m_center_pos;
	TKpoint m_center_endPos;

	CamaraManager(const CamaraManager&);
	CamaraManager operator=(const CamaraManager&);

	CamaraManager()
	{ 
		currentNode = m_pointList.begin(); 
		memset(&m_eye_pos, 0, sizeof(TKpoint));
		memset(&m_center_pos, 0, sizeof(TKpoint));
	}

public:
	static CamaraManager& Instance() {
		static CamaraManager instance;
		return instance;
	}

	TKpoint getEyePos() { return m_eye_pos; }
	TKpoint getCenterPos() { return m_center_pos; }

	void addCameraNode(TKpoint nextNodePos, bool autoSight, bool autoMove);
	void removeAllNode();
	void setEyePos(TKpoint set_eyePoint);
	void setCenterPos(TKpoint set_centerPoint);
	void setNextMove(bool _set);
	void update();

};

#endif //CAMERAMANAGER_H