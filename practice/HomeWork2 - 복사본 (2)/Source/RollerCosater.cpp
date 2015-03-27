#include "RollerCosater.h"

#define SPEEDCONTROLL 10

// ------------- SplineCurve --------------------

void SplineCurve::AddPoint(float _x, float _y, float _z)
{
	_point temp;
	temp.x = _x;
	temp.y = _y;
	temp.z = _z;
	pointList.push_back(temp);
	
}

void SplineCurve::AddSplineCureve(_point p[4])
{

	int index = 0;
	if(!m_first)
		index = 1;
	for(index; index <= 4; index++) {
		_point result = CubicBezierCurve(p, (index)/4.f);
		AddPoint(result.x, result.y, result.z);
		clickPoint.push_back(p[index]);
	}

	for(int i = 0; i <= 15; i++) {
		_point result = CubicBezierCurve(p, i/15.f);
		drawPoint.push_back(result);
	}
	
}

void SplineCurve::Draw()
{
	//Object3D::Draw();

	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for(std::vector<_point>::iterator it = drawPoint.begin(); it != drawPoint.end(); it++) {
		glVertex3f(it->x, it->y, it->z);
	}
	glEnd();

	
	glColor3f(1, 0, 1);
	for(std::vector<_point>::iterator it = pointList.begin(); it != pointList.end(); it++) {
		glBegin(GL_LINES);
		glVertex3f(it->x, it->y, it->z);
		glVertex3f(it->x, 0, it->z);
		glEnd();
	}

	glColor3f(1, 0, 1);
	
	for(std::vector<_point>::iterator it = clickPoint.begin(); it != clickPoint.end(); it++) {
		glPushMatrix();

		glTranslatef(it->x, it->y, it->z);
		glColor3f(0.0, 0.0, 1);
		glutSolidCube(10);

		glPopMatrix();
		
	}
	
}

void SplineCurve::Update()
{

}

// -------------------- RollerCosater ---------------------

void RollerCosater::Draw()
{
	Object3D::Draw();
	glutWireCube(20);

	glPopMatrix();

	glPushMatrix();
	CollisionBox debug;
	debug.Max.x = nextPoint->x + abs(vector.x) + 1;
	debug.Max.y = nextPoint->y + abs(vector.y) + 1;
	debug.Max.z = nextPoint->z + abs(vector.z) + 1;

	debug.Min.x = nextPoint->x - abs(vector.x) - 1;
	debug.Min.y = nextPoint->y - abs(vector.y) - 1;
	debug.Min.z = nextPoint->z - abs(vector.z) - 1;

	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(debug.Min.x, debug.Min.y, debug.Min.z);
	glVertex3f(debug.Max.x, debug.Min.y, debug.Min.z);
	glVertex3f(debug.Max.x, debug.Max.y, debug.Min.z);
	glVertex3f(debug.Min.x, debug.Max.y, debug.Min.z);
	glEnd();	

	glBegin(GL_LINE_LOOP);
	glVertex3f(debug.Min.x, debug.Min.y, debug.Min.z);
	glVertex3f(debug.Min.x, debug.Min.y, debug.Max.z);
	glVertex3f(debug.Min.x, debug.Max.y, debug.Max.z);
	glVertex3f(debug.Min.x, debug.Max.y, debug.Min.z);
	glEnd();	

	glBegin(GL_LINE_LOOP);
	glVertex3f(debug.Min.x, debug.Min.y, debug.Min.z);
	glVertex3f(debug.Min.x, debug.Min.y, debug.Max.z);
	glVertex3f(debug.Min.x, debug.Max.y, debug.Max.z);
	glVertex3f(debug.Min.x, debug.Max.y, debug.Min.z);
	glEnd();	

	glBegin(GL_LINE_LOOP);
	glVertex3f(debug.Min.x, debug.Min.y, debug.Min.z);
	glVertex3f(debug.Min.x, debug.Min.y, debug.Max.z);
	glVertex3f(debug.Max.x, debug.Min.y, debug.Max.z);
	glVertex3f(debug.Max.x, debug.Min.y, debug.Min.z);
	glEnd();	

	glBegin(GL_LINE_LOOP);
	glVertex3f(debug.Max.x, debug.Max.y, debug.Max.z);
	glVertex3f(debug.Max.x, debug.Min.y, debug.Max.z);
	glVertex3f(debug.Max.x, debug.Min.y, debug.Min.z);
	glVertex3f(debug.Max.x, debug.Max.y, debug.Min.z);
	glEnd();	

	glBegin(GL_LINE_LOOP);
	glVertex3f(debug.Max.x, debug.Max.y, debug.Max.z);
	glVertex3f(debug.Min.x, debug.Max.y, debug.Max.z);
	glVertex3f(debug.Min.x, debug.Min.y, debug.Max.z);
	glVertex3f(debug.Max.x, debug.Min.y, debug.Max.z);
	glEnd();
}

