#ifndef GLOBALVALUE_H
#define GLOBALVALUE_H

#include "Util.h"
#include "Object.h"

// Define Value
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FOV SCREEN_HEIGHT
#define ASPECT float(SCREEN_WIDTH)/float(SCREEN_HEIGHT)
#define PI 3.14

// Global Value Management Class Define
#define GLOBAL GlobalValue::Instance()

// Global Value Management Class
class GlobalValue {
private:
	GlobalValue(const GlobalValue&);
	GlobalValue operator=(const GlobalValue&);

	GlobalValue()
	{
		memset(&g_eye, 0, sizeof(TKpoint));
		memset(&g_center, 0, sizeof(TKpoint));
		memset(&g_angle, 0, sizeof(TKpoint));
		memset(&pre_point, 0, sizeof(TKpoint));
		memset(&projection_point, 0, sizeof(TKpoint));
		memset(&ray_start_point, 0, sizeof(TKpoint));
		memset(&ray_end_point, 0, sizeof(TKpoint));
		memset(&g_camera, 0, sizeof(TKpoint));

		memset(&keyDown, 0, sizeof(keyDown));
		
		camera_debug = false;

		g_eye.x = 0;
		g_eye.y = 0;
		g_eye.z = 500;

		camera_eye_select = false;

		g_init = false;

		objectPointer = 0;
	}

public:
	static GlobalValue& Instance() {
		static GlobalValue instance;
		return instance;
	}


	// Use Value in CallBackFunction

	TKpoint g_eye;			// camera eye
	TKpoint g_center;		// camera center
	TKpoint g_angle;		// global angle
	TKpoint g_camera;

	bool g_init;			// init process


	// Use Value in InputFunction

	TKpoint pre_point;		// save pre mouse point
	TKpoint projection_point;
	TKpoint ray_start_point;
	TKpoint ray_end_point;

	Object* objectPointer;

	// Camera Debug
	bool camera_debug;
	bool camera_eye_select;
	bool keyDown[400];

};

#endif