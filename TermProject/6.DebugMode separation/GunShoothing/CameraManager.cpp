#include "CameraManager.h"



void CamaraManager::addCameraNode(TKpoint nextNodePos, bool autoSight, bool autoMove) {
	CameraNode addnode;
	addnode.movingPoint = nextNodePos;
	addnode.autoSight = autoSight;
	addnode.autoMove = autoMove;
	addnode.staticSight = false;
	m_pointList.push_back(addnode);

	currentNode = m_pointList.begin();
}

void CamaraManager::removeAllNode() {
	m_pointList.clear();
	currentNode = m_pointList.begin();
}

void CamaraManager::setEyePos(TKpoint set_eyePoint) {
	m_eye_pos = set_eyePoint;
}

void CamaraManager::setCenterPos(TKpoint set_centerPoint) {
	m_center_endPos = set_centerPoint;
}

void CamaraManager::setNextMove(bool _set) {
	if( currentNode == m_pointList.end() )
		return;
	currentNode->autoMove = true;
}

void CamaraManager::update() {

	float speed = getDist(m_center_pos, m_center_endPos);
	TKpoint unitVector = getUnitVector(m_center_pos, m_center_endPos);

	if( abs(speed) > 1 ){

		m_center_pos.x += (unitVector.x * (speed/10.f));
		m_center_pos.y += (unitVector.y * (speed/10.f));
		m_center_pos.z += (unitVector.z * (speed/10.f));
	}

	if( currentNode == m_pointList.end() )
		return;
	
	unitVector = getUnitVector(m_eye_pos, currentNode->movingPoint);
	

	if( !( (abs(unitVector.x) == 0) && (abs(unitVector.y) == 0) && (abs(unitVector.z) == 0) ) ) {


		m_eye_pos.x += unitVector.x;
		m_eye_pos.y += unitVector.y;
		m_eye_pos.z += unitVector.z;

		if(currentNode->autoSight) {
			m_center_endPos = m_eye_pos;

			unitVector = getUnitVector(m_center_endPos, currentNode->movingPoint);


			m_center_endPos.x += (unitVector.x * 15);
			m_center_endPos.y += (unitVector.y * 15);
			m_center_endPos.z += (unitVector.z * 15);

		}

	} else if(currentNode->autoMove) {
		currentNode++;
	}
}