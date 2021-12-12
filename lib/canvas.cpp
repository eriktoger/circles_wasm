#include <emscripten.h>
#include <emscripten/bind.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#define NUM_CIRCLES 5
#define PI 3.14159265359

// em++ --bind -o public/CPP/canvas.js lib/canvas.cpp

class Circle {
public:
  Circle(int x, int y, int r, int cr, int cg, int cb)
      : x(x), y(y), r(r), cr(cr), cg(cg), cb(cb) {}
  Circle() : x(0), y(0), r(0), cr(0), cg(0), cb(0) {}

  void setX(int newX) { x = newX; }
  void setY(int newY) { y = newY; }

  int getX() const { return x; }
  int getY() const { return y; }
  int getR() const { return r; }
  int getCR() const { return cr; }
  int getCG() const { return cg; }
  int getCB() const { return cb; }

private:
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
  AnimationData(double d, double v) : direction(d), velocity(v) {}
};

std::vector<Circle> circles;
std::vector<AnimationData> animationData;

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
    circles.emplace_back(x, y, radius, cr, cg, cb);

    double direction = getDirection(0, 2 * PI);
    double velocity = getRand(10) + 1;
    animationData.emplace_back(direction, velocity);
  }

  EM_ASM({ render($0, $1); }, NUM_CIRCLES, 6);
}

void updateCircles(int width, int height) {
  for (int i = 0; i < NUM_CIRCLES; i++) {
    // will it collide with a wall?

    int x = circles[i].getX();
    int y = circles[i].getY();
    int r = circles[i].getR();
    double cosVal = cos(animationData[i].direction);
    int signOfCosVal = cosVal > 0 ? 1 : -1;

    int newX = x + cosVal * animationData[i].velocity;

    double sinVal = sin(animationData[i].direction);

    int newY = y + sinVal * animationData[i].velocity;

    // there is a edge case when the circle touches both walls, and my if
    // statments are in the wrong order
    // printf("%f %f %f \n", animationData[i].direction, sinVal, cosVal);
    if ((newY + r) >= height) { // top
      circles[i].setY(height - r);
      circles[i].setX(newX);
      animationData[i].direction = getDirection(PI, 2 * PI);
    } else if ((newY - r) <= 0) { // bottom
      circles[i].setY(r);
      circles[i].setX(newX);
      animationData[i].direction = getDirection(0, PI);
    } else if ((newX + r) >= width) { //  right
      circles[i].setX(width - r);
      circles[i].setY(newY);
      animationData[i].direction = getDirection(PI / 2, 3 * PI / 2);
    } else if ((newX - r) <= 0) { // left
      circles[i].setX(r);
      circles[i].setY(newY);
      animationData[i].direction = getDirection(0, PI) - PI / 2;
    } else {
      circles[i].setX(newX);
      circles[i].setY(newY);
    }
  }
}

std::vector<Circle> getCircles(int width, int height) {

  updateCircles(width, height);
  return circles;
}

EMSCRIPTEN_BINDINGS(my_module) {
  emscripten::class_<Circle>("Circle")
      .property("x", &Circle::getX)
      .property("y", &Circle::getY)
      .property("r", &Circle::getR)
      .property("cr", &Circle::getCR)
      .property("cg", &Circle::getCG)
      .property("cb", &Circle::getCB);
  emscripten::register_vector<Circle>("vector<Circle>");

  emscripten::function("getCircles", &getCircles);
  emscripten::function("main", &main);
}
