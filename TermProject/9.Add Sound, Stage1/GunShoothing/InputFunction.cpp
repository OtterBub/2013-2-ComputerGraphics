#include "InputFunction.h"
#include "WorldInit.h"

void mouseFunc(int button, int state, int x, int y)
{
	if((button == GLUT_LEFT && state == GLUT_DOWN)){
		int viewport[4];
		double modelview[16];
		double projection[16];
		float winX, winY;

		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);

		float z_cursor;
		winX = (float)x;
		winY = (float)viewport[3] - (float)y;
		glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z_cursor);

		double temp_x, temp_y, temp_z;

		gluUnProject(winX, winY, z_cursor, modelview, projection, viewport, &temp_x, &temp_y, &temp_z);

		GLOBAL.projection_point.x = temp_x;
		GLOBAL.projection_point.y = temp_y;
		GLOBAL.projection_point.z = temp_z;

		std::cout << GLOBAL.projection_point.x << ", " 
			<< GLOBAL.projection_point.y << ", "
			<< GLOBAL.projection_point.z << std::endl;

		WORLD.pickingCheck(GLOBAL.projection_point);
		SOUND.pSystem->playSound(FMOD_CHANNEL_FREE, SOUND.pSound[SOUNDKIND::SD_GUN_SHOT], FALSE, &(SOUND.pChannel));
		
	}

	GLOBAL.pre_point.x = x;
	GLOBAL.pre_point.y = y;
}

void mouseMove(int x, int y)
{
	GLOBAL.g_angle.y -= (GLOBAL.pre_point.x - (float)x) / 5;
	GLOBAL.g_angle.x -= (GLOBAL.pre_point.y - (float)y) / 5;

	GLOBAL.pre_point.x = x;
	GLOBAL.pre_point.y = y;

	glutPostRedisplay();
}

void keyBoardFunc(unsigned char key, int x, int y)
{
	GLOBAL.keyDown[key] = true;

	switch(key) {
	case 'a':
		GLOBAL.g_eye.x -= 5;
		GLOBAL.g_center.x -= 5;
		break;
	case 'd':
		GLOBAL.g_eye.x += 5;
		GLOBAL.g_center.x += 5;
		break;
	case 'w':
		GLOBAL.g_eye.z -= 5;
		GLOBAL.g_center.z -= 5;
		break;
	case 's':
		GLOBAL.g_eye.z += 5;
		GLOBAL.g_center.z += 5;
		break;

	case 'r':
		GLOBAL.g_eye.y += 5;
		GLOBAL.g_center.y += 5;
		break;
	case 'f':
		GLOBAL.g_eye.y -= 5;
		GLOBAL.g_center.y -= 5;
		break;
	case ' ':
		WORLD.removeAllObject();
		GLOBAL.g_init = false;
		break;
	case '1':
		UI.setStage(0);
		init();		
		break;
	case '2':
		UI.setStage(0);
		initTest();		
		break;
	case '3':
		UI.setStage(0);
		initCameraTest();		
		break;
	case '4':
		UI.setStage(0);
		initStage1();		
		break;
	case '5':
		UI.setStage(0);
		initStage2();		
		break;
	case '6':
		UI.setStage(0);
		initParticleTest();
		break;

	case '9':
		UI.setStage(1);
		break;

	case '0':
		UI.setStage(2);
		break;

	case 'b': 
		GLOBAL.camera_debug = !(GLOBAL.camera_debug);
		if(GLOBAL.camera_debug){
			GLOBAL.g_center = GLOBAL.g_eye;
			GLOBAL.g_center.z -= 10;
		}
			
		break;

	case 't':
		CAMERA.removeAllNode();
		GLOBAL.camera_eye_select = !(GLOBAL.camera_eye_select);
		break;

	case 'i':
		if(GLOBAL.camera_eye_select) {
			TKpoint setCamera;
			setCamera = CAMERA.getEyePos();
			setCamera.z -= 5;
			CAMERA.setEyePos(setCamera);
		} else {
			TKpoint setCamera;
			setCamera = CAMERA.getCenterPos();
			setCamera.z -= 5;
			CAMERA.setCenterPos(setCamera);
		}
		break;
	case 'k':
		if(GLOBAL.camera_eye_select) {
			TKpoint setCamera;
			setCamera = CAMERA.getEyePos();
			setCamera.z += 5;
			CAMERA.setEyePos(setCamera);
		} else {
			TKpoint setCamera;
			setCamera = CAMERA.getCenterPos();
			setCamera.z += 5;
			CAMERA.setCenterPos(setCamera);
		}
		break;
	case 'j':
		if(GLOBAL.camera_eye_select) {
			TKpoint setCamera;
			setCamera = CAMERA.getEyePos();
			setCamera.x -= 5;
			CAMERA.setEyePos(setCamera);
		} else {
			TKpoint setCamera;
			setCamera = CAMERA.getCenterPos();
			setCamera.x -= 5;
			CAMERA.setCenterPos(setCamera);
		}
		break;
	case 'l':
		if(GLOBAL.camera_eye_select) {
			TKpoint setCamera;
			setCamera = CAMERA.getEyePos();
			setCamera.x += 5;
			CAMERA.setEyePos(setCamera);
		} else {
			TKpoint setCamera;
			setCamera = CAMERA.getCenterPos();
			setCamera.x += 5;
			CAMERA.setCenterPos(setCamera);
		}
		break;

	default:
		break;
	}
}

void keyBoardUpFunc(unsigned char key, int x, int y)
{
	GLOBAL.keyDown[key] = false;
	
	switch(key) {
	default:
		break;
	}
}