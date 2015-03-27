#ifndef __WORLD3D_H__
#define __WORLD3D_H__

#include <iostream>
#include <vector>

#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <cstdlib>
#include <ctime>
#include "Object3D.h"

class World3D{
protected:
	World3D(){}	
	~World3D(){ m_obj.clear(); }
	World3D(const World3D&);
	World3D& operator=(const World3D&);

	std::vector<Object3D*> m_obj;

public:
	static World3D* Instance();

	void Draw();
	void Update();
	void AddObject(Object3D* object);
	Object3D* GetPointIndex(int index){ return m_obj[index]; }
};


#endif //__WORLD3D_H__