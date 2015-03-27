#include "Object.h"

void Object::init()
{
	m_position.x = 0;
	m_position.y = 0;
	m_position.z = 0;

	m_scale = 1;

	m_angleX = 0;
	m_angleY = 0;
	m_angleZ = 0;
}

Object::Object()
{
	init();
}

Object::Object(TKpoint setPosition)
{
	init();
	m_position = setPosition;
}

Object::~Object()
{
	delete m_textures;
}

void Object::addTexture(char* filename[], int textureNum) {

	if(m_textures != NULL)
		delete m_textures;
	m_textures = new unsigned int[textureNum];

	glGenTextures(textureNum, m_textures);

	for(int i = 0; i < textureNum; i++){
		glBindTexture(GL_TEXTURE_2D, m_textures[i]);
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

void Object::draw()
{
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glScalef(m_scale, m_scale, m_scale);
	glRotatef(m_angleX, 1, 0, 0);
	glRotatef(m_angleY, 0, 1, 0);
	glRotatef(m_angleZ, 0, 0, 1);
}
