#include "Util.h"

bool CollisionCheck(CollisionBox A, CollisionBox B)
{
	if( (A.Max.x >= B.Min.x) && (A.Min.x <= B.Max.x) &&
		(A.Max.y >= B.Min.y) && (A.Min.y <= B.Max.y) &&
		(A.Max.z >= B.Min.z) && (A.Min.z <= B.Max.z) )
		return true;
	return false;
}

void drawStrokeText(char *string, float x, float y, float z, float scale){
	char *c;
	glPushMatrix();
	{
		glTranslatef(x, y, z);
		glColor3f(1.0, 1.0, 1.0);
		//glScalef(0.09f, 0.08f, z);
		glScalef(scale, scale, scale);
		for(c = string; *c != '\0'; c++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();
}