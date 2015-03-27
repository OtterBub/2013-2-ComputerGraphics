#include "UserInterface.h"

void UserInterface::draw() {
	glPushMatrix();

	drawStrokeText(0, 0, -1, 0.0005, "printf");

	glPopMatrix();
}

void UserInterface::update() {
	
}