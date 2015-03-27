#include "FireWork.h"

void Firework::Draw()
{
	int St_x = startPoint.x;
	int St_y = startPoint.y;

	int Ed_x = endPoint.x;
	int Ed_y = endPoint.y;

	int DeltaX, DeltaY;
	int X, Y;
	int D;
	int InCount = 0;

	float _z = -299;

	DeltaX =  Ed_x -  St_x;
	DeltaY =  Ed_y -  St_y;

	X = 1;
	Y = 1;

	if( DeltaX < 0 ) {
		DeltaX = -DeltaX;
		X = -1;
	}

	if( DeltaY < 0 ) {
		DeltaY = -DeltaY;
		Y =-1;
	}

	glColor3f(r, g, b);
	glPointSize(2);

	glBegin(GL_POINTS);
	glVertex3f(St_x, St_y, _z);
	glEnd();

	if( DeltaX > DeltaY ) {

		D = ( 2 * DeltaY ) - DeltaX;

		while( ( St_x !=  Ed_x) && (InCount != count) ) {

			if( D >= 0 ) {
				St_y += Y;
				D -= 2 * DeltaX;
			}
			St_x += X;
			D += 2 * DeltaY;

			glColor3f(1.0, 0, 0);
			glPointSize(2);

			glBegin(GL_POINTS);
			glVertex3f(St_x, St_y, _z);
			glEnd();
			InCount++;
		}
	}

	else {

		D = ( 2 * DeltaX ) - DeltaY;

		while( ( St_y !=  Ed_y) && (InCount != count) ) {
			if( D >= 0 ) {
				St_x += X;
				D -= 2 * DeltaY;
			}

			St_y += Y;
			D += 2 * DeltaX;

			glColor3f(1.0, 0, 0);
			glPointSize(2);

			glBegin(GL_POINTS);
			glVertex3f(St_x, St_y, _z);
			glEnd();
			InCount++;
		}
	}
	/*if( (count == endPoint.x + 100) || (count == endPoint.y + 100) ){
		count = 0;

		_point tempStart = endPoint, tempEnd = endPoint;
		tempEnd.x = (rand() % 600) - 300;
		tempEnd.y += (rand() % 50) + 100;

		BoxStage::Instance()->AddObject(new Firework(tempStart, tempEnd));
	}*/

	return;
}

void Firework::Update() {
	count ++;
	if( (count == endPoint.x + 100) || (count == endPoint.y + 100) ){
		count = 0;
		endPoint.x = (rand() % 600) - 300;
		endPoint.y += (rand() % 50) + 100;
	}
	
}