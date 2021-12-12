#include <emscripten.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CIRCLES 10
#define PI 3.14159265359

struct Circle {
  int x;
  int y;
  int r;
  int cr;
  int cg;
  int cb;
};

struct AnimationData {
  double direction;
  double velocity;
};

struct Circle circles[NUM_CIRCLES];
struct AnimationData animationData[NUM_CIRCLES];

int getRand(int max) { return rand() % max + 1; }

double getDirection(double start, double end) {
  return start + ((double)rand() / RAND_MAX) * (end - start);
}

int main() {

  srand(time(NULL));
  for (int i = 0; i < NUM_CIRCLES; i++) {

    int radius = getRand(50);
    int x = getRand(1000 - radius) + radius;
    int y = getRand(1000 - radius) + radius;
    int cr = getRand(255);
    int cg = getRand(255);
    int cb = getRand(255);
    struct Circle c = {x, y, radius, cr, cg, cb};
    circles[i] = c;

    double direction = getDirection(0, 2 * PI);

    double velocity = getRand(10) + 1;

    struct AnimationData ad = {direction, velocity};
    animationData[i] = ad;
  }

  EM_ASM({ render($0, $1); }, NUM_CIRCLES, 6);
}

void updateCircles(int width, int height) {
  for (int i = 0; i < NUM_CIRCLES; i++) {
    // will it collide with a wall?

    double cosVal = cos(animationData[i].direction);
    int signOfCosVal = cosVal > 0 ? 1 : -1;

    int newX = circles[i].x + cosVal * animationData[i].velocity;

    double sinVal = sin(animationData[i].direction);

    int newY = circles[i].y + sinVal * animationData[i].velocity;

    // there is a edge case when the circle touches both walls, and my if
    // statments are in the wrong order
    // printf("%f %f %f \n", animationData[i].direction, sinVal, cosVal);
    if ((newY + circles[i].r) >= height) { // top
      circles[i].y = height - circles[i].r;
      circles[i].x = newX;
      animationData[i].direction = getDirection(PI, 2 * PI);
    } else if ((newY - circles[i].r) <= 0) { // bottom
      circles[i].y = circles[i].r;
      circles[i].x = newX;
      animationData[i].direction = getDirection(0, PI);
    } else if ((newX + circles[i].r) >= width) { //  right
      circles[i].x = width - circles[i].r;
      circles[i].y = newY;
      animationData[i].direction = getDirection(PI / 2, 3 * PI / 2);
    } else if ((newX - circles[i].r) <= 0) { // left
      circles[i].x = circles[i].r;
      circles[i].y = newY;
      animationData[i].direction = getDirection(0, PI) - PI / 2;
    } else {
      circles[i].x = newX;
      circles[i].y = newY;
    }
  }
}

struct Circle *getCircles(int width, int height) {

  updateCircles(width, height);

  return circles;
}
