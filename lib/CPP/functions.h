#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "constants.h"
#include <math.h>
#include <stdlib.h>

bool collideWithWall(int index, int newX, int newY, int width, int height);

bool collideWithCircle(int index, int newX, int newY, int width, int height);

void updateCircles(int width, int height);

int getRand(int max);

double getDirection(double start, double end);

#endif