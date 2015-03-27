#include "Object.h"
#include <sstream>

void Object::init()
{
	m_position.x = 0;
	m_position.y = 0;
	m_position.z = 0;

	m_textures = NULL;

	m_scale = 1;

	m_angleX = 0;
	m_angleY = 0;
	m_angleZ = 0;

	memset(m_modelMatrix, 0, sizeof(m_modelMatrix));
	memset(&m_ViewPosition, 0, sizeof(m_ViewPosition));
	
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
		delete[] m_textures;
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

	glGetFloatv(GL_MODELVIEW_MATRIX, m_modelMatrix);

	memset(&m_ViewPosition, 1, sizeof(m_ViewPosition));

	/*m_ViewPosition.x = m_modelMatrix[12];
	m_ViewPosition.y = m_modelMatrix[13];
	m_ViewPosition.z = m_modelMatrix[14];*/

	m_ViewPosition = MatrixRealConvert(m_ViewPosition, m_modelMatrix);

	drawStrokeText(0, 150, 0, 0.1, "(%.2f, %.2f, %.2f)", m_ViewPosition.x, m_ViewPosition.y, m_ViewPosition.z);

	// view object matrix
	for(int i = 0; i < 4; i++){
		drawStrokeText(0, 20 * (5 - i), 0, 0.05, 
			"(%.2f, %.2f, %.2f, %.2f)", 
			m_modelMatrix[(0 * 4) + i],
			m_modelMatrix[(1 * 4) + i],
			m_modelMatrix[(2 * 4) + i],
			m_modelMatrix[(3 * 4) + i]);
			
	}

	m_collisionBox;
	
}
