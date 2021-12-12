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
#define SINP4 0.70710678118

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

struct Point {
  double x;
  double y;
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

    int radius = getRand(40) + 10;
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

bool collideWithWall(int index, int newX, int newY, int width, int height) {

  int r = circles[index].getR();

  // there is a edge case when the circle touches both walls, and my if
  // statments are in the wrong order
  if ((newY + r) >= height) { // top
    circles[index].setY(height - r);
    circles[index].setX(newX);
    animationData[index].direction = getDirection(PI, 2 * PI);
    return true;
  } else if ((newY - r) <= 0) { // bottom
    circles[index].setY(r);
    circles[index].setX(newX);
    animationData[index].direction = getDirection(0, PI);
    return true;
  } else if ((newX + r) >= width) { //  right
    circles[index].setX(width - r);
    circles[index].setY(newY);
    animationData[index].direction = getDirection(PI / 2, 3 * PI / 2);
    return true;
  } else if ((newX - r) <= 0) { // left
    circles[index].setX(r);
    circles[index].setY(newY);
    animationData[index].direction = getDirection(0, PI) - PI / 2;
    return true;
  }
  return false;
}

bool collideWithCircle(int index, int newX, int newY, int width, int height) {

  double x = newX;
  double y = newY;
  double r = (double)circles[index].getR();
  // checking 8 points on the circles perimiter
  // (x,y + r)
  double length = r * SINP4;
  std::vector<Point> bounderies = {{x + r, y},      {x + length, y - length},
                                   {x, y - r},      {x - length, y - length},
                                   {x - length, y}, {x - length, y + length},
                                   {x, y + r},      {x + length, y + length}};

  for (int j = index + 1; j < NUM_CIRCLES; j++) {
    int x2 = circles[j].getX();
    int y2 = circles[j].getY();
    int r2 = circles[j].getR();
    for (auto &point : bounderies) {
      double distance = r2 * r2 - (point.x - x2) * (point.x - x2) -
                        (point.y - y2) * (point.y - y2);

      if (distance >= 0) {

        auto dir1 = animationData[index].direction;
        auto dir2 = animationData[j].direction;

        auto reverseDir1 = dir1 + PI;
        if (reverseDir1 > 2 * PI) {
          reverseDir1 -= 2 * PI;
        }

        auto reverseDir2 = dir2 + PI;
        if (reverseDir2 > 2 * PI) {
          reverseDir2 -= 2 * PI;
        }

        // head on collision
        if (abs(reverseDir1 - dir2) < PI) {

          animationData[index].direction = reverseDir1;
          animationData[j].direction = reverseDir2;

        } else {
          // catch up with same direction
          // the faster one should reverse.
          if (animationData[index].velocity >= animationData[j].velocity) {
            animationData[index].direction = reverseDir1;
          } else {
            animationData[j].direction = reverseDir2;
          }
        }

        return true;

        // I may add side collision later on
      }
    }
  }

  return false;
}

void updateCircles(int width, int height) {
  for (int index = 0; index < NUM_CIRCLES; index++) {
    double x = (double)circles[index].getX();
    double y = (double)circles[index].getY();
    double r = (double)circles[index].getR();

    double cosVal = cos(animationData[index].direction);
    int newX = x + cosVal * animationData[index].velocity;
    double sinVal = sin(animationData[index].direction);
    int newY = y + sinVal * animationData[index].velocity;

    // will it collide with a wall?
    auto hitWall = collideWithWall(index, newX, newY, width, height);
    auto hitCircle = collideWithCircle(index, newX, newY, width, height);

    if (!hitWall && !hitCircle) {
      circles[index].setX(newX);
      circles[index].setY(newY);
    };
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
