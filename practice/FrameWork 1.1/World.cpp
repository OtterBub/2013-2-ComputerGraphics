#include "World.h"

World::World()
{

}

World::~World()
{

}

World& World::Instance()
{
	static World instance;
	return instance;
}

void World::addTexture(const char* filename) {
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

void World::draw()
{
	std::vector<Object*>::iterator it = m_objVec.begin();

	for(it ; it != m_objVec.end(); it++) {
		glPushMatrix();
		(*it)->draw();
		glPopMatrix();
	}
}

void World::update()
{
	std::vector<Object*>::iterator it = m_objVec.begin();

	for(it ; it != m_objVec.end(); it++) {
		(*it)->update();
	}
}