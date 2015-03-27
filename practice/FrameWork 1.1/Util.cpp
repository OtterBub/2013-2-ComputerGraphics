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

GLubyte* LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	if( ( fp = fopen(filename, "rb")) == NULL )
		return NULL;

	if( fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1 ) {
		fclose(fp);
		return NULL;
	}

	if( header.bfType != 'MB' ) {
		fclose(fp);
		return NULL;
	}

	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	if( ( *info = (BITMAPINFO *)malloc(infosize)) == NULL ) {
		fclose(fp);
		//exit(0);
		return NULL;
	}

	if( fread(*info, 1, infosize, fp) < (unsigned int)infosize ) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	if( ( bitsize = (*info)->bmiHeader.biSizeImage) == 0 ) {
		bitsize = ( (*info)->bmiHeader.biWidth *
			(*info)->bmiHeader.biBitCount + 7 ) / 8.0 *
			abs((*info)->bmiHeader.biHeight);
	}

	if( ( bits = (unsigned char*)malloc(bitsize) ) == NULL ) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	if( fread(bits, 1, bitsize, fp) < (unsigned int)bitsize ) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}