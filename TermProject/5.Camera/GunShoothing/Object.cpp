#include "Object.h"
#include <sstream>

void Object::init()
{
	m_position.x = 0;
	m_position.y = 0;
	m_position.z = 0;

	m_textures = NULL;

	m_picking = false;

	m_scale = 1;

	m_angleX = 0;
	m_angleY = 0;
	m_angleZ = 0;

	m_destroy = false;

	memset(m_modelMatrix, 0, sizeof(m_modelMatrix));
	memset(&m_viewPosition, 0, sizeof(m_viewPosition));
	
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

bool Object::drawTextureBegin(int index) {
	if(m_textures[index] == NULL) {
		return false;
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_textures[index]);
	
	return true;
}

void Object::drawTextureEnd() {
	glDisable(GL_TEXTURE_2D);
}

bool Object::pickingCheck(TKpoint pick) 
{
	if( ((m_viewPosition.x - 10) < pick.x) && ((m_viewPosition.x + 10) > pick.x) &&
		((m_viewPosition.y - 10) < pick.y) && ((m_viewPosition.y + 10) > pick.y) &&
		((m_viewPosition.z - 10) < pick.z) && ((m_viewPosition.z + 10) > pick.z)){
			return true;
	}
	return false;
}

void Object::debugDraw() 
{
	glPushMatrix();
	{
		glLoadIdentity();

		glColor3f(1, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(m_collisionBox.Min.x, m_collisionBox.Min.y, m_collisionBox.Min.z);
		glVertex3f(m_collisionBox.Max.x, m_collisionBox.Min.y, m_collisionBox.Min.z);
		glVertex3f(m_collisionBox.Max.x, m_collisionBox.Max.y, m_collisionBox.Min.z);
		glVertex3f(m_collisionBox.Min.x, m_collisionBox.Max.y, m_collisionBox.Min.z);
		glEnd();	

		glBegin(GL_LINE_LOOP);
		glVertex3f(m_collisionBox.Min.x, m_collisionBox.Min.y, m_collisionBox.Min.z);
		glVertex3f(m_collisionBox.Min.x, m_collisionBox.Min.y, m_collisionBox.Max.z);
		glVertex3f(m_collisionBox.Min.x, m_collisionBox.Max.y, m_collisionBox.Max.z);
		glVertex3f(m_collisionBox.Min.x, m_collisionBox.Max.y, m_collisionBox.Min.z);
		glEnd();	

		glBegin(GL_LINE_LOOP);
		glVertex3f(m_collisionBox.Min.x, m_collisionBox.Min.y, m_collisionBox.Min.z);
		glVertex3f(m_collisionBox.Min.x, m_collisionBox.Min.y, m_collisionBox.Max.z);
		glVertex3f(m_collisionBox.Min.x, m_collisionBox.Max.y, m_collisionBox.Max.z);
		glVertex3f(m_collisionBox.Min.x, m_collisionBox.Max.y, m_collisionBox.Min.z);
		glEnd();	

		glBegin(GL_LINE_LOOP);
		glVertex3f(m_collisionBox.Min.x, m_collisionBox.Min.y, m_collisionBox.Min.z);
		glVertex3f(m_collisionBox.Min.x, m_collisionBox.Min.y, m_collisionBox.Max.z);
		glVertex3f(m_collisionBox.Max.x, m_collisionBox.Min.y, m_collisionBox.Max.z);
		glVertex3f(m_collisionBox.Max.x, m_collisionBox.Min.y, m_collisionBox.Min.z);
		glEnd();	

		glBegin(GL_LINE_LOOP);
		glVertex3f(m_collisionBox.Max.x, m_collisionBox.Max.y, m_collisionBox.Max.z);
		glVertex3f(m_collisionBox.Max.x, m_collisionBox.Min.y, m_collisionBox.Max.z);
		glVertex3f(m_collisionBox.Max.x, m_collisionBox.Min.y, m_collisionBox.Min.z);
		glVertex3f(m_collisionBox.Max.x, m_collisionBox.Max.y, m_collisionBox.Min.z);
		glEnd();	

		glBegin(GL_LINE_LOOP);
		glVertex3f(m_collisionBox.Max.x, m_collisionBox.Max.y, m_collisionBox.Max.z);
		glVertex3f(m_collisionBox.Min.x, m_collisionBox.Max.y, m_collisionBox.Max.z);
		glVertex3f(m_collisionBox.Min.x, m_collisionBox.Min.y, m_collisionBox.Max.z);
		glVertex3f(m_collisionBox.Max.x, m_collisionBox.Min.y, m_collisionBox.Max.z);
		glEnd();
	}
	glPopMatrix();
}

void Object::draw()
{
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glScalef(m_scale, m_scale, m_scale);
	glRotatef(m_angleX, 1, 0, 0);
	glRotatef(m_angleY, 0, 1, 0);
	glRotatef(m_angleZ, 0, 0, 1);

	glGetFloatv(GL_MODELVIEW_MATRIX, m_modelMatrix);

	memset(&m_viewPosition, 1, sizeof(m_viewPosition));
	/*m_viewPosition.x = m_modelMatrix[12];
	m_viewPosition.y = m_modelMatrix[13];
	m_viewPosition.z = m_modelMatrix[14];*/

	m_viewPosition = MatrixRealConvert(m_viewPosition, m_modelMatrix);

	drawStrokeText(0, 150, 0, 0.1, "(%.2f, %.2f, %.2f)", m_viewPosition.x, m_viewPosition.y, m_viewPosition.z);

	// view object matrix
	for(int i = 0; i < 4; i++){
		drawStrokeText(0, 20 * (5 - i), 0, 0.05, 
			"(%.2f, %.2f, %.2f, %.2f)", 
			m_modelMatrix[(0 * 4) + i],
			m_modelMatrix[(1 * 4) + i],
			m_modelMatrix[(2 * 4) + i],
			m_modelMatrix[(3 * 4) + i]);
	}
}