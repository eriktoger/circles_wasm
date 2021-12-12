#include "helpers.h"
int getRand(int max) { return rand() % max + 1; }

double getRandomDirection(double start, double end) {
  return start + ((double)rand() / RAND_MAX) * (end - start);
}