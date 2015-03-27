#ifndef __PYRAMID_H__
#define __PYRAMID_H__

#include "Object3D.h"
#include "Util.h"

class Pyramid : public Object3D{
private:
	float rotate;
	float scale;
	bool cover;

	GLubyte *pBytes;
	BITMAPINFO *info;
	GLuint textures[10];

public:
	Pyramid() { 
		rotate = rand() % 360;
		scale = 1;
		cover = true;
	}
	Pyramid(float _x, float _y, float _z) 
		: Object3D(_x, _y, _z) {
			scale = 1;
			cover = true;

			glEnable(GL_TEXTURE_2D);

			glGenTextures(10, textures);

			glBindTexture(GL_TEXTURE_2D, textures[0]);
			pBytes = LoadDIBitmap("stone-wall.bmp", &info);
			if(pBytes == NULL)
				printf("Image Load Fail\n");
			else printf("Image Load Success\n");
			glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 128, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glBindTexture(GL_TEXTURE_2D, textures[1]);
			pBytes = LoadDIBitmap("Golf_Ball.bmp", &info);
			if(pBytes == NULL)
				printf("Image Load Fail\n");
			else printf("Image Load Success\n");
			glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 128, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	}
	Pyramid(float _x, float _y, float _z, float _scale)
		: Object3D(_x, _y, _z) {
			scale = _scale;
			cover = true;

			glEnable(GL_TEXTURE_2D);
			glGenTextures(10, textures);

			glBindTexture(GL_TEXTURE_2D, textures[0]);
			pBytes = LoadDIBitmap("stone-wall.bmp", &info);
			if(pBytes == NULL)
				printf("Image Load Fail\n");
			else printf("Image Load Success\n");
			glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 128, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glBindTexture(GL_TEXTURE_2D, textures[1]);
			pBytes = LoadDIBitmap("Golf_Ball.bmp", &info);
			if(pBytes == NULL)
				printf("Image Load Fail\n");
			else printf("Image Load Success\n");
			glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 128, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	void Draw();
	void Update();
	void AddFuntion() {
		if(cover)
			cover = false;
		else
			cover = true;
	}
};

#endif //__PYRAMID_H__