#ifndef INPUTFUNCTION_H
#define INPUTFUNCTION_H

#include <iostream>
#include <gl/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Util.h"
#include "World.h"

#include "GlobalValue.h"
#include "FinalPracticeObj.h"
#include "GunShoothingObject.h"

void mouseFunc(int button, int state, int x, int y);
void mouseMove(int x, int y);
void keyBoardFunc(unsigned char key, int x, int y);
void keyBoardUpFunc(unsigned char key, int x, int y);

#endif