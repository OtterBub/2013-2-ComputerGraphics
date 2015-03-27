#ifndef BOXSTAGE_OBJECT_H
#define BOXSTAGE_OBJECT_H

#include "Object3D.h"
#include "Util.h"

class Ball : public Object3D {
private:
	_point m_velocity;
	float r, g, b;
	float m_MaxVelocity;
	bool m_onlyLine;
	bool m_debug;

	GLubyte *pBytes;
	BITMAPINFO *info;
	GLuint textures[10];
	
public:
	Ball() { type = objectTypeID::BALL; }
	Ball(float _x, float _y, float _z)
		: Object3D(_x, _y, _z){
			type = objectTypeID::BALL;
			m_velocity.x = 2;
			m_velocity.y = 2;
			m_velocity.z = -2;

			r = 0.5;
			g = 0.5;
			b = 1;
			m_debug = false;
			m_CollisionBox.Max.x = point.x + 10;
			m_CollisionBox.Min.x = point.x - 10;

			m_CollisionBox.Max.y = point.y + 10;
			m_CollisionBox.Min.y = point.y - 10;

			m_CollisionBox.Max.z = point.z + 10;
			m_CollisionBox.Min.z = point.z - 10;
			m_MaxVelocity = 5;
			m_onlyLine = true;
	}
	Ball(float _x, float _y, float _z, float _scale)
		: Object3D(_x, _y, _z, _scale){
			type = objectTypeID::BALL;
			m_velocity.x = 2;
			m_velocity.y = 0;
			m_velocity.z = 0;
			r = g = b = 0;
			m_debug = false;
			m_CollisionBox.Max.x = point.x + 10;
			m_CollisionBox.Min.x = point.x - 10;

			m_CollisionBox.Max.y = point.y + 10;
			m_CollisionBox.Min.y = point.y - 10;

			m_CollisionBox.Max.z = point.z + 10;
			m_CollisionBox.Min.z = point.z - 10;
			m_MaxVelocity = 5;
			m_onlyLine = false;
	}

	Ball(float _x, float _y, float _z,
		float vel_x, float vel_y, float vel_z)
		: Object3D(_x, _y, _z){
			type = objectTypeID::BALL;
			m_velocity.x = vel_x;
			m_velocity.y = vel_y;
			m_velocity.z = vel_z;
			r = 1;
			g = 1;
			b = 1;
			m_debug = false;
			m_CollisionBox.Max.x = point.x + 10;
			m_CollisionBox.Min.x = point.x - 10;

			m_CollisionBox.Max.y = point.y + 10;
			m_CollisionBox.Min.y = point.y - 10;

			m_CollisionBox.Max.z = point.z + 10;
			m_CollisionBox.Min.z = point.z - 10;
			m_MaxVelocity = 5;
			m_onlyLine = false;
	}

	~Ball() {}

	bool Bound(CollisionBox Box);

	void Draw();
	void Update();
	void AddVelocity(float _x, float _y, float _z);
	void ColorChange(float _r, float _g, float _b);

	void AddFuntion() {
		if(m_debug)
			m_debug = false;
		else
			m_debug = true;
	}

	float getR() { return r; }
	float getG() { return g; }
	float getB() { return b; }
};

class Wall : public Object3D{
private:
	int m_mode;
	float r, g, b;
	bool colorChange;
	bool bTexture;

	GLubyte *pBytes;
	BITMAPINFO *info;
	GLuint textures[10];

public:
	Wall() { type = objectTypeID::WALL; }

	Wall(CollisionBox Box){
		m_CollisionBox = Box;
		type = objectTypeID::WALL;
		m_mode = GL_POLYGON;
		r = 0.5;
		g = 0.5;
		b = 0.5;
		colorChange = true;
		bTexture = false;
	}

	Wall(CollisionBox Box, bool _changeColor){
		m_CollisionBox = Box;
		type = objectTypeID::WALL;
		m_mode = GL_POLYGON;
		r = 0.5;
		g = 0.5;
		b = 0.5;
		colorChange = _changeColor;
		bTexture = false;
	}

	Wall(CollisionBox Box, const char* filename){
		m_CollisionBox = Box;
		type = objectTypeID::WALL;
		m_mode = GL_POLYGON;
		r = 0.5;
		g = 0.5;
		b = 0.5;
		colorChange = false;
		bTexture = true;
		
		glGenTextures(10, textures);

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		pBytes = LoadDIBitmap("1.bmp", &info);
		if(pBytes == NULL)
			printf("Image Load Fail\n");
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 128, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, textures[1]);
		pBytes = LoadDIBitmap("2.bmp", &info);
		if(pBytes == NULL)
			printf("Image Load Fail\n");
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 128, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, textures[2]);
		pBytes = LoadDIBitmap("3.bmp", &info);
		if(pBytes == NULL)
			printf("Image Load Fail\n");
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 128, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	}

	Wall(CollisionBox Box, const char filename[][50], int index){
		m_CollisionBox = Box;
		type = objectTypeID::WALL;
		m_mode = GL_POLYGON;
		r = 0.5;
		g = 0.5;
		b = 0.5;
		colorChange = true;
		bTexture = true;
		
		for(int i = 0; i < 10; i++)
			textures[i] = NULL;

		glGenTextures(index, textures);

		for(int i = 0; i < index; i++){
			glBindTexture(GL_TEXTURE_2D, textures[i]);
			pBytes = LoadDIBitmap(filename[i], &info);
			if(pBytes == NULL)
				printf("Image Load Fail\n");
			glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 128, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
		}
	}
	~Wall() {}

	void Draw();
	void Update();
	void SetMode(int mode) { m_mode = mode; }
	void SetRGB(float _r, float _g, float _b) { 
		if(colorChange){
			r = _r; 
			g = _g;
			b = _b;
		}
	}
};

class ColorWall : public Object3D{
private:
	int m_mode;
	float r, g, b;
	bool colorChange;

public:
	ColorWall() { type = objectTypeID::COLORWALL; }

	ColorWall(CollisionBox Box){
		m_CollisionBox = Box;
		type = objectTypeID::COLORWALL;
		m_mode = GL_POLYGON;
		r = 0.5;
		g = 0.5;
		b = 0.5;
		colorChange = true;
	}

	ColorWall(CollisionBox Box, bool _changeColor){
		m_CollisionBox = Box;
		type = objectTypeID::COLORWALL;
		m_mode = GL_POLYGON;
		r = 0.5;
		g = 0.5;
		b = 0.5;
		colorChange = _changeColor;
	}
	~ColorWall() {}

	void Draw();
	void Update();
	void SetMode(int mode) { m_mode = mode; }
	void SetRGB(float _r, float _g, float _b) { 
		if(colorChange){
			r = _r; 
			g = _g;
			b = _b;
		}
	}
};

#endif // BOXSTAGE_OBJECT_H