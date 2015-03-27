#include "UserInterface.h"

void UserInterface::draw() {
	glPushMatrix();

	drawStrokeText(0, 0.5, -1, 0.0005, "%.1f, %.1f, %.1f", GLOBAL.g_eye.x, GLOBAL.g_eye.y, GLOBAL.g_eye.z);
	drawStrokeText(-0.7, 0.5, -1, 0.0005, "Stage %d-%d", m_stage, m_scene);
	drawStrokeText(-0.6, 0.4, -1, 0.0005, "shotEnemy %d", m_shotEnemy);

	glPopMatrix();
}

void UserInterface::update() {

	switch(m_stage) {
	case 0:
		return;
	case 1:
		initStage1();
		switch(m_scene){
		case 1:
			if(m_shotEnemy >= 1) {
				CAMERA.setNextMove(true);
			}
			break;
		case 2:
			if(m_shotEnemy >= 3) {
				CAMERA.setNextMove(true);
			}
			break;
		case 3:
			if(m_shotEnemy >= 6) {
				CAMERA.setNextMove(true);
			}
		case 4:
			if(m_shotEnemy >= 7) {
				CAMERA.setNextMove(true);
			}
			break;
		case 6:
			if(m_shotEnemy >= 9) {
				CAMERA.setNextMove(true);
			}
			break;
		}
		break;
	case 2:
		initStage2();
		
		break;
	}

	if(CAMERA.getEndNode()) {
		m_scene++;
		switch(m_stage) {
		case 1:
			initTartgetStage1(m_scene);
			break;
		case 2:
			break;
		}
	}
}