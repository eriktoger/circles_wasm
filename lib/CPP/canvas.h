#ifndef CANVAS_H
#define CANVAS_H

#include "functions.h"
#include <emscripten.h>
#include <emscripten/bind.h>
#include <vector>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

std::vector<Circle> getCircles(int width, int height);

int main();
#endif