#include "canvas.h"

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