void RollerCosater::Update()
{

	_point dist;
	dist.x = (nextPoint->x - currentPoint->x);
	dist.y = (nextPoint->y - currentPoint->y);
	dist.z = (nextPoint->z - currentPoint->z);

	float rad = atan2(dist.x, dist.y);
	float degree = (rad*180) / 3.14;

	float rad2 = atan2(dist.z, dist.y);
	float degree2 = (rad*180) / 3.14;

	if( abs(degree2) < abs(degree) ) {
		degree = degree2;
	}
	
	float scalar = sqrt(pow(dist.x,2) + pow(dist.y,2) + pow(dist.z,2));

	if((abs(degree) < 90) && !m_init)
		scalar = -scalar;
	

	_point unitVector;
	_point tempVector;

	unitVector.x = (dist.x / scalar);
	unitVector.y = (dist.y / scalar);
	unitVector.z = (dist.z / scalar);

	if( ((abs(degree) > 87) && (abs(degree) < 93)) || ((abs(degree) > 178) && (abs(degree) < 183)) || ((abs(degree) >= 0) && (abs(degree) < 3)) ){
		vector.x;
		vector.y;
		vector.z;
	} else if(m_init){
		vector.x = (unitVector.x);
		vector.y = (unitVector.y);
		vector.z = (unitVector.z);
	} else {
		vector.x += (unitVector.x / SPEEDCONTROLL);
		vector.y += (unitVector.y / SPEEDCONTROLL);
		vector.z += (unitVector.z / SPEEDCONTROLL);
	}
	
	float speed = vector.x / (unitVector.x / SPEEDCONTROLL);
	if( (unitVector.x == 0) )
		speed = vector.y / (unitVector.y / SPEEDCONTROLL);
	if( (unitVector.y == 0) )
		speed = vector.z / (unitVector.z / SPEEDCONTROLL);

	printf("speed %f \n", speed);
	printf("Curspeed %f \n", currentSpeed);
	printf("Degree %f\n\n", degree);

	if((currentSpeed > 0) && (speed < 0)) {
		currentSpeed = speed;
	}

	if(((currentSpeed < 0) && (speed > 0) && (speed < 1))){
		
		previousPoint = currentPoint;
		currentPoint = nextPoint;
		nextPoint = previousPoint;
		

		currentSpeed = speed;

		m_reverse = !m_reverse;
		printf("---- REVERSE!! ------ \n");
	}

	tempVector = vector;

	/*float maxVector = ( vector.x > vector.y ? (vector.x > vector.z ? vector.x : vector.z) : ( vector.y > vector.z ? vector.y : vector.z) );
	float minVector = ( vector.x < vector.y ? (vector.x < vector.z ? vector.x : vector.z) : ( vector.y < vector.z ? vector.y : vector.z) );*/

	if( (point.x + vector.x < (nextPoint->x + abs(vector.x) + 1 ) && (point.x + vector.x > (nextPoint->x - abs(vector.x) - 1 ) ) ) &&
		(point.y + vector.y < (nextPoint->y + abs(vector.y) + 1 ) && (point.y + vector.y > (nextPoint->y - abs(vector.y) - 1 ) ) ) &&
		(point.z + vector.z < (nextPoint->z + abs(vector.z) + 1 ) && (point.z + vector.z > (nextPoint->z - abs(vector.z) - 1 ) ) ) )
	{

		point = *nextPoint;
		previousPoint = currentPoint;
		if(m_reverse){
			if((currentPoint) == pointList.begin())
				currentPoint = pointList.end() - 1;
			else
				currentPoint--;

			if((nextPoint) == pointList.begin())
				nextPoint = pointList.end() - 1;
			else
				nextPoint--;
		} else {

			if((nextPoint + 1) == pointList.end()){
				nextPoint = pointList.begin();
				m_init = true;
			}
			else {
				nextPoint++;
			}

			if((nextPoint == pointList.begin() + 1) && m_init){
				previousPoint = currentPoint = pointList.begin();
				nextPoint = previousPoint + 1;

				point = *currentPoint;

				currentTime = clock();

				vector.x = 0;
				vector.y = 0;
				vector.z = 0;
				currentSpeed = 0;

				m_init = false;
				m_reverse = false;
				sinValue = 0;
				printf("init\n");
			}
			else
				currentPoint++;

			
		}
		//printf("next point\n");

		speed = vector.x / (unitVector.x / SPEEDCONTROLL);
		if( (unitVector.x == 0) )
			speed = vector.y / (unitVector.y / SPEEDCONTROLL);
		if( (unitVector.y == 0) )
			speed = vector.z / (unitVector.z / SPEEDCONTROLL);
		
		

		dist.x = (nextPoint->x - currentPoint->x);
		dist.y = (nextPoint->y - currentPoint->y);
		dist.z = (nextPoint->z - currentPoint->z);

		rad = atan2(dist.x, dist.y);
		float nextDegree = (rad*180) / 3.14;

		//printf("degree :: %.2f \n", degree);
		//printf("NextDegree :: %.2f \n", nextDegree);

		if(scalar <= 0){
			scalar = -(sqrt(pow(dist.x,2) + pow(dist.y,2) + pow(dist.z,2)));
		} else {
			scalar = (sqrt(pow(dist.x,2) + pow(dist.y,2) + pow(dist.z,2)));
		}

		unitVector.x = dist.x / scalar;
		unitVector.y = dist.y / scalar;
		unitVector.z = dist.z / scalar;

		if(abs(sin(rad)) > sinValue){
			sinValue = abs(sin(rad));
		} else if(abs(sin(rad)) < sinValue) {
			sinValue = abs(sin(rad));
			speed/=1.01;
			//printf("---- down speed ----\n");
		}
		/*printf("speed %.2f\n", speed);
		printf("sin(rad)%.2f\n", sin(rad));*/

		tempVector.x = (unitVector.x / SPEEDCONTROLL) * speed;
		tempVector.y = (unitVector.y / SPEEDCONTROLL) * speed;
		tempVector.z = (unitVector.z / SPEEDCONTROLL) * speed;


		//printf("Speed %.2f\n", speed);

		currentSpeed = speed;

	} else if(20 < clock() - currentTime){
		currentTime = clock();
		ObjectControlPosition(vector.x, vector.y, vector.z);
	}

	vector = tempVector;
}