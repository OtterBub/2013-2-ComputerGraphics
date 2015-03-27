#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Util.h"
#include "Object.h"

#define TEXTURE_NUM 5

#define TEXTURE_STONE_WALL 0
#define TEXTURE_TARGET 1
#define TEXTURE_CRACK_PILLAR 2
#define TEXTURE_GROUND 3
#define TEXTURE_BARREL 4

// TextureManager Class Define
#define TEXTURE TextureManager::Instance()

// TextureManager Class
class TextureManager {
private:

	unsigned int* m_textures;

	TextureManager(const TextureManager&);
	TextureManager operator=(const TextureManager&);

	TextureManager()
	{
		GLubyte *pBytes;
		BITMAPINFO *info;
		char* filename[TEXTURE_NUM] = {
			"stone-wall.bmp",
			"target.bmp",
			"concrete_cracked.bmp",
			"ground.bmp",
			"oildrum_texturestart.bmp"
		};

		m_textures = new unsigned int[TEXTURE_NUM];

		glGenTextures(TEXTURE_NUM, m_textures);

		for(int i = 0; i < TEXTURE_NUM; i++){
			glBindTexture(GL_TEXTURE_2D, m_textures[i]);
			pBytes = LoadDIBitmap(filename[i], &info);
			if(pBytes == NULL)
				printf("Image Load Fail\n");
			glTexImage2D(GL_TEXTURE_2D, 0, 3, 128, 128, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
		}
	}

	~TextureManager() {
		delete[] m_textures;
	}

public:
	
	static TextureManager& Instance() {
		static TextureManager instance;
		return instance;
	}
	
	bool drawTextureBegin(int index);
	void drawAutoMapping(int mappingmode);
	void drawTextureEnd();
};



#endif //TEXTUREMANAGER_H