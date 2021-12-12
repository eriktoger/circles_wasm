#include "classes.h"

void Circle::setX(int newX) { x = newX; }
void Circle::setY(int newY) { y = newY; }

void Circle::changeColor() {
  cr = getRand(255);
  cg = getRand(255);
  cb = getRand(255);
}

int Circle::getX() const { return x; }
int Circle::getY() const { return y; }
int Circle::getR() const { return r; }
int Circle::getCR() const { return cr; }
int Circle::getCG() const { return cg; }
int Circle::getCB() const { return cb; }