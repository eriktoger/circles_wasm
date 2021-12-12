#ifndef EXPORT_H
#define EXPORT_H

#include "circleFunctions.h"
#include "constants.h"
#include "globals.h"
#include "helpers.h"
#include <emscripten.h>
#include <emscripten/bind.h>
#include <vector>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

std::vector<Circle> getCircles(int width, int height);

void init(int width, int height);

void increaseCircles();

void decreaseCircles();

void changeColor(int x, int y);
#endif
