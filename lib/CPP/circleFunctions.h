#ifndef CIRCLE_FUNCTIONS_H
#define CIRCLE_FUNCTIONS_H

#include "constants.h"
#include "globals.h"
#include <math.h>

bool collideWithWall(int index, int newX, int newY, int width, int height);

bool collideWithCircle(int index, int newX, int newY, int width, int height);

void updateCircles(int width, int height);

#endif