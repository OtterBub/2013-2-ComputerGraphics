#ifndef __WORLD3D_H__
#define __WORLD3D_H__

#include <iostream>
#include <vector>
#include <algorithm>


#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <cstdlib>
#include <ctime>
#include "Object3D.h"
#include "Snow.h"

class World3D{
protected:
	
	std::vector<Object3D*> m_obj;
	bool m_update;

	World3D(){ m_update = true; }	
	~World3D(){ m_obj.clear(); }
	World3D(const World3D&);
	World3D& operator=(const World3D&);

	std::vector<GroundSnow> m_groundsnow;
	
public:
	static World3D* Instance();

	void Draw();
	void Update();
	void AddObject(Object3D* object);
	Object3D* GetPointIndex(int index){ return m_obj[index]; }
	void AddFunction();
	
	void AddLight(int lightNum);
	void RemoveLight(int lightNum);
	void SetLightPos(int lightNum, float light_x, float light_y, float light_z, float light_infinit_local);
	void SetLightColor(int lightNum, GLenum pname , float light_R, float light_G, float light_B, float light_A);

	void UpdateStop() { 
		if(m_update)
			m_update = false;
		else
			m_update = true;
	}
};


#endif //__WORLD3D_H__