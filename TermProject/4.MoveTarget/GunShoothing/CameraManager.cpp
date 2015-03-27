#include "CameraManager.h"



void CamaraManager::addCameraNode(TKpoint nextNodePos, bool autoSight, bool autoMove) {
	CameraNode addnode;
	addnode.movingPoint = nextNodePos;
	addnode.autoSight = autoSight;
	addnode.autoMove = autoMove;
	m_pointList.push_back(addnode);
}

void CamaraManager::setEyePos(TKpoint set_eyePoint) {
	m_eye_pos = set_eyePoint;
}

void CamaraManager::setCenterPos(TKpoint set_centerPoint) {
	m_center_pos = set_centerPoint;
}

void CamaraManager::update() {
	
}