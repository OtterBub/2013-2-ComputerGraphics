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

void drawStrokeText(float x, float y, float z, float scale, char *fmt, ...) {
	
	va_list arg;
	va_start(arg, fmt);

	const int ibufsize = strlen(fmt);

	char cbuf[512]/* = new char[ibufsize]*/;
	vsprintf(cbuf, fmt, arg);

	char *c;
	glPushMatrix();
	{
		glTranslatef(x, y, z);
		glColor3f(1.0, 1.0, 1.0);
		//glScalef(0.09f, 0.08f, z);
		glScalef(scale, scale, scale);
		for(c = cbuf; *c != '\0'; c++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();

	//delete cbuf;
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

POINT SRTconvertToPoint(POINT point, float scaleX, float scaleY, float angle, float trans_x, float trans_y) {
	POINT result = point;

	result.x = result.x * scaleX;
	result.y = result.y * scaleY;

	float tempX = result.x;

	result.x = (cos(angle * (3.14/180)) * result.x) + (-sin(angle * (3.14/180)) * result.y) + trans_x;
	result.y = (sin(angle * (3.14/180)) * tempX) + (cos(angle * (3.14/180)) * result.y) + trans_y;

	return result;
}

TKpoint MatrixRealConvert(TKpoint point, float modelview[16])
{
	
	TKpoint result = point;


	result.x = (modelview[0] * point.x) + (modelview[4] * point.y) + (modelview[8] * point.z) + (modelview[12] * 1);
	result.y = (modelview[1] * point.x) + (modelview[5] * point.y) + (modelview[9] * point.z) + (modelview[13] * 1);
	result.z = (modelview[2] * point.x) + (modelview[6] * point.y) + (modelview[10] * point.z) + (modelview[14] * 1);

	return result;
}