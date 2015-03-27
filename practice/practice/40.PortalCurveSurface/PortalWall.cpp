#include "PortalWall.h"

void PortalWall::Draw()
{
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);

	glBegin(m_mode);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0.0, 0.0);
	glColor4f(r, g, b, 0.5);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glTexCoord2f(1.0, 0.0);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glTexCoord2f(1.0, 1.0);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glTexCoord2f(0.0, 1.0);
	glColor4f(r, g, b, 0.5);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(m_mode);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0.0, 0.0);
	glColor4f(r, g, b, 0.5);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glTexCoord2f(1.0, 0.0);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glTexCoord2f(1.0, 1.0);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glTexCoord2f(0.0, 1.0);
	glColor4f(r, g, b, 0.5);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(m_mode);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0, 0.0);
	glColor4f(r, g, b, 0.5);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glTexCoord2f(1.0, 0.0);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glTexCoord2f(1.0, 1.0);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glTexCoord2f(0.0, 1.0);
	glColor4f(r, g, b, 0.5);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();
	
	glBegin(m_mode);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0.0, 0.0);
	glColor4f(r, g, b, 0.5);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glTexCoord2f(1.0, 0.0);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glTexCoord2f(1.0, 1.0);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glTexCoord2f(0.0, 1.0);
	glColor4f(r, g, b, 0.5);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glEnd();

	glBegin(m_mode);
	glNormal3f(1, 0, 0);
	glTexCoord2f(0.0, 0.0);
	glColor4f(r, g, b, 0.5);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glTexCoord2f(1.0, 0.0);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glTexCoord2f(1.0, 1.0);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glTexCoord2f(0.0, 1.0);
	glColor4f(r, g, b, 0.5);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(m_mode);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0.0, 0.0);
	glColor4f(r, g, b, 0.5);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glTexCoord2f(1.0, 0.0);
	glColor3f(g, b, r);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glTexCoord2f(1.0, 1.0);
	glColor3f(b, r, g);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glTexCoord2f(0.0, 1.0);
	glColor4f(r, g, b, 0.5);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glEnd();	

	glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(GL_LINE_LOOP);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(GL_LINE_LOOP);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(GL_LINE_LOOP);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(GL_LINE_LOOP);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Min.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Min.z);
	glEnd();	

	glBegin(GL_LINE_LOOP);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Max.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Min.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glVertex3f(m_CollisionBox.Max.x, m_CollisionBox.Min.y, m_CollisionBox.Max.z);
	glEnd();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}
void PortalWall::Update()
{
	if(20 <= clock() - colorChangeTime){
		if(colorTwinkle) {
			r -= 0.01;
			g -= 0.01; 
			b -= 0.01; 
			if(b <= 0)
				colorTwinkle = false;
		} else {
			r += 0.01;
			g += 0.01; 
			b += 0.01; 
			if(b >= 0.5)
				colorTwinkle = true;
		}
	}
}