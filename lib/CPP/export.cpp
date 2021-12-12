#include "export.h"

void init(int width, int height) {
  srand(time(NULL));
  for (int i = 0; i < MAX_NUM_CIRCLES; i++) {

    int radius = getRand(30) + 20;
    int x = getRand(width - radius) + radius;
    int y = getRand(height - radius) + radius;
    int cr = getRand(255);
    int cg = getRand(255);
    int cb = getRand(255);
    circles.emplace_back(x, y, radius, cr, cg, cb);

    double direction = getRandomDirection(0, 2 * PI);
    double velocity = getRand(10) + 1;
    animationData.emplace_back(direction, velocity);
  }

  EM_ASM({render()});
}

std::vector<Circle> getCircles(int width, int height) {
  updateCircles(width, height);
  return std::vector<Circle>(circles.begin(), circles.begin() + displayNr);
}

void increaseCircles() {
  if (displayNr < MAX_NUM_CIRCLES) {
    displayNr++;
  }
}

void decreaseCircles() {
  if (displayNr > 0) {
    displayNr--;
  }
}

void changeColor(int x, int y) {
  for (int i = 0; i < displayNr; i++) {

    auto &circle = circles[i];
    auto circleX = circle.getX();
    auto circleY = circle.getY();
    auto r = circle.getR();

    double distance =
        r * r - (circleX - x) * (circleX - x) - (circleY - y) * (circleY - y);

    if (distance >= 0) {
      circle.changeColor();
    }
  }
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

  emscripten::function("increaseCircles", &increaseCircles);
  emscripten::function("decreaseCircles", &decreaseCircles);
  emscripten::function("changeColor", &changeColor);

  emscripten::function("getCircles", &getCircles);
  emscripten::function("init", &init);
}
