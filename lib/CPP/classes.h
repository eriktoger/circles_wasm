#ifndef CLASSES_H
#define CLASSES_H

#include "helpers.h"

class Circle {
public:
  Circle(int x, int y, int r, int cr, int cg, int cb)
      : x(x), y(y), r(r), cr(cr), cg(cg), cb(cb) {}
  Circle() : x(0), y(0), r(0), cr(0), cg(0), cb(0) {}

  void setX(int newX);
  void setY(int newY);
  void changeColor();

  int getX() const;
  int getY() const;
  int getR() const;
  int getCR() const;
  int getCG() const;
  int getCB() const;

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

#endif